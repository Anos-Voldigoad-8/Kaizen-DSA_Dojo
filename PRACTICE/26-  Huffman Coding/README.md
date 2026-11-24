<div align="center">

```
╔══════════════════════════════════════════════╗
║   H U F F M A N   C O D I N G                ║
║   frequent = short.  rare = long.            ║
║   no code is a prefix of another.            ║
╚══════════════════════════════════════════════╝
```

![Language](https://img.shields.io/badge/lang-C-00ffd5?style=for-the-badge&labelColor=0a0a0f)
![Strategy](https://img.shields.io/badge/strategy-greedy-ff2bd6?style=for-the-badge&labelColor=0a0a0f)
![Codes](https://img.shields.io/badge/codes-prefix--free-f9f002?style=for-the-badge&labelColor=0a0a0f)
![Mode](https://img.shields.io/badge/mode-interactive-9d4edd?style=for-the-badge&labelColor=0a0a0f)

**`> count the symbols. merge the weakest two. repeat until one tree remains.`**

</div>

---

## `// 00 :: OVERVIEW`

**Huffman coding** is a lossless compression scheme that assigns variable-length binary codes to characters based on how often they occur:

- Frequent characters sit near the root and get **short** codes
- Rare characters sit deep in the tree and get **long** codes
- No code is a prefix of another, so the bit stream decodes **unambiguously**

This program reads a line of text, builds the Huffman tree, prints the code table, then **encodes** the text, **decodes** it back by walking the tree bit by bit, and compares the sizes.

## `// 01 :: PIPELINE`

```
  text ──► frequency count ──► one leaf per symbol
                                      │
                         merge two smallest, repeat
                                      ▼
  decode ◄── bit string ◄── encode ◄── code table ◄── tree walk
```

| Stage | What happens |
|-------|--------------|
| **Count** | `fr[c]++` for every character of the input |
| **Leaves** | One node per distinct character, created in ASCII order |
| **Merge** | Repeatedly take the two smallest alive nodes, kill them, and create a parent with their summed frequency |
| **Codes** | Walk from the root: left edge = `0`, right edge = `1`. The path to each leaf is its code |
| **Encode** | Concatenate each character's code |
| **Decode** | Follow `0`/`1` edges from the root, emit a character at every leaf, reset to the root |

> **⚠ Ties:** `pickMin()` uses a strict `<` over the node array, so equal frequencies are resolved in favor of the **earlier index**. This makes the output deterministic.

## `// 02 :: TRACE`

Input: `abracadabra` (11 characters)

### Frequencies

| Char | `a` | `b` | `r` | `c` | `d` |
|:----:|:---:|:---:|:---:|:---:|:---:|
| Freq | 5 | 2 | 2 | 1 | 1 |

Leaves are created in ASCII order: `0:a(5)`, `1:b(2)`, `2:c(1)`, `3:d(1)`, `4:r(2)`.

### Merges

| Step | Picked | New node | Freq |
|:----:|--------|:--------:|:----:|
| 1 | `c(1)` + `d(1)` | 5 | 2 |
| 2 | `b(2)` + `r(2)` (earlier index wins the tie over node 5) | 6 | 4 |
| 3 | node 5 `(2)` + node 6 `(4)` | 7 | 6 |
| 4 | `a(5)` + node 7 `(6)` | 8 (root) | 11 |

### Resulting tree

```
                [11]
               0/    \1
            a(5)      [6]
                    0/    \1
                  [2]      [4]
                 0/  \1   0/  \1
               c(1) d(1) b(2) r(2)
```

### Sample run

```
Enter text (max 100 characters): abracadabra

Char   Freq   Code
a      5      0
b      2      110
c      1      100
d      1      101
r      2      111

Encoded : 01101110100010101101110
Decoded : abracadabra

Original size : 88 bits (8 bits per character)
Encoded size  : 23 bits
```

### Size check

```
encoded bits = 5·1 + 2·3 + 1·3 + 1·3 + 2·3 = 23
original     = 11 · 8 = 88
saved        = 65 bits  (≈ 73.9%)
```

## `// 03 :: SPECIAL CASES`

| Case | Behavior |
|------|----------|
| Empty input | Prints `Empty text.` and exits |
| One distinct symbol (e.g. `aaaa`) | Root is a leaf, so it gets the code `0` (1 bit per character) and the decoder handles it separately |
| Spaces | Shown as `space` in the code table |
| Frequency ties | Resolved by earlier node index, see the note above |

## `// 04 :: CONFIG`

| Item | Value | Meaning |
|------|-------|---------|
| `MAXN` | `512` | Node capacity: up to 256 leaves + 255 internal nodes |
| `txt[101]` | 100 chars max | Input buffer, read with `fgets` |
| `code[256][64]` | 64 chars per code | Code string per character |
| `t[]` | struct `H` | Tree nodes: `f` frequency, `ch` char, `l`/`r` children (`-1` for a leaf), `alive` flag |
| `m` | counter | Number of nodes created so far |
| `root` | index | Root of the finished tree |

## `// 05 :: BUILD & RUN`

```bash
gcc -o huffman code.c
./huffman
```

Windows (MinGW):

```bash
gcc -o huffman.exe code.c
huffman.exe
```

Then type a line of text and press Enter.

## `// 06 :: COMPLEXITY`

Let `n` be the text length and `k` the number of distinct characters (`k ≤ 256`).

| Stage | Time |
|-------|------|
| Frequency count | `O(n)` |
| Tree build | `O(k²)`, because `pickMin()` does a linear scan on each of the `k − 1` merges |
| Code generation | `O(k · depth)` |
| Encode / decode | `O(total encoded bits)` |

| Resource | Cost |
|----------|------|
| Space | `O(MAXN + 256 · 64)`, static arrays |

> A min-heap would bring the build down to `O(k log k)`. At `k ≤ 256` the simple scan is fast enough and much easier to read.

## `// 07 :: LIMITATIONS`

- Input is limited to **100 characters** and one line.
- The decoder replays the codes produced from the input text, so it works as a **round-trip check** rather than decoding a separately stored bit stream.
- The tree or code table isn't serialized, so the reported encoded size **excludes** the table overhead a real compressor would need to store.
- Several valid Huffman trees can exist for the same frequencies. The tie-break rule picks one, but the **total bit count** is the same for all of them.
- Bits are printed as `'0'`/`'1'` characters, not packed into bytes.

## `// 08 :: NEXT`

- [ ] Replace the linear `pickMin()` with a min-heap
- [ ] Pack the encoded bits into real bytes and write them to a file
- [ ] Store and read back the tree so a file can be decompressed on its own
- [ ] Canonical Huffman codes (deterministic, compact table)
- [ ] Print the compression ratio and average bits per symbol

---

<div align="center">

`[ EOF ]` &nbsp;·&nbsp; MIT License

</div>
