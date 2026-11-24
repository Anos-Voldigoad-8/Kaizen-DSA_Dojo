<div align="center">

```
╔═══════════════════════════════════════════╗
║   E E R T R E E   ::   PALINDROMIC TREE   ║
║   every distinct palindrome. one node.    ║
╚═══════════════════════════════════════════╝
```

![Language](https://img.shields.io/badge/lang-C-00ffd5?style=for-the-badge&labelColor=0a0a0f)
![Time](https://img.shields.io/badge/time-O(n)-ff2bd6?style=for-the-badge&labelColor=0a0a0f)
![Space](https://img.shields.io/badge/space-O(128n)-f9f002?style=for-the-badge&labelColor=0a0a0f)
![Pattern](https://img.shields.io/badge/pattern-palindromic%20tree-9d4edd?style=for-the-badge&labelColor=0a0a0f)

**`> feed it a string. get back every distinct palindrome and how often it appears.`**

</div>

---

## `// 00 :: OVERVIEW`

An **Eertree** (palindromic tree) stores every **distinct palindromic substring** of a string, one node per palindrome. A string of length `n` has at most `n` distinct palindromes, so the whole structure is built online in `O(n)`.

For each distinct palindrome this program reports:

| Field | Meaning |
|-------|---------|
| `start` | Start index of its **first** occurrence (0-based) |
| `length` | Length of the palindrome |
| `count` | Total number of occurrences in the string |

## `// 01 :: STRUCTURE`

### Nodes

| Node | Meaning |
|:----:|---------|
| `0` | Imaginary root, length `-1` |
| `1` | Empty root, length `0` |
| `2..` | One node per distinct palindrome, created in order of discovery |

### Edges

An edge labeled `c` from node `P` leads to the palindrome `cPc`. The two roots make this work for both parities:

```
 root(-1) ──c──►  "c"        odd palindromes grow from here
 root( 0) ──c──►  "cc"       even palindromes grow from here
```

### Suffix links

Each node links to its **longest proper palindromic suffix**. These links are how the algorithm falls back when a palindrome can't be extended.

## `// 02 :: ALGORITHM`

For each character `s[i]`:

1. **Find the extendable suffix.** Starting from the longest palindromic suffix of the prefix so far (`last`), follow suffix links until `s[i - len - 1] == s[i]`.
2. **Look up the edge** labeled `s[i]` from that node.
3. **If it doesn't exist**, create a new node and compute its suffix link:
   - length `1` → link to the empty root
   - otherwise → walk suffix links from the parent's link to the next extendable node, then follow its `s[i]` edge
4. **Set `last`** to the (new or existing) node and add `1` to its `occurrences`.

**After construction**, propagate counts: walk nodes from newest to oldest and add each node's count into its suffix-link target. A palindrome occurrence also contains all of its palindromic suffixes, so this turns "ends here" counts into total counts.

> **⚠ Why it's linear:** each step creates at most one node, and the suffix-link walks amortize to `O(n)` overall.

## `// 03 :: TRACE`

Input: `"abacaba"` → `a b a c a b a`

### Construction

| Pos | Char | Extendable suffix | New node | Palindrome | Suffix link |
|:---:|:----:|:-----------------:|:--------:|:----------:|:-----------:|
| 0 | `a` | root(-1) | 2 | `a`       | 1 |
| 1 | `b` | root(-1) | 3 | `b`       | 1 |
| 2 | `a` | node 3   | 4 | `aba`     | 2 |
| 3 | `c` | root(-1) | 5 | `c`       | 1 |
| 4 | `a` | node 5   | 6 | `aca`     | 2 |
| 5 | `b` | node 6   | 7 | `bacab`   | 3 |
| 6 | `a` | node 7   | 8 | `abacaba` | 4 |

### Resulting tree

```
root(-1)
├─ a ► [2] "a"
├─ b ► [3] "b"
│       └─ a ► [4] "aba"
└─ c ► [5] "c"
        └─ a ► [6] "aca"
                └─ b ► [7] "bacab"
                        └─ a ► [8] "abacaba"

suffix links:  4→2   6→2   7→3   8→4   (2, 3, 5 → empty root)
```

### Count propagation

Every node is hit once during construction (`1` each). Pushing counts down suffix links gives:

| Node | Palindrome | Own | + from links | **Total** |
|:----:|:----------:|:---:|:------------:|:---------:|
| 2 | `a`       | 1 | `aca` (1) + `aba` (2) | **4** |
| 3 | `b`       | 1 | `bacab` (1)           | **2** |
| 4 | `aba`     | 1 | `abacaba` (1)         | **2** |
| 5 | `c`       | 1 | none                  | **1** |
| 6 | `aca`     | 1 | none                  | **1** |
| 7 | `bacab`   | 1 | none                  | **1** |
| 8 | `abacaba` | 1 | none                  | **1** |

### Output

Triples of `(start, length, count)`, one per node in creation order:

| Palindrome | start | length | count |
|:----------:|:-----:|:------:|:-----:|
| `a`       | 0 | 1 | 4 |
| `b`       | 1 | 1 | 2 |
| `aba`     | 0 | 3 | 2 |
| `c`       | 3 | 1 | 1 |
| `aca`     | 2 | 3 | 1 |
| `bacab`   | 1 | 5 | 1 |
| `abacaba` | 0 | 7 | 1 |

```
0 1 4 1 1 2 0 3 2 3 1 1 2 3 1 1 5 1 0 7 1
```

## `// 04 :: CONFIG`

All parameters are globals at the top of the source file.

| Variable | Default | Meaning |
|----------|---------|---------|
| `values` | `{97,98,97,99,97,98,97}` | Input string as ASCII codes (`"abacaba"`) |
| `length` | `7` | Number of characters `n` |
| `transitions` | `int[1152]` | Edge table, `128` slots per node (`9 × 128`) |
| `palindromeLength` | `int[9]` | Length per node, roots set to `-1` and `0` |
| `suffixLink` | `int[9]` | Suffix link per node |
| `firstEnd` | `int[9]` | End index of each node's first occurrence |
| `occurrences` | `int[9]` | Occurrence count per node |
| `parent` / `labels` | `int[9]` | Parent node and edge label (for tree inspection) |
| `nodeCount` | `2` | Next free node index (`0` and `1` are the roots) |
| `last` | `1` | Node of the longest palindromic suffix so far |

> **Changing the input?** With `n` characters, node arrays need `n + 2` entries and `transitions` needs `128 × (n + 2)`. Update `length`, the node arrays, and the `-1` initializers in `palindromeLength` / `firstEnd` together.

## `// 05 :: BUILD & RUN`

```bash
gcc -o eertree code.c
./eertree
```

Windows (MinGW):

```bash
gcc -o eertree.exe code.c
eertree.exe
```

## `// 06 :: COMPLEXITY`

| Resource | Cost |
|----------|------|
| Time  | `O(n)` for construction plus `O(n)` for count propagation |
| Space | `O(128 · n)`, a fixed ASCII alphabet with one transition row per node |
| Distinct palindromes | at most `n` |

## `// 07 :: LIMITATIONS`

- Alphabet is fixed to ASCII codes `0..127`.
- All arrays are statically sized for the sample input, with no bounds checking.
- Input is hard-coded, no CLI or file reading.
- `start` is the position of the **first** occurrence only.
- Output has a trailing space and no final newline.

## `// 08 :: NEXT`

- [ ] Read the string from `argv` / `stdin`
- [ ] Print palindromes as readable strings instead of triples
- [ ] Sparse transitions (map or linked list) to cut the `128n` memory
- [ ] Count **all** palindromic substrings (sum of `count`)
- [ ] Shortest/longest palindromic factorization using series links

## `// 09 :: REFERENCE`

Rubinchik, M. and Shur, A. M. *EERTREE: An Efficient Data Structure for Processing Palindromes in Strings* (2015).

---

<div align="center">

`[ EOF ]` &nbsp;·&nbsp; MIT License

</div>
