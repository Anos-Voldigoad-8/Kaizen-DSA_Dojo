<div align="center">

```
╔══════════════════════════════════════════════╗
║   H E A P   S O R T                          ║
║   build the heap. pull the max. repeat.      ║
╚══════════════════════════════════════════════╝
```

![Language](https://img.shields.io/badge/lang-C-00ffd5?style=for-the-badge&labelColor=0a0a0f)
![Time](https://img.shields.io/badge/time-O(n%20log%20n)-ff2bd6?style=for-the-badge&labelColor=0a0a0f)
![Space](https://img.shields.io/badge/space-in--place-f9f002?style=for-the-badge&labelColor=0a0a0f)
![Mode](https://img.shields.io/badge/mode-interactive-9d4edd?style=for-the-badge&labelColor=0a0a0f)

**`> max-heap in. sorted array out. no extra buffer.`**

</div>

---

## `// 00 :: OVERVIEW`

**Heap sort** turns the array itself into a **max-heap**, where every parent is at least as large as its children, so the largest element sits at `a[0]`. It then repeatedly swaps that maximum to the end of the array, shrinks the heap by one, and restores the heap property. The array ends up sorted **ascending**, with no auxiliary array.

## `// 01 :: INDEXING`

The heap lives directly inside the array. For a node at index `i`:

| Relation | Index |
|----------|:-----:|
| Left child  | `2i + 1` |
| Right child | `2i + 2` |
| Last non-leaf node | `n/2 − 1` |

```
 index:   0   1   2   3   4   5   6
 value:  10   5   8   4   1   3   2

                10
              /    \
             5      8
            / \    / \
           4   1  3   2
```

## `// 02 :: ALGORITHM`

### `heapify(a, n, i)`

Sifts `a[i]` down until the subtree rooted at `i` is a max-heap (heap size = `n`):

1. Find the largest among `a[i]`, its left child and its right child (children must be `< n`).
2. If a child is larger, swap with it and recurse into that child's subtree.

### `heapSort(a, n)`

| Phase | Action |
|-------|--------|
| **1. Build** | Call `heapify` on every non-leaf, from `n/2 − 1` **down to** `0`. Bottom-up building is `O(n)` |
| **2. Extract** | For `i = n−1 … 1`: swap `a[0]` with `a[i]`, then `heapify(a, i, 0)` on the shrunken heap |

> **⚠ Why `heapify(a, i, 0)`:** after the swap, positions `i..n−1` are the sorted tail. Passing `i` as the heap size keeps `heapify` from touching them.

## `// 03 :: TRACE`

Input: `4 10 3 5 1 8 2`

### Phase 1: build the max-heap

| Step | Node `i` | Action | Array |
|:----:|:--------:|--------|-------|
| start | | | `4 10 3 5 1 8 2` |
| 1 | 2 | `3` swaps with larger child `8` | `4 10 8 5 1 3 2` |
| 2 | 1 | `10` already ≥ children | `4 10 8 5 1 3 2` |
| 3 | 0 | `4` swaps with `10`, then with `5` | `10 5 8 4 1 3 2` |

### Phase 2: extract the maximum

`|` marks the boundary between the heap (left) and the sorted tail (right).

| Pass | Swap | After re-heapify |
|:----:|------|------------------|
| 1 | `10 ↔ 2` | `8 5 3 4 1 2 \| 10` |
| 2 | `8 ↔ 2`  | `5 4 3 2 1 \| 8 10` |
| 3 | `5 ↔ 1`  | `4 2 3 1 \| 5 8 10` |
| 4 | `4 ↔ 1`  | `3 2 1 \| 4 5 8 10` |
| 5 | `3 ↔ 1`  | `2 1 \| 3 4 5 8 10` |
| 6 | `2 ↔ 1`  | `1 \| 2 3 4 5 8 10` |

### Sample run

```
Enter number of elements: 7
Enter elements: 4 10 3 5 1 8 2
Max-heap built : 10 5 8 4 1 3 2
Sorted array   : 1 2 3 4 5 8 10
```

## `// 04 :: CONFIG`

| Item | Value | Meaning |
|------|-------|---------|
| `a[100]` | 100 ints | Input buffer, so `n` must be **≤ 100** |
| `n` | read from `stdin` | Number of elements |
| `heapify` | recursive | Sift-down on a heap of size `n` |
| `display` | helper | Prints the array on one line |

## `// 05 :: BUILD & RUN`

```bash
gcc -o heap_sort code.c
./heap_sort
```

Windows (MinGW):

```bash
gcc -o heap_sort.exe code.c
heap_sort.exe
```

Then enter the element count, followed by the elements.

## `// 06 :: COMPLEXITY`

| Case | Time |
|------|------|
| Best | `O(n log n)` |
| Average | `O(n log n)` |
| Worst | `O(n log n)` |
| Build-heap phase | `O(n)` |

| Property | Value |
|----------|-------|
| Space | `O(1)` auxiliary, plus `O(log n)` recursion stack for `heapify` |
| In-place | Yes |
| Stable | **No**, since swaps can reorder equal keys |

## `// 07 :: LIMITATIONS`

- Fixed buffer of **100** elements, with no check that `n ≤ 100`.
- `scanf` return values aren't checked, so bad input leaves values undefined.
- Sorts **ascending** only. For descending, build a **min-heap** (flip the comparisons in `heapify`).
- Recursive `heapify` could be written iteratively to avoid the stack use.

## `// 08 :: NEXT`

- [ ] Iterative `heapify`
- [ ] Min-heap variant for descending order
- [ ] Input validation for `n` and `scanf`
- [ ] Print the heap after every pass
- [ ] Compare against merge sort and quick sort on large inputs

---

<div align="center">

`[ EOF ]` &nbsp;·&nbsp; MIT License

</div>
