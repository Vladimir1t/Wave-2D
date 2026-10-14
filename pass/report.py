#!/usr/bin/env python3
"""Строит отчёт по частым паттернам трассы User <- Operand.

Вход: CSV-файлы <prefix>_ngrams.csv, которые пишет trace_log.c
(n;count;pattern, паттерн - записи трассы через " | ").
Выход: Markdown с топом паттернов для каждой длины окна 1..5.

    python3 pass/report.py stats/basic_ngrams.csv stats/phi_ngrams.csv \
        --top 20 -o stats/STATS.md
"""
import argparse
import collections
import os

TITLES = {
    "basic": "Базовая трасса (операнд-phi записывается как `phi`)",
    "phi": "Трасса с раскрытием phi (задание со звёздочкой)",
}


def load(path):
    total = None
    by_n = collections.defaultdict(list)
    with open(path) as f:
        for line in f:
            line = line.rstrip("\n")
            if line.startswith("# total_records="):
                total = int(line.split("=", 1)[1])
                continue
            if not line or line.startswith("#") or line.startswith("n;"):
                continue
            n, count, pattern = line.split(";", 2)
            by_n[int(n)].append((int(count), pattern))
    for rows in by_n.values():
        rows.sort(key=lambda r: (-r[0], r[1]))
    return total, by_n


def num(x):
    return f"{x:,}".replace(",", "\u00a0")


def coverage(rows, k):
    all_ = sum(c for c, _ in rows)
    return 100.0 * sum(c for c, _ in rows[:k]) / all_ if all_ else 0.0


def section(path, top):
    name = os.path.basename(path).replace("_ngrams.csv", "")
    total, by_n = load(path)
    out = [f"## {TITLES.get(name, name)}", ""]
    out.append(f"Файл: `{os.path.basename(path)}`, всего записей в трассе: "
               f"**{num(total)}**")
    out.append("")
    out.append("| Окно | Окон в трассе | Разных паттернов | Доля топ-1 | Доля топ-10 |")
    out.append("|---:|---:|---:|---:|---:|")
    for n in sorted(by_n):
        rows = by_n[n]
        windows = sum(c for c, _ in rows)
        out.append(f"| {n} | {num(windows)} | {len(rows)} | {coverage(rows, 1):.1f}% | "
                   f"{coverage(rows, 10):.1f}% |")
    out.append("")
    for n in sorted(by_n):
        rows = by_n[n]
        windows = sum(c for c, _ in rows)
        out.append(f"### Окно {n}")
        out.append("")
        out.append("| # | Количество | Доля | Паттерн |")
        out.append("|---:|---:|---:|---|")
        for i, (count, pattern) in enumerate(rows[:top], 1):
            cells = "<br>".join(f"`{p}`" for p in pattern.split(" | "))
            out.append(f"| {i} | {num(count)} | {100.0 * count / windows:.2f}% | {cells} |")
        out.append("")
    return "\n".join(out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("csv", nargs="+")
    ap.add_argument("--top", type=int, default=20)
    ap.add_argument("-o", "--output", required=True)
    args = ap.parse_args()
    parts = ["# Частые паттерны трассы User <- Operand", "",
             "Паттерн длины n - это n подряд идущих записей динамической трассы "
             "(скользящее окно с шагом 1). Доля считается от числа окон данной длины.",
             ""]
    parts += [section(p, args.top) for p in args.csv]
    with open(args.output, "w") as f:
        f.write("\n".join(parts) + "\n")


if __name__ == "__main__":
    main()
