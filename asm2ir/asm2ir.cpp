#include "llvm_c_api.h"
#include <cstdint>
extern "C" {
#include "../sim.h"
}

#include <algorithm>
#include <array>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace wave32 {
constexpr int W = SIM_X_SIZE / 3;
constexpr int H = SIM_Y_SIZE / 3;
constexpr int N = W * H;
constexpr int REGS = 128;
constexpr int BUFFERS = 4;
constexpr uint64_t REG_FLAG = 1ull << 32;
static_assert(W == 512 && H == 256, "Wave32 app.wasm targets 512x256 cells");

struct State {
  int32_t reg[REGS];
  int32_t mem[N * BUFFERS];
};
static_assert(sizeof(State) == (REGS + BUFFERS * N) * sizeof(int32_t), "Packed register/memory layout");

enum class Op {
  MOV, ADD, SUB, MUL, DIV, MOD, AND, OR, SHL, ASHR,
  EQ, NE, LT, LE, GT, GE, LD, ST, CIRCLE, STENCIL, SHADE,
  RAND, PIXEL, FLUSH, JMP, BR, HALT
};
struct Spec { const char *name; Op op; int args; bool control; };
static constexpr Spec SPECS[] = {
  {"mov", Op::MOV,2,false}, {"add",Op::ADD,3,false},
  {"sub",Op::SUB,3,false}, {"mul",Op::MUL,3,false},
  {"div",Op::DIV,3,false}, {"mod",Op::MOD,3,false},
  {"and",Op::AND,3,false}, {"or",Op::OR,3,false},
  {"shl",Op::SHL,3,false}, {"ashr",Op::ASHR,3,false},
  {"eq",Op::EQ,3,false}, {"ne",Op::NE,3,false},
  {"lt",Op::LT,3,false}, {"le",Op::LE,3,false},
  {"gt",Op::GT,3,false}, {"ge",Op::GE,3,false},
  {"ld",Op::LD,3,false}, {"st",Op::ST,3,false},
  {"circle",Op::CIRCLE,6,false}, {"stencil",Op::STENCIL,4,false},
  {"shade",Op::SHADE,3,false}, {"rand",Op::RAND,1,false},
  {"pixel",Op::PIXEL,3,false}, {"flush",Op::FLUSH,0,false},
  {"jmp",Op::JMP,1,true}, {"br",Op::BR,3,true},
  {"halt",Op::HALT,0,true}
};

static std::string trim(std::string s) {
  const auto start = s.find_first_not_of(" \t\r\n");
  if (start == std::string::npos) return "";
  const auto end = s.find_last_not_of(" \t\r\n");
  return s.substr(start,end-start+1);
}
static const Spec &specFor(const std::string &name) {
  for (const auto &s : SPECS) if (name == s.name) return s;
  throw std::runtime_error("unknown instruction: " + name);
}
static inline bool isReg(uint64_t o) { return (o & REG_FLAG) != 0; }
static inline int regNo(uint64_t o) {
  if (!isReg(o) || (o & 0xffffffffu) >= REGS) throw std::runtime_error("destination is not a register");
  return int(o & 0xffffffffu);
}
static inline int32_t value(const State &s,uint64_t o) {
  return isReg(o) ? s.reg[regNo(o)] : static_cast<int32_t>(static_cast<uint32_t>(o));
}
static inline void set(State &s,uint64_t o,int32_t v) { s.reg[regNo(o)] = v; }
static inline int32_t &cell(State &s,int32_t base,int32_t offset) {
  if (base < 0 || base >= BUFFERS || offset < 0 || offset >= N)
    throw std::runtime_error("memory index out of range (buffer=" + std::to_string(base) +
                             ", index=" + std::to_string(offset) + ")");
  return s.mem[base * N + offset];
}
static int32_t clamp255(int32_t v) { return std::max<int32_t>(0, std::min<int32_t>(255,v)); }
static uint32_t wrappingAdd(int32_t a,int32_t b) { return uint32_t(a)+uint32_t(b); }
static uint32_t wrappingSub(int32_t a,int32_t b) { return uint32_t(a)-uint32_t(b); }
static uint32_t wrappingMul(int32_t a,int32_t b) { return uint32_t(a)*uint32_t(b); }
static int32_t shade(State &s,int32_t base,int32_t idx) {
  auto at=[&](int d){return cell(s,base,idx+d);};
  int32_t slope=(at(-1)-at(1))+(at(-W)-at(W));
  int32_t brightness=clamp255(90+(slope>>2)+(at(0)>>4));
  int32_t red=(brightness*brightness*brightness)>>16;
  int32_t green=clamp255(30+((brightness*brightness)>>8));
  int32_t blue=clamp255(80+brightness);
  return static_cast<int32_t>(0xFF000000u | (uint32_t(red)<<16) |
                               (uint32_t(green)<<8) | uint32_t(blue));
}
static void stencil(State &s,int32_t cur,int32_t prev,int32_t water,int32_t i) {
  uint32_t neighbors=wrappingAdd(cell(s,cur,i-1),cell(s,cur,i+1));
  neighbors+=wrappingAdd(cell(s,cur,i-W),cell(s,cur,i+W));
  int32_t v=static_cast<int32_t>(neighbors)>>1;
  v=static_cast<int32_t>(wrappingSub(v,cell(s,prev,i)));
  v=static_cast<int32_t>(wrappingSub(v,v>>6));
  cell(s,prev,i)=v & cell(s,water,i);
}

// One interpreter implementation shared by the native simulator and the
// independently callable instruction handlers in the external-call JIT mode.
static void emulate(State &s,Op op,const std::array<uint64_t,6> &a) {
  auto v=[&](int n)->int32_t{return value(s,a[n]);};
  auto dst=[&](int32_t x){set(s,a[0],x);};
  switch(op) {
    case Op::MOV: dst(v(1)); break;
    case Op::ADD: dst(int32_t(wrappingAdd(v(1),v(2)))); break;
    case Op::SUB: dst(int32_t(wrappingSub(v(1),v(2)))); break;
    case Op::MUL: dst(int32_t(wrappingMul(v(1),v(2)))); break;
    case Op::DIV: if (!v(2)) throw std::runtime_error("division by zero"); dst(v(1)/v(2)); break;
    case Op::MOD: if (!v(2)) throw std::runtime_error("modulo by zero"); dst(v(1)%v(2)); break;
    case Op::AND: dst(v(1)&v(2)); break;
    case Op::OR: dst(v(1)|v(2)); break;
    case Op::SHL: dst(int32_t(uint32_t(v(1)) << (uint32_t(v(2))&31u))); break;
    case Op::ASHR: dst(v(1) >> (uint32_t(v(2))&31u)); break;
    case Op::EQ: dst(v(1)==v(2)); break;
    case Op::NE: dst(v(1)!=v(2)); break;
    case Op::LT: dst(v(1)<v(2)); break;
    case Op::LE: dst(v(1)<=v(2)); break;
    case Op::GT: dst(v(1)>v(2)); break;
    case Op::GE: dst(v(1)>=v(2)); break;
    case Op::LD: dst(cell(s,v(1),v(2))); break;
    case Op::ST: cell(s,v(0),v(1))=v(2); break;
    case Op::CIRCLE: {
      int32_t dx=v(1)-v(3),dy=v(2)-v(4),r=v(5);
      dst(dx*dx+dy*dy < r*r);
      break;
    }
    case Op::STENCIL: stencil(s,v(0),v(1),v(2),v(3)); break;
    case Op::SHADE: dst(shade(s,v(1),v(2))); break;
    case Op::RAND: dst(simRand()); break;
    case Op::PIXEL: simPutPixel(v(0),v(1),v(2)); break;
    case Op::FLUSH: simFlush(); break;
    default: throw std::runtime_error("control instructions aren't emulated as data operations");
  }
}

// Each non-control opcode has its OWN callable emulator symbol. The IR for
// --mode calls contains one call to this function for each ASM instruction.
// Signature intentionally fixed: (State*, i64 operands[6]) without an array,
// so no stack temporaries or argument marshalling are needed in JIT code.
#define ARGDECL uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5
#define EMU(NAME,OP) extern "C" void emu_##NAME(State *s,ARGDECL) {emulate(*s,Op::OP,{{a0,a1,a2,a3,a4,a5}});}
EMU(mov,MOV) EMU(add,ADD) EMU(sub,SUB) EMU(mul,MUL) EMU(div,DIV)
EMU(mod,MOD) EMU(and,AND) EMU(or,OR) EMU(shl,SHL) EMU(ashr,ASHR)
EMU(eq,EQ) EMU(ne,NE) EMU(lt,LT) EMU(le,LE) EMU(gt,GT) EMU(ge,GE)
EMU(ld,LD) EMU(st,ST) EMU(circle,CIRCLE) EMU(stencil,STENCIL)
EMU(shade,SHADE) EMU(rand,RAND) EMU(pixel,PIXEL) EMU(flush,FLUSH)
#undef EMU
#undef ARGDECL
using EmuPtr=void (*)(State*,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static EmuPtr emuFor(Op op) {
#define CASE(NAME,OP) case Op::OP: return &emu_##NAME;
  switch(op) {
    CASE(mov,MOV) CASE(add,ADD) CASE(sub,SUB) CASE(mul,MUL)
    CASE(div,DIV) CASE(mod,MOD) CASE(and,AND) CASE(or,OR)
    CASE(shl,SHL) CASE(ashr,ASHR) CASE(eq,EQ) CASE(ne,NE)
    CASE(lt,LT) CASE(le,LE) CASE(gt,GT) CASE(ge,GE)
    CASE(ld,LD) CASE(st,ST) CASE(circle,CIRCLE)
    CASE(stencil,STENCIL) CASE(shade,SHADE) CASE(rand,RAND)
    CASE(pixel,PIXEL) CASE(flush,FLUSH)
    default: return nullptr;
  }
#undef CASE
}

struct Inst {
  Op op;
  std::string mnemonic;
  std::array<uint64_t,6> a{};
  std::array<std::string,3> labels{};
  int line=0;
};
struct Program {
  std::vector<Inst> code;
  std::unordered_map<std::string,size_t> labels;
  std::unordered_map<std::string,int> registers;
  std::vector<std::string> labelOrder;
};

static Program parse(const std::string &path) {
  std::ifstream file(path);
  if (!file) throw std::runtime_error("unable to open ASM file: " + path);
  Program prog;
  std::string raw;
  int line=0;
  while(std::getline(file,raw)) {
    ++line;
    raw=trim(raw.substr(0,raw.find(';')));
    if(raw.empty()) continue;
    if(raw.back()==':') {
      std::string name=trim(raw.substr(0,raw.size()-1));
      if (name.empty() || prog.labels.count(name)) throw std::runtime_error("invalid/duplicate label at line "+std::to_string(line));
      prog.labels[name]=prog.code.size();
      prog.labelOrder.push_back(name);
      continue;
    }
    auto ws=raw.find_first_of(" \t");
    std::string name=raw.substr(0,ws);
    const auto &spec=specFor(name);
    std::string rest=ws==std::string::npos ? "" : trim(raw.substr(ws));
    std::vector<std::string> args;
    while(!rest.empty()) {
      auto comma=rest.find(',');
      auto token=trim(rest.substr(0,comma));
      if(token.empty()) throw std::runtime_error("empty operand at line "+std::to_string(line));
      args.push_back(token);
      if(comma==std::string::npos) break;
      rest=trim(rest.substr(comma+1));
    }
    if(int(args.size())!=spec.args) throw std::runtime_error("wrong operand count at line "+std::to_string(line)+" ("+name+")");
    Inst ins{spec.op,name,{}, {},line};
    for(int k=0;k<spec.args;k++) {
      const auto &t=args[k];
      bool isLabel= (spec.op==Op::JMP) || (spec.op==Op::BR && k>=1);
      if(isLabel) {ins.labels[k]=t;continue;}
      if(t[0]=='%') {
        if(t.size()==1) throw std::runtime_error("empty register at line "+std::to_string(line));
        auto it=prog.registers.find(t);
        if(it==prog.registers.end()) {
          int id=int(prog.registers.size());
          if(id>=REGS) throw std::runtime_error("register file exhausted");
          it=prog.registers.emplace(t,id).first;
        }
        ins.a[k]=REG_FLAG | uint64_t(it->second);
      } else {
        size_t n=0;
        long long v;
        try { v=std::stoll(t,&n,0); }
        catch(...) {throw std::runtime_error("invalid immediate '"+t+"' at line "+std::to_string(line));}
        if(n!=t.size() || v<INT32_MIN || (v>=0 && static_cast<unsigned long long>(v)>UINT32_MAX))
          throw std::runtime_error("immediate exceeds 32 bits at line "+std::to_string(line));
        ins.a[k]=uint32_t(v);
      }
    }
    if(!spec.control) {
      // Destinations are explicit for register-writing instructions.
      if(spec.op!=Op::ST && spec.op!=Op::STENCIL && spec.op!=Op::PIXEL && spec.op!=Op::FLUSH)
        regNo(ins.a[0]);
    } else if(spec.op==Op::BR && !isReg(ins.a[0])) {
      throw std::runtime_error("br condition must be a register at line "+std::to_string(line));
    }
    prog.code.push_back(ins);
  }
  if(prog.labelOrder.empty() || prog.labels.at(prog.labelOrder.front())!=0)
    throw std::runtime_error("ASM must start with a label");
  for(const auto &i: prog.code) {
    if(i.op==Op::JMP && !prog.labels.count(i.labels[0]))
      throw std::runtime_error("undefined jump label '"+i.labels[0]+"'");
    if(i.op==Op::BR && (!prog.labels.count(i.labels[1]) || !prog.labels.count(i.labels[2])))
      throw std::runtime_error("undefined branch label at line "+std::to_string(i.line));
  }
  // Make malformed fall-through / dead code explicit rather than silently
  // introducing control-flow not present in the user's assembler.
  std::vector<bool> starts(prog.code.size()+1,false);
  for(const auto &[label,index]:prog.labels) starts[index]=true;
  for(size_t i=0;i<prog.code.size();++i) {
    bool end=prog.code[i].op==Op::JMP||prog.code[i].op==Op::BR||prog.code[i].op==Op::HALT;
    if(end && i+1<prog.code.size() && !starts[i+1])
      throw std::runtime_error("instructions after terminator at line "+std::to_string(prog.code[i].line));
    if(i+1==prog.code.size() || starts[i+1])
      if(!end) throw std::runtime_error("missing jmp/br/halt at line "+std::to_string(prog.code[i].line));
  }
  return prog;
}

static void runSimulator(const Program &p,State &s) {
  size_t pc=0;
  for(;;) {
    if(pc>=p.code.size()) throw std::runtime_error("program counter out of range");
    const auto &i=p.code[pc];
    if(i.op==Op::JMP) pc=p.labels.at(i.labels[0]);
    else if(i.op==Op::BR) pc=p.labels.at(value(s,i.a[0]) ? i.labels[1] : i.labels[2]);
    else if(i.op==Op::HALT) return;
    else {emulate(s,i.op,i.a);++pc;}
  }
}

class IRCompiler {
  LLVMContextRef C=nullptr;
  LLVMModuleRef M=nullptr;
  LLVMBuilderRef B=nullptr;
  LLVMTypeRef I32=nullptr,I64=nullptr,Void=nullptr,Ptr=nullptr;
  LLVMValueRef Fn=nullptr,S=nullptr;
  const Program &P;
  bool calls;
  std::unordered_map<std::string,LLVMBasicBlockRef> blocks;
  std::unordered_map<std::string,LLVMValueRef> externFns;
  LLVMTypeRef emuTy=nullptr,randTy=nullptr,pixelTy=nullptr,flushTy=nullptr;
  LLVMValueRef const32(uint32_t n){return LLVMConstInt(I32,n,0);}
  LLVMValueRef const64(uint64_t n){return LLVMConstInt(I64,n,0);}
  LLVMValueRef getReg(int i){
    auto *idx=const32(uint32_t(i));
    return LLVMBuildLoad2(B,I32,LLVMBuildGEP2(B,I32,S,&idx,1,"r.ptr"),"r");
  }
  void setReg(uint64_t target,LLVMValueRef val){
    auto *idx=const32(uint32_t(regNo(target)));
    LLVMBuildStore(B,val,LLVMBuildGEP2(B,I32,S,&idx,1,"r.ptr"));
  }
  LLVMValueRef val(uint64_t a){return isReg(a) ? getReg(regNo(a)) : const32(uint32_t(a));}
  LLVMValueRef add(LLVMValueRef x,LLVMValueRef y){return LLVMBuildAdd(B,x,y,"");}
  LLVMValueRef sub(LLVMValueRef x,LLVMValueRef y){return LLVMBuildSub(B,x,y,"");}
  LLVMValueRef mul(LLVMValueRef x,LLVMValueRef y){return LLVMBuildMul(B,x,y,"");}
  LLVMValueRef ashr(LLVMValueRef x,int shift){return LLVMBuildAShr(B,x,const32(shift),"");}
  LLVMValueRef icmp(LLVMIntPredicate p,LLVMValueRef x,LLVMValueRef y){return LLVMBuildICmp(B,p,x,y,"");}
  LLVMValueRef bool32(LLVMValueRef x){return LLVMBuildZExt(B,x,I32,"");}
  LLVMValueRef ptr(LLVMValueRef base,LLVMValueRef offset){
    auto *index=add(add(mul(base,const32(N)),offset),const32(REGS));
    return LLVMBuildGEP2(B,I32,S,&index,1,"mem.ptr");
  }
  LLVMValueRef ld(LLVMValueRef base,LLVMValueRef offset){return LLVMBuildLoad2(B,I32,ptr(base,offset),"mem");}
  void st(LLVMValueRef base,LLVMValueRef offset,LLVMValueRef v){LLVMBuildStore(B,v,ptr(base,offset));}
  LLVMValueRef clamp(LLVMValueRef x){
    x=LLVMBuildSelect(B,icmp(LLVMIntSLT,x,const32(0)),const32(0),x,"");
    return LLVMBuildSelect(B,icmp(LLVMIntSGT,x,const32(255)),const32(255),x,"");
  }
  LLVMValueRef color(LLVMValueRef base,LLVMValueRef idx){
    auto around=[&](int d){return ld(base,add(idx,const32(uint32_t(d))));};
    auto *slope=add(sub(around(-1),around(1)),sub(around(-W),around(W)));
    auto *s=clamp(add(add(const32(90),ashr(slope,2)),ashr(around(0),4)));
    auto *ss=mul(s,s);
    auto *red=ashr(mul(ss,s),16);
    auto *green=clamp(add(const32(30),ashr(ss,8)));
    auto *blue=clamp(add(const32(80),s));
    auto *packed=LLVMBuildOr(B,LLVMBuildOr(B,const32(0xFF000000u),LLVMBuildShl(B,red,const32(16),""),""),LLVMBuildShl(B,green,const32(8),""),"");
    return LLVMBuildOr(B,packed,blue,"");
  }
  LLVMValueRef getIO(const char *name,LLVMTypeRef ty){
    const auto found=externFns.find(name);
    if(found!=externFns.end()) return found->second;
    return externFns.emplace(name,LLVMAddFunction(M,name,ty)).first->second;
  }
  void lowerPure(const Inst &i){
    auto a=i.a;
    auto src=[&](int k){return val(a[k]);};
    switch(i.op){
      case Op::MOV: setReg(a[0],src(1)); break;
      case Op::ADD: setReg(a[0],add(src(1),src(2))); break;
      case Op::SUB: setReg(a[0],sub(src(1),src(2))); break;
      case Op::MUL: setReg(a[0],mul(src(1),src(2))); break;
      case Op::DIV: setReg(a[0],LLVMBuildSDiv(B,src(1),src(2),"")); break;
      case Op::MOD: setReg(a[0],LLVMBuildSRem(B,src(1),src(2),"")); break;
      case Op::AND: setReg(a[0],LLVMBuildAnd(B,src(1),src(2),"")); break;
      case Op::OR: setReg(a[0],LLVMBuildOr(B,src(1),src(2),"")); break;
      case Op::SHL: setReg(a[0],LLVMBuildShl(B,src(1),LLVMBuildAnd(B,src(2),const32(31),""),"")); break;
      case Op::ASHR: setReg(a[0],LLVMBuildAShr(B,src(1),LLVMBuildAnd(B,src(2),const32(31),""),"")); break;
      case Op::EQ: setReg(a[0],bool32(icmp(LLVMIntEQ,src(1),src(2)))); break;
      case Op::NE: setReg(a[0],bool32(icmp(LLVMIntNE,src(1),src(2)))); break;
      case Op::LT: setReg(a[0],bool32(icmp(LLVMIntSLT,src(1),src(2)))); break;
      case Op::LE: setReg(a[0],bool32(icmp(LLVMIntSLE,src(1),src(2)))); break;
      case Op::GT: setReg(a[0],bool32(icmp(LLVMIntSGT,src(1),src(2)))); break;
      case Op::GE: setReg(a[0],bool32(icmp(LLVMIntSGE,src(1),src(2)))); break;
      case Op::LD: setReg(a[0],ld(src(1),src(2))); break;
      case Op::ST: st(src(0),src(1),src(2)); break;
      case Op::CIRCLE: {
        auto *dx=sub(src(1),src(3)),*dy=sub(src(2),src(4)),*r=src(5);
        auto *squared=add(mul(dx,dx),mul(dy,dy));
        setReg(a[0],bool32(icmp(LLVMIntSLT,squared,mul(r,r))));
        break;
      }
      case Op::STENCIL: {
        auto *cur=src(0),*prev=src(1),*water=src(2),*idx=src(3);
        auto neighbor=[&](int d){return ld(cur,add(idx,const32(uint32_t(d))));};
        auto *sum=add(add(neighbor(-1),neighbor(1)),add(neighbor(-W),neighbor(W)));
        auto *v=sub(ashr(sum,1),ld(prev,idx));
        v=sub(v,ashr(v,6));
        st(prev,idx,LLVMBuildAnd(B,v,ld(water,idx),""));
        break;
      }
      case Op::SHADE: setReg(a[0],color(src(1),src(2))); break;
      case Op::RAND: {
        auto *callee=getIO("simRand",randTy);
        setReg(a[0],LLVMBuildCall2(B,randTy,callee,nullptr,0,"rand"));
        break;
      }
      case Op::PIXEL: {
        auto *callee=getIO("simPutPixel",pixelTy);
        LLVMValueRef args[]={src(0),src(1),src(2)};
        LLVMBuildCall2(B,pixelTy,callee,args,3,"");
        break;
      }
      case Op::FLUSH: LLVMBuildCall2(B,flushTy,getIO("simFlush",flushTy),nullptr,0,""); break;
      default: throw std::runtime_error("unknown non-control lowering");
    }
  }
  void lowerCall(const Inst &i){
    LLVMValueRef args[7]={S,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr};
    for(int k=0;k<6;k++) args[k+1]=const64(i.a[k]);
    LLVMBuildCall2(B,emuTy,externFns.at("emu_"+i.mnemonic),args,7,"");
  }
public:
  explicit IRCompiler(const Program &p,bool external):P(p),calls(external){
    C=LLVMContextCreate(); M=LLVMModuleCreateWithNameInContext(calls?"wave32_calls":"wave32_pure",C);
    B=LLVMCreateBuilderInContext(C);
    I32=LLVMInt32TypeInContext(C); I64=LLVMInt64TypeInContext(C);
    Void=LLVMVoidTypeInContext(C); Ptr=LLVMPointerType(I32,0);
    LLVMTypeRef parameters[]={Ptr};
    Fn=LLVMAddFunction(M,"wave32_app",LLVMFunctionType(Void,parameters,1,0));
    S=LLVMGetParam(Fn,0);
    if(calls){
      LLVMTypeRef emuArgs[]={Ptr,I64,I64,I64,I64,I64,I64};
      emuTy=LLVMFunctionType(Void,emuArgs,7,0);
      for(const auto &sp:SPECS) if(!sp.control)
        externFns[std::string("emu_")+sp.name]=LLVMAddFunction(M,(std::string("emu_")+sp.name).c_str(),emuTy);
    } else {
      randTy=LLVMFunctionType(I32,nullptr,0,0);
      LLVMTypeRef pixelArgs[]={I32,I32,I32};
      pixelTy=LLVMFunctionType(Void,pixelArgs,3,0);
      flushTy=LLVMFunctionType(Void,nullptr,0,0);
    }
    for(const auto &name:P.labelOrder) blocks[name]=LLVMAppendBasicBlockInContext(C,Fn,name.c_str());
    std::unordered_map<size_t,LLVMBasicBlockRef> at;
    for(const auto &p:P.labels) at[p.second]=blocks.at(p.first);
    for(size_t k=0;k<P.code.size();k++){
      if(auto it=at.find(k);it!=at.end()) LLVMPositionBuilderAtEnd(B,it->second);
      const auto &ins=P.code[k];
      if(ins.op==Op::JMP) LLVMBuildBr(B,blocks.at(ins.labels[0]));
      else if(ins.op==Op::BR) {
        auto *test=icmp(LLVMIntNE,val(ins.a[0]),const32(0));
        LLVMBuildCondBr(B,test,blocks.at(ins.labels[1]),blocks.at(ins.labels[2]));
      } else if(ins.op==Op::HALT) LLVMBuildRetVoid(B);
      else if(calls) lowerCall(ins);
      else lowerPure(ins);
    }
    char *error=nullptr;
    if(LLVMVerifyModule(M,LLVMReturnStatusAction,&error)){
      std::string msg=error?error:"unknown verifier error";
      if(error)LLVMDisposeMessage(error);
      throw std::runtime_error("invalid generated IR: "+msg);
    }
    if(error) LLVMDisposeMessage(error);
  }
  ~IRCompiler(){
    if(B) LLVMDisposeBuilder(B);
    if(M) LLVMDisposeModule(M);
    if(C) LLVMContextDispose(C);
  }
  void save(const std::string &path){
    char *error=nullptr;
    if(LLVMPrintModuleToFile(M,path.c_str(),&error)){
      std::string msg=error?error:"unknown error";
      if(error)LLVMDisposeMessage(error);
      throw std::runtime_error("IR emit error: "+msg);
    }
  }
  // Link-time mappings installed before ownership transfer, then execute.
  void jit(State &state){
#if defined(__x86_64__) || defined(_M_X64)
    LLVMInitializeX86TargetInfo(); LLVMInitializeX86Target();
    LLVMInitializeX86TargetMC(); LLVMInitializeX86AsmPrinter();
#elif defined(__aarch64__) || defined(_M_ARM64)
    LLVMInitializeAArch64TargetInfo(); LLVMInitializeAArch64Target();
    LLVMInitializeAArch64TargetMC(); LLVMInitializeAArch64AsmPrinter();
#else
#error "Native MCJIT initialization for this CPU has not been added"
#endif
    LLVMLinkInMCJIT();
    LLVMModuleRef module=M;
    LLVMExecutionEngineRef engine=nullptr;
    char *error=nullptr;
    if(LLVMCreateExecutionEngineForModule(&engine,M,&error)){
      std::string msg=error?error:"unknown error";
      if(error)LLVMDisposeMessage(error);
      throw std::runtime_error("ExecutionEngine initialization error: "+msg);
    }
    M=nullptr; // module ownership transferred to the ExecutionEngine
    if(calls) {
      for(const auto &spec:SPECS){
        if(spec.control) continue;
        std::string name=std::string("emu_")+spec.name;
        LLVMValueRef f=LLVMGetNamedFunction(module,name.c_str());
        // memcpy avoids function-pointer-to-object-pointer warnings; the
        // LLVM C API expects host addresses to be supplied as void*.
        EmuPtr callback=emuFor(spec.op);
        void *address=nullptr;
        static_assert(sizeof(callback)==sizeof(address));
        std::memcpy(&address,&callback,sizeof(address));
        LLVMAddGlobalMapping(engine,f,address);
      }
    } else {
      auto bind=[&](const char *name,void *address){
        LLVMValueRef f=LLVMGetNamedFunction(module,name);
        if(!f) throw std::runtime_error(std::string("missing external declaration: ")+name);
        LLVMAddGlobalMapping(engine,f,address);
      };
      using RandFn=int(*)(); using PixelFn=void(*)(int,int,int); using FlushFn=void(*)();
      RandFn r=&simRand; PixelFn p=&simPutPixel; FlushFn f=&simFlush;
      void *rp=nullptr,*pp=nullptr,*fp=nullptr;
      static_assert(sizeof(r)==sizeof(rp));
      std::memcpy(&rp,&r,sizeof(rp));std::memcpy(&pp,&p,sizeof(pp));std::memcpy(&fp,&f,sizeof(fp));
      // No declaration is emitted if an opcode wasn't present in the program.
      if(LLVMGetNamedFunction(module,"simRand")) bind("simRand",rp);
      if(LLVMGetNamedFunction(module,"simPutPixel")) bind("simPutPixel",pp);
      if(LLVMGetNamedFunction(module,"simFlush")) bind("simFlush",fp);
    }
    uint64_t address=LLVMGetFunctionAddress(engine,"wave32_app");
    if(!address) throw std::runtime_error("MCJIT could not resolve wave32_app");
    using Entry=void(*)(State*);
    Entry entry=nullptr;
    static_assert(sizeof(entry)==sizeof(address));
    std::memcpy(&entry,&address,sizeof(entry));
    entry(&state);
    LLVMDisposeExecutionEngine(engine);
  }
};

} // namespace wave32

int main(int argc,char **argv) {
  try{
    std::string mode="ir",file="app.s",output;
    bool emitOnly=false;
    for(int i=1;i<argc;i++){
      std::string arg=argv[i];
      if(arg=="--mode" && i+1<argc) mode=argv[++i];
      else if(arg=="--asm" && i+1<argc) file=argv[++i];
      else if(arg=="--emit" && i+1<argc) output=argv[++i];
      else if(arg=="--emit-only") emitOnly=true;
      else if(arg=="--frames" && i+1<argc) {
        std::string frames=argv[++i];
        if(std::stoi(frames)<=0) throw std::runtime_error("--frames must be positive");
#ifdef _WIN32
        _putenv_s("SIM_FRAMES",frames.c_str());
#else
        setenv("SIM_FRAMES",frames.c_str(),1);
#endif
      }
      else if(arg=="--help" || arg=="-h") {
        std::cout << "Wave32: --asm PATH --mode sim|calls|ir --frames N --emit FILE --emit-only\n"
                  << "sim = native instruction interpreter (5*), calls = LLVM + emulators (3),\n"
                  << "ir = direct instruction lowering to LLVM IR (4).\n";
        return 0;
      } else throw std::runtime_error("unrecognized option: "+arg);
    }
    if(mode!="sim" && mode!="calls" && mode!="ir") throw std::runtime_error("mode must be sim, calls or ir");
    auto program=wave32::parse(file);
    if(mode=="sim" && (emitOnly || !output.empty()))
      throw std::runtime_error("--emit/--emit-only need mode calls or ir");
    if(emitOnly && output.empty()) throw std::runtime_error("--emit-only requires --emit FILE");
    if(mode!="sim") {
      wave32::IRCompiler builder(program,mode=="calls");
      if(!output.empty()) builder.save(output);
      if(emitOnly) return 0;
      auto state=std::make_unique<wave32::State>();
      simInit();
      builder.jit(*state);
      simExit();
    } else {
      auto state=std::make_unique<wave32::State>();
      simInit();
      wave32::runSimulator(program,*state);
      simExit();
    }
    return 0;
  } catch(const std::exception &e){
    std::cerr << "asm2ir: " << e.what() << '\n';
    return 1;
  }
}
