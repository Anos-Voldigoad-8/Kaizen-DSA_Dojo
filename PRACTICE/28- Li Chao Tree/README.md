<div align="center">

```
╔══════════════════════════════════════╗
║   L I   C H A O   T R E E            ║
║   minimum of inserted lines at x     ║
╚══════════════════════════════════════╝
```

![Language](https://img.shields.io/badge/lang-C-00ffd5?style=for-the-badge&labelColor=0a0a0f)
![Insert/Query](https://img.shields.io/badge/insert%20%2F%20query-O(log%20U)-ff2bd6?style=for-the-badge&labelColor=0a0a0f)
![Pattern](https://img.shields.io/badge/pattern-convex%20hull%20trick-f9f002?style=for-the-badge&labelColor=0a0a0f)

**`> throw lines in. ask for the lowest point. get an answer in log time.`**

</div>

---

## `// 00 :: OVERVIEW`

A **Li Chao Tree** stores a set of lines `y = m·x + b` and answers one question fast: *what is the minimum value over all inserted lines at a given x?*

It is a segment tree over the x-domain where **each node keeps exactly one line**, the one that wins at that node's midpoint. A line that loses at the midpoint can still win on at most one side, so it is pushed down into a single child. No hull maintenance and no sorting of slopes are needed.

```
 y
 │ \         /  L0 : y = 2x + 3
 │  \   ___ /   L1 : y = -x + 5
 │   \_/   /    L2 : y = 1
 │ ───┴────┴──  lower envelope = what the tree answers
 └──────────────── x
```

## `// 01 :: DOMAIN`

| Item | Value |
|------|-------|
| Integer x-domain | `[-16, 16]` |
| Internal positions | `0..32` (shifted by `+16`) |
| Universe size `U` | `33` |
| Line evaluation | `slope * (position - 16) + intercept` |
| Empty-node sentinel | `1000000` (returned when a child doesn't exist) |

Queries take `x`, shift it to `x + 16`, and descend from the root `[0, 32]`.

## `// 02 :: ALGORITHM`

### Insert `insertLine(node, low, high, incoming)`

1. If the node is empty, store the line and stop.
2. Compare `incoming` against the stored line at `low` and at `middle`.
3. If `incoming` wins at `middle`, **swap** it with the stored line.
4. If `low == high`, stop.
5. The loser is better on at most one side:
   - `betterLeft != betterMiddle` → push the loser into the **left** child `[low, middle]`
   - otherwise
