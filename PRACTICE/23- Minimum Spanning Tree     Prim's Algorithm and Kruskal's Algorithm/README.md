<div align="center">

```
╔══════════════════════════════════════════════╗
║   M I N I M U M   S P A N N I N G   T R E E  ║
║   PRIM  ◄──────────────────►  KRUSKAL        ║
║   connect everything. spend the least.       ║
╚══════════════════════════════════════════════╝
```

![Language](https://img.shields.io/badge/lang-C-00ffd5?style=for-the-badge&labelColor=0a0a0f)
![Strategy](https://img.shields.io/badge/strategy-greedy-ff2bd6?style=for-the-badge&labelColor=0a0a0f)
![Algorithms](https://img.shields.io/badge/algorithms-Prim%20%2B%20Kruskal-f9f002?style=for-the-badge&labelColor=0a0a0f)
![Mode](https://img.shields.io/badge/mode-interactive-9d4edd?style=for-the-badge&labelColor=0a0a0f)

**`> two greedy strategies. one graph. same total weight.`**

</div>

---

## `// 00 :: OVERVIEW`

A **minimum spanning tree (MST)** of a connected, undirected, weighted graph is a subset of edges that:

- connects **all** vertices,
- contains **no cycles** (so exactly `n − 1` edges),
- has the **smallest possible total weight**.

This program reads one graph and runs both classic algorithms on it, so their outputs can be compared side by side.

| | **Prim** | **Kruskal** |
|---|----------|-------------|
| Grows | a single tree outward from a start vertex | a forest of components that merge over time |
| Picks | cheapest edge leaving the tree | globally cheapest edge that doesn't form a cycle |
| Needs | adjacency matrix + `key[]` / `from[]` arrays | sorted edge list + union-find |
| Cycle check | vertex already in tree? | `find(u) == find(v)`? |

## `// 01 :: INPUT FORMAT`

```
Enter number of vertices (max 10): n
Enter number of edges: ne
Enter each edge as: u v weight        (repeated ne times)
```

| Rule | Behavior |
|------|----------|
| Vertices | numbered `0 .. n−1`, with `1 ≤ n ≤ 10` |
| Weights | must be **positive** (`> 0`), because `0` means "no edge" in the matrix |
| Graph type | undirected, so each edge is stored in both `g[u][v]` and `g[v][u]` |
| Bad edge | out-of-range vertex, self-loop, or `w ≤ 0` prints `Invalid edge ignored.` |
| Repeated edge | the **cheapest** weight is kept |

## `// 02 :: ALGORITHMS`

### Prim `prim(s)`

1. Set `key[v] = INF` for all vertices and `key[s] = 0`.
2. Pick the vertex `u` **not yet in the tree** with the smallest `key`. If none is reachable, stop.
3. Add `u` to the tree and print the edge `from[u] - u` (except for the start vertex).
4. For each neighbour `v` of `u` not in the tree, if `g[u][v] < key[v]`, set `key[v] = g[u][v]` and `from[v] = u`.
5. Repeat for `n` rounds.

### Kruskal `kruskal()`

1. Build the edge list from the matrix (each edge once, `i < j`).
2. **Sort** edges by weight using selection sort.
3. Make every vertex its own set: `p[i] = i`.
4. Scan edges in order. If `find(u) != find(v)`, the edge joins two components, so **take it** and union them. Otherwise it would close a cycle, so skip it.
5. Stop early once `n − 1` edges are chosen.

> **⚠ Disconnected graph:** if fewer than `n − 1` edges are found, both algorithms print `Graph is not connected: no spanning tree.` instead of a total.

## `// 03 :: TRACE`

### Sample graph

5 vertices, 7 edges:

| Edge | `0-1` | `0-3` | `1-2` | `1-3` | `1-4` | `2-4` | `3-4` |
|:----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|
| Weight | 2 | 6 | 3 | 8 | 5 | 7 | 9 |

### Prim from vertex `0`

| Round | Picked `u` | Key | Edge added | Total |
|:-----:|:----------:|:---:|:----------:|:-----:|
| 1 | `0` | 0 | start vertex, nothing printed | 0 |
| 2 | `1` | 2 | `0 - 1` | 2 |
| 3 | `2` | 3 | `1 - 2` | 5 |
| 4 | `4` | 5 | `1 - 4` | 10 |
| 5 | `3` | 6 | `0 - 3` | 16 |

### Kruskal

Edges after sorting by weight:

| # | Edge | Weight | Find roots | Decision | Total |
|:-:|:----:|:------:|:----------:|:--------:|:-----:|
| 1 | `0 - 1` | 2 | `0` vs `1` | ✅ take | 2 |
| 2 | `1 - 2` | 3 | `1` vs `2` | ✅ take | 5 |
| 3 | `1 - 4` | 5 | `2` vs `4` | ✅ take | 10 |
| 4 | `0 - 3` | 6 | `4` vs `3` | ✅ take | 16 |
| | | | | **4 = n − 1 edges, stop** | |

Edges `2-4` (7), `1-3` (8) and `3-4` (9) are never examined, since the loop exits as soon as the tree is complete.

### Resulting tree

```
      (0)───2───(1)───3───(2)
       │         │
       6         5
       │         │
      (3)       (4)

      total weight = 2 + 3 + 5 + 6 = 16
```

### Sample run

```
Enter number of vertices (max 10): 5
Enter number of edges: 7
Enter each edge as: u v weight
0 1 2
0 3 6
1 2 3
1 3 8
1 4 5
2 4 7
3 4 9

Prim's MST (start = 0):
Edge      Weight
0 - 1      2
1 - 2      3
1 - 4      5
0 - 3      6
Total weight = 16

Kruskal's MST:
Edge      Weight
0 - 1      2
1 - 2      3
1 - 4      5
0 - 3      6
Total weight = 16
```

> **Note:** both algorithms always agree on the **total weight**. The chosen **edges** can differ when the graph has equal-weight edges, since each algorithm breaks ties differently.

## `// 04 :: CONFIG`

| Item | Value | Meaning |
|------|-------|---------|
| `V` | `10` | Maximum number of vertices |
| `INF` | `99999` | "Unreachable" sentinel for Prim's `key[]` |
| `g[V][V]` | matrix | Adjacency matrix, `0` = no edge |
| `struct E e[V*V]` | edge list | `u`, `v`, `w` per edge, used by Kruskal |
| `p[V]` | parent array | Union-find forest |
| `m` | counter | Number of edges in the edge list |

> Need a bigger graph? Raise `V`. Weights must stay below `INF`.

## `// 05 :: BUILD & RUN`

```bash
gcc -o mst code.c
./mst
```

Windows (MinGW):

```bash
gcc -o mst.exe code.c
mst.exe
```

## `// 06 :: COMPLEXITY`

Let `V` be the vertex count and `E` the edge count.

| Algorithm | Time | Why |
|-----------|------|-----|
| **Prim** (matrix) | `O(V²)` | `V` rounds, each scanning `V` vertices twice |
| **Kruskal** | `O(E²)` sort + `O(E · V)` finds | selection sort, plus `find` without path compression |

| Resource | Cost |
|----------|------|
| Space | `O(V² + E)` for the matrix and edge list |

> A heap-based Prim runs in `O(E log V)`. Kruskal with a fast sort and union-by-rank plus path compression runs in `O(E log E)`. At `V ≤ 10` the simple versions are fast and easy to read.

## `// 07 :: LIMITATIONS`

- Maximum of **10 vertices**.
- Weights must be **positive integers**. Zero and negative weights are rejected.
- Selection sort is **not stable**, so equal-weight edges may be reordered.
- `find()` has no path compression or union-by-rank.
- `scanf` return values aren't checked.
- Parallel edges collapse to the cheapest one.
- Output isn't saved to a file.

## `// 08 :: NEXT`

- [ ] Heap-based Prim (`O(E log V)`)
- [ ] Replace selection sort with `qsort` or merge sort
- [ ] Add path compression and union by rank
- [ ] Read the graph from a file
- [ ] Print the MST as an adjacency list or ASCII tree
- [ ] Detect and report **all** connected components (minimum spanning forest)

---

<div align="center">

`[ EOF ]` &nbsp;·&nbsp; MIT License

</div>
