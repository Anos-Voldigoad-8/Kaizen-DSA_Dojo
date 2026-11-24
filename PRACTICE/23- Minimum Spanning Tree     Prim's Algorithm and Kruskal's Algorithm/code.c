/*
    DSA Practical: Minimum Spanning Tree
    Prim's Algorithm and Kruskal's Algorithm
    ----------------------------------------------------
    Compile : gcc mst_prim_kruskal.c -o mst_prim_kruskal
    Run     : ./mst_prim_kruskal
    Input   : undirected weighted graph, vertices numbered 0 .. n-1,
              weights must be positive.
*/

#include <stdio.h>

#define V   10
#define INF 99999

int g[V][V];            // adjacency matrix (0 = no edge)
int n;                  // number of vertices

struct E { int u, v, w; } e[V * V];
int m = 0;              // number of edges in edge list

int p[V];               // parent array for union-find

// -------------------- PRIM'S --------------------
void prim(int s) {
    int in[V] = {0};            // vertex already in the tree?
    int k[V];                   // cheapest edge weight connecting vertex to tree
    int f[V];                   // vertex on the tree that gives that cheapest edge
    int tot = 0, cnt = 0;

    for (int i = 0; i < n; i++) { k[i] = INF; f[i] = -1; }
    k[s] = 0;

    printf("\nPrim's MST (start = %d):\n", s);
    printf("Edge      Weight\n");

    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++)                 // pick cheapest vertex not yet in tree
            if (!in[j] && k[j] < INF && (u == -1 || k[j] < k[u])) u = j;

        if (u == -1) break;                         // remaining vertices unreachable

        in[u] = 1;
        if (f[u] != -1) {
            printf("%d - %d      %d\n", f[u], u, k[u]);
            tot += k[u];
            cnt++;
        }

        for (int v = 0; v < n; v++)                 // update neighbours of u
            if (g[u][v] && !in[v] && g[u][v] < k[v]) {
                k[v] = g[u][v];
                f[v] = u;
            }
    }

    if (cnt < n - 1) printf("Graph is not connected: no spanning tree.\n");
    else             printf("Total weight = %d\n", tot);
}

// -------------------- KRUSKAL'S --------------------
int fnd(int x) {
    while (p[x] != x) x = p[x];
    return x;
}

void kruskal() {
    int tot = 0, cnt = 0;

    // sort edges by weight (selection sort)
    for (int i = 0; i < m - 1; i++) {
        int mn = i;
        for (int j = i + 1; j < m; j++)
            if (e[j].w < e[mn].w) mn = j;
        struct E t = e[i]; e[i] = e[mn]; e[mn] = t;
    }

    for (int i = 0; i < n; i++) p[i] = i;

    printf("\nKruskal's MST:\n");
    printf("Edge      Weight\n");

    for (int i = 0; i < m && cnt < n - 1; i++) {
        int a = fnd(e[i].u);
        int b = fnd(e[i].v);
        if (a != b) {                               // different sets: no cycle
            p[a] = b;
            printf("%d - %d      %d\n", e[i].u, e[i].v, e[i].w);
            tot += e[i].w;
            cnt++;
        }
    }

    if (cnt < n - 1) printf("Graph is not connected: no spanning tree.\n");
    else             printf("Total weight = %d\n", tot);
}

// -------------------- MAIN --------------------
int main() {
    int ne, u, v, w;

    printf("Enter number of vertices (max %d): ", V);
    scanf("%d", &n);
    if (n < 1 || n > V) {
        printf("Invalid number of vertices.\n");
        return 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &ne);

    printf("Enter each edge as: u v weight\n");
    for (int i = 0; i < ne; i++) {
        scanf("%d %d %d", &u, &v, &w);
        if (u < 0 || u >= n || v < 0 || v >= n || u == v || w <= 0) {
            printf("Invalid edge ignored.\n");
            continue;
        }
        if (g[u][v] == 0 || w < g[u][v]) {          // keep cheapest if repeated
            g[u][v] = w;
            g[v][u] = w;
        }
    }

    // build edge list from the matrix (each edge once)
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (g[i][j]) {
                e[m].u = i; e[m].v = j; e[m].w = g[i][j];
                m++;
            }

    prim(0);
    kruskal();

    return 0;
}