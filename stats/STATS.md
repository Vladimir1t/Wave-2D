# Частые паттерны трассы User <- Operand

Паттерн длины n - это n подряд идущих записей динамической трассы (скользящее окно с шагом 1). Доля считается от числа окон данной длины.

## Базовая трасса (операнд-phi записывается как `phi`)

Файл: `basic_ngrams.csv`, всего записей в трассе: **211 011 418**

| Окно | Окон в трассе | Разных паттернов | Доля топ-1 | Доля топ-10 |
|---:|---:|---:|---:|---:|
| 1 | 211 011 418 | 91 | 12.1% | 52.7% |
| 2 | 211 011 417 | 242 | 6.6% | 29.6% |
| 3 | 211 011 416 | 334 | 3.5% | 20.6% |
| 4 | 211 011 415 | 410 | 3.5% | 16.3% |
| 5 | 211 011 414 | 473 | 2.3% | 14.9% |

### Окно 1

| # | Количество | Доля | Паттерн |
|---:|---:|---:|---|
| 1 | 25 631 035 | 12.15% | `load <- getelementptr` |
| 2 | 16 648 432 | 7.89% | `getelementptr <- getelementptr` |
| 3 | 15 237 735 | 7.22% | `add <- load` |
| 4 | 9 814 180 | 4.65% | `getelementptr <- add` |
| 5 | 8 843 096 | 4.19% | `br <- icmp` |
| 6 | 8 558 924 | 4.06% | `icmp <- add` |
| 7 | 7 404 540 | 3.51% | `mul <- select` |
| 8 | 6 705 619 | 3.18% | `add <- mul` |
| 9 | 6 545 624 | 3.10% | `add <- phi` |
| 10 | 5 790 923 | 2.74% | `add <- shl` |
| 11 | 5 253 295 | 2.49% | `mul <- sub` |
| 12 | 5 242 880 | 2.48% | `icmp <- load` |
| 13 | 5 151 253 | 2.44% | `add <- add` |
| 14 | 5 091 708 | 2.41% | `select <- icmp` |
| 15 | 4 936 720 | 2.34% | `add <- ashr` |
| 16 | 4 936 360 | 2.34% | `sub <- add` |
| 17 | 4 496 496 | 2.13% | `call <- add` |
| 18 | 3 809 340 | 1.81% | `ashr <- sub` |
| 19 | 3 108 260 | 1.47% | `add <- or` |
| 20 | 2 931 263 | 1.39% | `trunc <- phi` |

### Окно 2

| # | Количество | Доля | Паттерн |
|---:|---:|---:|---|
| 1 | 13 957 040 | 6.61% | `getelementptr <- getelementptr`<br>`load <- getelementptr` |
| 2 | 9 385 740 | 4.45% | `add <- load`<br>`add <- load` |
| 3 | 8 105 580 | 3.84% | `load <- getelementptr`<br>`getelementptr <- getelementptr` |
| 4 | 5 364 800 | 2.54% | `getelementptr <- add`<br>`load <- getelementptr` |
| 5 | 5 242 880 | 2.48% | `icmp <- load`<br>`br <- icmp` |
| 6 | 5 145 745 | 2.44% | `br <- icmp`<br>`add <- phi` |
| 7 | 4 449 380 | 2.11% | `getelementptr <- add`<br>`getelementptr <- getelementptr` |
| 8 | 3 840 480 | 1.82% | `load <- getelementptr`<br>`load <- getelementptr` |
| 9 | 3 469 088 | 1.64% | `add <- phi`<br>`icmp <- add` |
| 10 | 3 469 088 | 1.64% | `icmp <- add`<br>`br <- icmp` |
| 11 | 3 169 755 | 1.50% | `load <- getelementptr`<br>`add <- load` |
| 12 | 3 108 260 | 1.47% | `add <- or`<br>`add <- shl` |
| 13 | 3 014 656 | 1.43% | `add <- mul`<br>`add <- mul` |
| 14 | 2 682 400 | 1.27% | `add <- phi`<br>`add <- shl` |
| 15 | 2 682 240 | 1.27% | `add <- add`<br>`add <- load` |
| 16 | 2 626 560 | 1.24% | `mul <- sub`<br>`mul <- sub` |
| 17 | 2 626 560 | 1.24% | `sub <- trunc`<br>`mul <- sub` |
| 18 | 2 626 560 | 1.24% | `trunc <- phi`<br>`sub <- trunc` |
| 19 | 2 621 560 | 1.24% | `icmp <- add`<br>`select <- icmp` |
| 20 | 2 621 440 | 1.24% | `add <- mul`<br>`icmp <- add` |

### Окно 3

| # | Количество | Доля | Паттерн |
|---:|---:|---:|---|
| 1 | 7 465 500 | 3.54% | `getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`getelementptr <- getelementptr` |
| 2 | 7 465 500 | 3.54% | `load <- getelementptr`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr` |
| 3 | 6 216 520 | 2.95% | `add <- load`<br>`add <- load`<br>`add <- load` |
| 4 | 3 840 480 | 1.82% | `getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`load <- getelementptr` |
| 5 | 3 809 300 | 1.81% | `getelementptr <- add`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr` |
| 6 | 3 469 088 | 1.64% | `add <- phi`<br>`icmp <- add`<br>`br <- icmp` |
| 7 | 3 169 220 | 1.50% | `load <- getelementptr`<br>`add <- load`<br>`add <- load` |
| 8 | 2 692 816 | 1.28% | `icmp <- add`<br>`br <- icmp`<br>`add <- phi` |
| 9 | 2 677 280 | 1.27% | `br <- icmp`<br>`add <- phi`<br>`add <- shl` |
| 10 | 2 626 560 | 1.24% | `sub <- trunc`<br>`mul <- sub`<br>`mul <- sub` |
| 11 | 2 626 560 | 1.24% | `trunc <- phi`<br>`sub <- trunc`<br>`mul <- sub` |
| 12 | 2 621 440 | 1.24% | `add <- mul`<br>`add <- mul`<br>`icmp <- add` |
| 13 | 2 621 440 | 1.24% | `add <- mul`<br>`icmp <- add`<br>`select <- icmp` |
| 14 | 2 621 440 | 1.24% | `add <- phi`<br>`add <- shl`<br>`getelementptr <- add` |
| 15 | 2 621 440 | 1.24% | `add <- shl`<br>`getelementptr <- add`<br>`load <- getelementptr` |
| 16 | 2 621 440 | 1.24% | `getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- load` |
| 17 | 2 621 440 | 1.24% | `getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- select` |
| 18 | 2 621 440 | 1.24% | `icmp <- add`<br>`select <- icmp`<br>`select <- phi` |
| 19 | 2 621 440 | 1.24% | `icmp <- select`<br>`icmp <- load`<br>`br <- icmp` |
| 20 | 2 621 440 | 1.24% | `load <- getelementptr`<br>`icmp <- load`<br>`br <- icmp` |

### Окно 4

| # | Количество | Доля | Паттерн |
|---:|---:|---:|---|
| 1 | 7 465 500 | 3.54% | `getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr` |
| 2 | 4 936 360 | 2.34% | `load <- getelementptr`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`getelementptr <- getelementptr` |
| 3 | 3 108 260 | 1.47% | `add <- load`<br>`add <- load`<br>`add <- load`<br>`add <- load` |
| 4 | 3 108 260 | 1.47% | `load <- getelementptr`<br>`add <- load`<br>`add <- load`<br>`add <- load` |
| 5 | 2 692 816 | 1.28% | `add <- phi`<br>`icmp <- add`<br>`br <- icmp`<br>`add <- phi` |
| 6 | 2 677 280 | 1.27% | `icmp <- add`<br>`br <- icmp`<br>`add <- phi`<br>`add <- shl` |
| 7 | 2 626 560 | 1.24% | `trunc <- phi`<br>`sub <- trunc`<br>`mul <- sub`<br>`mul <- sub` |
| 8 | 2 621 440 | 1.24% | `add <- mul`<br>`add <- mul`<br>`icmp <- add`<br>`select <- icmp` |
| 9 | 2 621 440 | 1.24% | `add <- mul`<br>`icmp <- add`<br>`select <- icmp`<br>`select <- phi` |
| 10 | 2 621 440 | 1.24% | `add <- phi`<br>`add <- shl`<br>`getelementptr <- add`<br>`load <- getelementptr` |
| 11 | 2 621 440 | 1.24% | `add <- shl`<br>`getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- load` |
| 12 | 2 621 440 | 1.24% | `getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- load`<br>`br <- icmp` |
| 13 | 2 621 440 | 1.24% | `getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- select`<br>`icmp <- load` |
| 14 | 2 621 440 | 1.24% | `icmp <- add`<br>`select <- icmp`<br>`select <- phi`<br>`getelementptr <- add` |
| 15 | 2 621 440 | 1.24% | `load <- getelementptr`<br>`icmp <- select`<br>`icmp <- load`<br>`br <- icmp` |
| 16 | 2 621 440 | 1.24% | `mul <- sub`<br>`add <- mul`<br>`add <- mul`<br>`icmp <- add` |
| 17 | 2 621 440 | 1.24% | `mul <- sub`<br>`mul <- sub`<br>`add <- mul`<br>`add <- mul` |
| 18 | 2 621 440 | 1.24% | `select <- icmp`<br>`select <- phi`<br>`getelementptr <- add`<br>`load <- getelementptr` |
| 19 | 2 621 440 | 1.24% | `select <- phi`<br>`getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- select` |
| 20 | 2 621 440 | 1.24% | `sub <- trunc`<br>`mul <- sub`<br>`mul <- sub`<br>`add <- mul` |

### Окно 5

| # | Количество | Доля | Паттерн |
|---:|---:|---:|---|
| 1 | 4 936 360 | 2.34% | `getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`getelementptr <- getelementptr` |
| 2 | 4 936 360 | 2.34% | `load <- getelementptr`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr` |
| 3 | 3 108 260 | 1.47% | `load <- getelementptr`<br>`add <- load`<br>`add <- load`<br>`add <- load`<br>`add <- load` |
| 4 | 2 677 280 | 1.27% | `add <- phi`<br>`icmp <- add`<br>`br <- icmp`<br>`add <- phi`<br>`add <- shl` |
| 5 | 2 621 440 | 1.24% | `add <- mul`<br>`add <- mul`<br>`icmp <- add`<br>`select <- icmp`<br>`select <- phi` |
| 6 | 2 621 440 | 1.24% | `add <- mul`<br>`icmp <- add`<br>`select <- icmp`<br>`select <- phi`<br>`getelementptr <- add` |
| 7 | 2 621 440 | 1.24% | `add <- phi`<br>`add <- shl`<br>`getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- load` |
| 8 | 2 621 440 | 1.24% | `add <- shl`<br>`getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- load`<br>`br <- icmp` |
| 9 | 2 621 440 | 1.24% | `getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- select`<br>`icmp <- load`<br>`br <- icmp` |
| 10 | 2 621 440 | 1.24% | `icmp <- add`<br>`select <- icmp`<br>`select <- phi`<br>`getelementptr <- add`<br>`load <- getelementptr` |
| 11 | 2 621 440 | 1.24% | `mul <- sub`<br>`add <- mul`<br>`add <- mul`<br>`icmp <- add`<br>`select <- icmp` |
| 12 | 2 621 440 | 1.24% | `mul <- sub`<br>`mul <- sub`<br>`add <- mul`<br>`add <- mul`<br>`icmp <- add` |
| 13 | 2 621 440 | 1.24% | `select <- icmp`<br>`select <- phi`<br>`getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- select` |
| 14 | 2 621 440 | 1.24% | `select <- phi`<br>`getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- select`<br>`icmp <- load` |
| 15 | 2 621 440 | 1.24% | `sub <- trunc`<br>`mul <- sub`<br>`mul <- sub`<br>`add <- mul`<br>`add <- mul` |
| 16 | 2 621 440 | 1.24% | `trunc <- phi`<br>`sub <- trunc`<br>`mul <- sub`<br>`mul <- sub`<br>`add <- mul` |
| 17 | 2 616 320 | 1.24% | `br <- icmp`<br>`add <- phi`<br>`add <- shl`<br>`getelementptr <- add`<br>`load <- getelementptr` |
| 18 | 2 616 320 | 1.24% | `icmp <- add`<br>`br <- icmp`<br>`add <- phi`<br>`add <- shl`<br>`getelementptr <- add` |
| 19 | 2 529 140 | 1.20% | `getelementptr <- add`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr` |
| 20 | 2 529 140 | 1.20% | `getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`add <- load` |

## Трасса с раскрытием phi (задание со звёздочкой)

Файл: `phi_ngrams.csv`, всего записей в трассе: **212 414 453**

| Окно | Окон в трассе | Разных паттернов | Доля топ-1 | Доля топ-10 |
|---:|---:|---:|---:|---:|
| 1 | 212 414 453 | 81 | 12.1% | 54.8% |
| 2 | 212 414 452 | 225 | 6.6% | 29.4% |
| 3 | 212 414 451 | 327 | 3.5% | 20.4% |
| 4 | 212 414 450 | 407 | 3.5% | 16.2% |
| 5 | 212 414 449 | 473 | 2.3% | 14.8% |

### Окно 1

| # | Количество | Доля | Паттерн |
|---:|---:|---:|---|
| 1 | 25 631 035 | 12.07% | `load <- getelementptr` |
| 2 | 16 648 432 | 7.84% | `getelementptr <- getelementptr` |
| 3 | 15 237 735 | 7.17% | `add <- load` |
| 4 | 11 696 877 | 5.51% | `add <- add` |
| 5 | 9 945 252 | 4.68% | `getelementptr <- add` |
| 6 | 8 843 096 | 4.16% | `br <- icmp` |
| 7 | 8 559 712 | 4.03% | `icmp <- add` |
| 8 | 7 404 540 | 3.49% | `mul <- select` |
| 9 | 6 705 619 | 3.16% | `add <- mul` |
| 10 | 5 790 923 | 2.73% | `add <- shl` |
| 11 | 5 253 335 | 2.47% | `mul <- sub` |
| 12 | 5 242 880 | 2.47% | `icmp <- load` |
| 13 | 5 091 708 | 2.40% | `select <- icmp` |
| 14 | 4 936 720 | 2.32% | `add <- ashr` |
| 15 | 4 936 360 | 2.32% | `sub <- add` |
| 16 | 4 496 496 | 2.12% | `call <- add` |
| 17 | 3 809 340 | 1.79% | `ashr <- sub` |
| 18 | 3 507 328 | 1.65% | `getelementptr <- alloca` |
| 19 | 3 324 479 | 1.57% | `trunc <- add` |
| 20 | 3 108 260 | 1.46% | `add <- or` |

### Окно 2

| # | Количество | Доля | Паттерн |
|---:|---:|---:|---|
| 1 | 13 957 040 | 6.57% | `getelementptr <- getelementptr`<br>`load <- getelementptr` |
| 2 | 9 385 740 | 4.42% | `add <- load`<br>`add <- load` |
| 3 | 8 105 580 | 3.82% | `load <- getelementptr`<br>`getelementptr <- getelementptr` |
| 4 | 5 364 800 | 2.53% | `getelementptr <- add`<br>`load <- getelementptr` |
| 5 | 5 242 880 | 2.47% | `icmp <- load`<br>`br <- icmp` |
| 6 | 5 145 777 | 2.42% | `br <- icmp`<br>`add <- add` |
| 7 | 4 449 380 | 2.09% | `getelementptr <- add`<br>`getelementptr <- getelementptr` |
| 8 | 3 840 480 | 1.81% | `load <- getelementptr`<br>`load <- getelementptr` |
| 9 | 3 469 124 | 1.63% | `add <- add`<br>`icmp <- add` |
| 10 | 3 469 124 | 1.63% | `icmp <- add`<br>`br <- icmp` |
| 11 | 3 169 755 | 1.49% | `load <- getelementptr`<br>`add <- load` |
| 12 | 3 108 260 | 1.46% | `add <- or`<br>`add <- shl` |
| 13 | 3 014 656 | 1.42% | `add <- mul`<br>`add <- mul` |
| 14 | 2 682 556 | 1.26% | `add <- add`<br>`add <- shl` |
| 15 | 2 682 240 | 1.26% | `add <- add`<br>`add <- load` |
| 16 | 2 626 560 | 1.24% | `mul <- sub`<br>`mul <- sub` |
| 17 | 2 626 560 | 1.24% | `sub <- trunc`<br>`mul <- sub` |
| 18 | 2 626 560 | 1.24% | `trunc <- add`<br>`sub <- trunc` |
| 19 | 2 621 560 | 1.23% | `icmp <- add`<br>`select <- icmp` |
| 20 | 2 621 440 | 1.23% | `add <- mul`<br>`icmp <- add` |

### Окно 3

| # | Количество | Доля | Паттерн |
|---:|---:|---:|---|
| 1 | 7 465 500 | 3.51% | `getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`getelementptr <- getelementptr` |
| 2 | 7 465 500 | 3.51% | `load <- getelementptr`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr` |
| 3 | 6 216 520 | 2.93% | `add <- load`<br>`add <- load`<br>`add <- load` |
| 4 | 3 840 480 | 1.81% | `getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`load <- getelementptr` |
| 5 | 3 809 300 | 1.79% | `getelementptr <- add`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr` |
| 6 | 3 469 124 | 1.63% | `add <- add`<br>`icmp <- add`<br>`br <- icmp` |
| 7 | 3 169 220 | 1.49% | `load <- getelementptr`<br>`add <- load`<br>`add <- load` |
| 8 | 2 692 848 | 1.27% | `icmp <- add`<br>`br <- icmp`<br>`add <- add` |
| 9 | 2 677 280 | 1.26% | `br <- icmp`<br>`add <- add`<br>`add <- shl` |
| 10 | 2 626 560 | 1.24% | `sub <- trunc`<br>`mul <- sub`<br>`mul <- sub` |
| 11 | 2 626 560 | 1.24% | `trunc <- add`<br>`sub <- trunc`<br>`mul <- sub` |
| 12 | 2 621 440 | 1.23% | `add <- add`<br>`add <- shl`<br>`getelementptr <- add` |
| 13 | 2 621 440 | 1.23% | `add <- mul`<br>`add <- mul`<br>`icmp <- add` |
| 14 | 2 621 440 | 1.23% | `add <- mul`<br>`icmp <- add`<br>`select <- icmp` |
| 15 | 2 621 440 | 1.23% | `add <- shl`<br>`getelementptr <- add`<br>`load <- getelementptr` |
| 16 | 2 621 440 | 1.23% | `getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- load` |
| 17 | 2 621 440 | 1.23% | `getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- select` |
| 18 | 2 621 440 | 1.23% | `icmp <- add`<br>`select <- icmp`<br>`select <- add` |
| 19 | 2 621 440 | 1.23% | `icmp <- select`<br>`icmp <- load`<br>`br <- icmp` |
| 20 | 2 621 440 | 1.23% | `load <- getelementptr`<br>`icmp <- load`<br>`br <- icmp` |

### Окно 4

| # | Количество | Доля | Паттерн |
|---:|---:|---:|---|
| 1 | 7 465 500 | 3.51% | `getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr` |
| 2 | 4 936 360 | 2.32% | `load <- getelementptr`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`getelementptr <- getelementptr` |
| 3 | 3 108 260 | 1.46% | `add <- load`<br>`add <- load`<br>`add <- load`<br>`add <- load` |
| 4 | 3 108 260 | 1.46% | `load <- getelementptr`<br>`add <- load`<br>`add <- load`<br>`add <- load` |
| 5 | 2 692 848 | 1.27% | `add <- add`<br>`icmp <- add`<br>`br <- icmp`<br>`add <- add` |
| 6 | 2 677 280 | 1.26% | `icmp <- add`<br>`br <- icmp`<br>`add <- add`<br>`add <- shl` |
| 7 | 2 626 560 | 1.24% | `trunc <- add`<br>`sub <- trunc`<br>`mul <- sub`<br>`mul <- sub` |
| 8 | 2 621 440 | 1.23% | `add <- add`<br>`add <- shl`<br>`getelementptr <- add`<br>`load <- getelementptr` |
| 9 | 2 621 440 | 1.23% | `add <- mul`<br>`add <- mul`<br>`icmp <- add`<br>`select <- icmp` |
| 10 | 2 621 440 | 1.23% | `add <- mul`<br>`icmp <- add`<br>`select <- icmp`<br>`select <- add` |
| 11 | 2 621 440 | 1.23% | `add <- shl`<br>`getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- load` |
| 12 | 2 621 440 | 1.23% | `getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- load`<br>`br <- icmp` |
| 13 | 2 621 440 | 1.23% | `getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- select`<br>`icmp <- load` |
| 14 | 2 621 440 | 1.23% | `icmp <- add`<br>`select <- icmp`<br>`select <- add`<br>`getelementptr <- add` |
| 15 | 2 621 440 | 1.23% | `load <- getelementptr`<br>`icmp <- select`<br>`icmp <- load`<br>`br <- icmp` |
| 16 | 2 621 440 | 1.23% | `mul <- sub`<br>`add <- mul`<br>`add <- mul`<br>`icmp <- add` |
| 17 | 2 621 440 | 1.23% | `mul <- sub`<br>`mul <- sub`<br>`add <- mul`<br>`add <- mul` |
| 18 | 2 621 440 | 1.23% | `select <- add`<br>`getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- select` |
| 19 | 2 621 440 | 1.23% | `select <- icmp`<br>`select <- add`<br>`getelementptr <- add`<br>`load <- getelementptr` |
| 20 | 2 621 440 | 1.23% | `sub <- trunc`<br>`mul <- sub`<br>`mul <- sub`<br>`add <- mul` |

### Окно 5

| # | Количество | Доля | Паттерн |
|---:|---:|---:|---|
| 1 | 4 936 360 | 2.32% | `getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`getelementptr <- getelementptr` |
| 2 | 4 936 360 | 2.32% | `load <- getelementptr`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr` |
| 3 | 3 108 260 | 1.46% | `load <- getelementptr`<br>`add <- load`<br>`add <- load`<br>`add <- load`<br>`add <- load` |
| 4 | 2 677 280 | 1.26% | `add <- add`<br>`icmp <- add`<br>`br <- icmp`<br>`add <- add`<br>`add <- shl` |
| 5 | 2 621 440 | 1.23% | `add <- add`<br>`add <- shl`<br>`getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- load` |
| 6 | 2 621 440 | 1.23% | `add <- mul`<br>`add <- mul`<br>`icmp <- add`<br>`select <- icmp`<br>`select <- add` |
| 7 | 2 621 440 | 1.23% | `add <- mul`<br>`icmp <- add`<br>`select <- icmp`<br>`select <- add`<br>`getelementptr <- add` |
| 8 | 2 621 440 | 1.23% | `add <- shl`<br>`getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- load`<br>`br <- icmp` |
| 9 | 2 621 440 | 1.23% | `getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- select`<br>`icmp <- load`<br>`br <- icmp` |
| 10 | 2 621 440 | 1.23% | `icmp <- add`<br>`select <- icmp`<br>`select <- add`<br>`getelementptr <- add`<br>`load <- getelementptr` |
| 11 | 2 621 440 | 1.23% | `mul <- sub`<br>`add <- mul`<br>`add <- mul`<br>`icmp <- add`<br>`select <- icmp` |
| 12 | 2 621 440 | 1.23% | `mul <- sub`<br>`mul <- sub`<br>`add <- mul`<br>`add <- mul`<br>`icmp <- add` |
| 13 | 2 621 440 | 1.23% | `select <- add`<br>`getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- select`<br>`icmp <- load` |
| 14 | 2 621 440 | 1.23% | `select <- icmp`<br>`select <- add`<br>`getelementptr <- add`<br>`load <- getelementptr`<br>`icmp <- select` |
| 15 | 2 621 440 | 1.23% | `sub <- trunc`<br>`mul <- sub`<br>`mul <- sub`<br>`add <- mul`<br>`add <- mul` |
| 16 | 2 621 440 | 1.23% | `trunc <- add`<br>`sub <- trunc`<br>`mul <- sub`<br>`mul <- sub`<br>`add <- mul` |
| 17 | 2 616 320 | 1.23% | `br <- icmp`<br>`add <- add`<br>`add <- shl`<br>`getelementptr <- add`<br>`load <- getelementptr` |
| 18 | 2 616 320 | 1.23% | `icmp <- add`<br>`br <- icmp`<br>`add <- add`<br>`add <- shl`<br>`getelementptr <- add` |
| 19 | 2 529 140 | 1.19% | `getelementptr <- add`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr` |
| 20 | 2 529 140 | 1.19% | `getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`getelementptr <- getelementptr`<br>`load <- getelementptr`<br>`add <- load` |

