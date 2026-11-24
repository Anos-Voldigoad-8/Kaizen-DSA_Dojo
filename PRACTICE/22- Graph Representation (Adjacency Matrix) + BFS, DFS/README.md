<div align="center">

```
╔══════════════════════════════════════════════╗
║   G R A P H   ::   B F S  +  D F S           ║
║   adjacency matrix. two ways to explore.     ║
║   wide first.  deep first.                   ║
╚══════════════════════════════════════════════╝
```

![Language](https://img.shields.io/badge/lang-C-00ffd5?style=for-the-badge&labelColor=0a0a0f)
![Storage](https://img.shields.io/badge/storage-adjacency%20matrix-ff2bd6?style=for-the-badge&labelColor=0a0a0f)
![Traversals](https://img.shields.io/badge/traversals-BFS%20%2B%20DFS-f9f002?style=for-the-badge&labelColor=0a0a0f)
![Mode](https://img.shields.io/badge/mode-interactive-9d4edd?style=for-the-badge&labelColor=0a0a0f)

**`> store the graph as a grid. visit every vertex. two strategies.`**

</div>

---

## `// 00 :: OVERVIEW`

This program stores an **undirected graph** as an **adjacency matrix** and traverses it from a chosen start vertex using both classic strategies:

| | **BFS** (breadth-first) | **DFS** (depth-first) |
|---|------------------------|-----------------------|
| Explores | level by level, nearest vertices first | as deep as possible, then backtracks |
| Helper structure | **queue** (`q[]`) | **recursion stack** (call stack) |
| Good for | shortest path in unweighted graphs | cycle detection, connectivity, topological ideas |
| Output order | by distance from start | by path depth |

## `// 01 :: REPRESENTATION`

`adj[u][v] = 1` means an edge exists between `u` and `v`. The graph is undirected, so `addEdge` writes **both** `adj[u][v]` and `adj[v][u]` and the matrix is always symmetric.

```
 edge (0,1)  ──►  adj[0][1] = 1
                  adj[1][0] = 1
```

| Property | Value |
|----------|-------|
| Space | `O(V²)` regardless of edge count |
| Edge lookup | `O(1)` |
| List all neighbours of `u` | `O(V)` (scan row `u`) |
| Neighbour order | **ascending vertex number**, because each row is scanned `0 → nV−1` |

## `// 02 :: ALGORITHMS`

### BFS `bfs(start)`

1. Clear `visited[]`, mark `start` visited and push it into the queue.
2. Pop the front vertex `u` and print it.
3. For every unvisited neighbour `v` of `u`, mark it visited **when enqueued** and push it.
4. Repeat until the queue is empty.

### DFS `dfs(start)` → `dfsUtil(u)`

1. Clear `visited[]`.
2. In `dfsUtil(u)`: mark `u` visited and print it.
3. For each unvisited neighbour `v` (ascending), recurse into `dfsUtil(v)`.
4. When all neighbours are done, the call returns, which is the backtrack.

> **⚠ Mark early:** BFS marks a vertex visited at **enqueue** time, not at pop time. This is what stops a vertex from being queued twice, so the queue never needs more than `V` slots.

## `// 03 :: TRACE`

### Sample graph

6 vertices, 7 edges:

```
    (0)─────(1)─────(3)
     │       │       │
     │       │       │
    (2)─────(4)─────(5)
```

Edges: `0-1  0-2  1-3  1-4  2-4  3-5  4-5`

### Adjacency matrix

```
      0  1  2  3  4  5
  0 [ 0  1  1  0  0  0 ]
  1 [ 1  0  0  1  1  0 ]
  2 [ 1  0  0  0  1  0 ]
  3 [ 0  1  0  0  0  1 ]
  4 [ 0  1  1  0  0  1 ]
  5 [ 0  0  0  1  1  0 ]
```

### BFS from `0`

| Step | Pop | Newly queued | Queue after |
|:----:|:---:|:------------:|:-----------:|
| 1 | `0` | `1`, `2` | `[1, 2]` |
| 2 | `1` | `3`, `4` | `[2, 3, 4]` |
| 3 | `2` | none (`0`, `4` already seen) | `[3, 4]` |
| 4 | `3` | `5` | `[4, 5]` |
| 5 | `4` | none | `[5]` |
| 6 | `5` | none | `[]` |

### DFS from `0`

```
 visit 0
 └─ visit 1                 (first unvisited neighbour of 0)
    └─ visit 3              (first unvisited neighbour of 1)
       └─ visit 5
          └─ visit 4
             └─ visit 2     (neighbours 0 and 4 already seen)
             ◄── backtrack all the way up
```

### Sample run

```
Enter number of vertices: 6
Enter number of edges: 7
Enter edges (u v):
0 1
0 2
1 3
1 4
2 4
3 5
4 5
Enter starting vertex for traversal: 0
BFS: 0 1 2 3 4 5
DFS: 0 1 3 5 4 2
```

> Same graph, different order. BFS fans out by distance from `0`, while DFS dives `0 → 1 → 3 → 5 → 4 → 2` before it ever returns.

## `// 04 :: CONFIG`

| Item | Value | Meaning |
|------|-------|---------|
| `MAX` | `10` | Maximum number of vertices |
| `adj[MAX][MAX]` | matrix | Adjacency matrix, zeroed in `main` |
| `visited[MAX]` | array | Reset at the start of every traversal |
| `nV` | read from `stdin` | Number of vertices |
| `q[MAX]` | local to `bfs` | Queue with `front` / `rear` indices |

> Need a bigger graph? Raise `MAX`. Vertices are numbered `0 .. nV−1`.

## `// 05 :: BUILD & RUN`

```bash
gcc -o graph code.c
./graph
```

Windows (MinGW):

```bash
gcc -o graph.exe code.c
graph.exe
```

Enter the vertex count, the edge count, each edge as `u v`, then the start vertex.

## `// 06 :: COMPLEXITY`

| Algorithm | Time | Extra space |
|-----------|------|-------------|
| **BFS** | `O(V²)` | `O(V)` queue + `visited[]` |
| **DFS** | `O(V²)` | `O(V)` recursion depth + `visited[]` |

Both scan a full matrix row for every vertex they visit. With an **adjacency list** this drops to `O(V + E)`.

## `// 07 :: LIMITATIONS`

- Maximum of **10 vertices**, and `nV` is not checked against `MAX`.
- **No validation** of edge endpoints or the start vertex, so a value outside `0 .. nV−1` writes out of bounds.
- Only the **connected component** containing the start vertex is traversed. Vertices in other components are never printed.
- Undirected and unweighted only.
- Self-loops and duplicate edges are accepted silently (duplicates have no effect).
- `scanf` return values aren't checked.

## `// 08 :: NEXT`

- [ ] Validate `nV`, edge endpoints and the start vertex
- [ ] Traverse **all** components (loop over unvisited vertices)
- [ ] Adjacency-list version (`O(V + E)`)
- [ ] BFS shortest-path distances and parent array
- [ ] Cycle detection and connected-component count with DFS
- [ ] Directed-graph option

---

<div align="center">

`[ EOF ]` &nbsp;·&nbsp; MIT License

</div>
