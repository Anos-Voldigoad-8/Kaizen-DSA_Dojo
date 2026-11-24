<div align="center">

```
┌─────────────────────────────────────────────┐
│  ░██████╗██████╗ ██╗██████╗  █████╗ ██╗     │
│  ██╔════╝██╔══██╗██║██╔══██╗██╔══██╗██║     │
│  ╚█████╗ ██████╔╝██║██████╔╝███████║██║     │
│   ╚═══██╗██╔═══╝ ██║██╔══██╗██╔══██║██║     │
│  ██████╔╝██║     ██║██║  ██║██║  ██║███████╗│
│  ╚═════╝ ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝│
│        M A T R I X  ::  T R A V E R S A L   │
└─────────────────────────────────────────────┘
```

![Language](https://img.shields.io/badge/lang-C-00ffd5?style=for-the-badge&labelColor=0a0a0f)
![Time](https://img.shields.io/badge/time-O(r·c)-ff2bd6?style=for-the-badge&labelColor=0a0a0f)
![Pattern](https://img.shields.io/badge/pattern-shrinking%20boundaries-f9f002?style=for-the-badge&labelColor=0a0a0f)

**`> walk the grid. clockwise. never step twice.`**

</div>

---

## `// 00 :: OVERVIEW`

Reads a 2D matrix stored as a flat array and emits its elements in **clockwise spiral order**, starting from the top-left cell. Four boundary pointers (`top`, `bottom`, `left`, `right`) close in on the center after every pass.

```
 1   2   3   4          ┌──►──►──►──┐
 5   6   7   8    ==>   │ ┌──►──┐   ▼
 9  10  11  12          └─┤ ◄───┘   │
                          └◄──◄──◄──┘
```

## `// 01 :: ALGORITHM`

Each outer iteration peels one rectangular layer in four strokes:

| Stroke | Direction | Cells walked           | Boundary update |
|:------:|:---------:|------------------------|-----------------|
| 1 | `→` right | `top` row, `left..right`   | `top++`    |
| 2 | `↓` down  | `right` col, `top..bottom` | `right--`  |
| 3 | `←` left  | `bottom` row, `right..left`| `bottom--` |
| 4 | `↑` up    | `left` col, `bottom..top`  | `left++`   |

Loop runs while `top <= bottom && left <= right`.

> **⚠ Guard rails:** strokes 3 and 4 are re-checked (`top <= bottom`, `left <= right`) *before* running. Without these checks, a leftover single row or single column gets visited twice.

## `// 02 :: TRACE`

Input: `3 × 4` matrix holding `1..12`.

| Round | top | bottom | left | right | Emitted |
|:-----:|:---:|:------:|:----:|:-----:|---------|
| 1 | 0 | 2 | 0 | 3 | `1 2 3 4` · `8 12` · `11 10 9` · `5` |
| 2 | 1 | 1 | 1 | 2 | `6 7` (remaining strokes skipped by guards) |
| end | 2 | 0 | 2 | 1 | boundaries crossed, loop exits |

**Output**

```
1 2 3 4 8 12 11 10 9 5 6 7
```

**Visit order** (stored in the `visited[]` lane, value = step number):

```
  1   2   3   4
 10  11  12   5
  9   8   7   6
```

## `// 03 :: CONFIG`

All parameters are globals at the top of the source file.

| Variable    | Default            | Meaning                                      |
|-------------|--------------------|----------------------------------------------|
| `values`    | `{1..12}`          | Matrix flattened in row-major order          |
| `length`    | `12`               | Total cells, must equal `rows * columns`     |
| `rows`      | `3`                | Number of rows                               |
| `columns`   | `4`                | Number of columns                            |
| `bottom`    | `2`                | Must be `rows - 1`                           |
| `right`     | `3`                | Must be `columns - 1`                        |
| `top`/`left`| `0`                | Always start at `0`                          |
| `visited`   | `int[12]`          | Step number at which each cell was visited   |
| `traversal` | `int[12]`          | Values in the order they were walked         |
| `output`    | `int[512]`         | Flat output sequence                         |

> Changing the matrix size? Update `rows`, `columns`, `length`, `bottom`, `right`, and the sizes of `values[]`, `visited[]`, `traversal[]` together.

## `// 04 :: BUILD & RUN`

```bash
gcc -o spiral code.c
./spiral
```

Windows (MinGW):

```bash
gcc -o spiral.exe code.c
spiral.exe
```

## `// 05 :: COMPLEXITY`

| Resource | Cost |
|----------|------|
| Time  | `O(rows · columns)`, every cell is visited exactly once |
| Space | `O(rows · columns)`, for the `visited[]` and `traversal[]` teaching lanes (the algorithm itself needs only `O(1)` extra) |

## `// 06 :: EDGE CASES`

| Shape | Why it works |
|-------|--------------|
| Single row (`1 × n`) | Stroke 1 consumes it; `top <= bottom` guard blocks stroke 3 |
| Single column (`n × 1`) | Stroke 2 consumes it; `left <= right` guard blocks stroke 4 |
| Odd × odd square | The last round ends on the center cell exactly once |
| 1 × 1 | One step, then the boundaries cross |

## `// 07 :: LIMITATIONS`

- Fixed-size static arrays with no bounds checking.
- Matrix is hard-coded, no CLI or file input.
- Output has a trailing space and no final newline.
- Boundary variables (`bottom`, `right`) are set by hand instead of derived from `rows`/`columns`.

## `// 08 :: NEXT`

- [ ] Derive `bottom` / `right` from `rows` / `columns`
- [ ] Read the matrix from `stdin`
- [ ] Counter-clockwise and inward-to-outward variants
- [ ] Spiral matrix **generation** (fill an `n × n` grid in spiral order)

---

<div align="center">

`[ EOF ]` &nbsp;·&nbsp; MIT License

</div>
