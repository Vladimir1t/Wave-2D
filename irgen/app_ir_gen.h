#ifndef APP_IR_GEN_H
#define APP_IR_GEN_H

namespace llvm {
class Function;
class Module;
} // namespace llvm

// Строит в модуле M функции логического модуля app.c (те, что вызываются
// при исполнении) и возвращает @app. Реализация сгенерирована ir2cpp.
llvm::Function *generateApp(llvm::Module &M);

#endif // APP_IR_GEN_H
