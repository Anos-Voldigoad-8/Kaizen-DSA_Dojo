/*  DSA Practical: Graph - Adjacency Matrix + List, BFS and DFS
    Compile : gcc graph_bfs_dfs.c -o graph_bfs_dfs
    Run     : ./graph_bfs_dfs
    Vertices are 0..n-1. Neighbours are visited in increasing order. */

#include <stdio.h>
#include <stdlib.h>

#define V 10

struct Node { int v; struct Node *n; };

int g[V][V];                // adjacency matrix
struct Node *adj[V];        // adjacency list (linked lists)
int n, made, vis[V];        // vertex count, graph created?, visited flags

void rd(int *x) {           // read an int; stop cleanly on bad input / end of input
    if (scanf("%d", x) != 1) { printf("\nInvalid input. Exiting.\n"); exit(0); }
}

void freeList() {
    for (int i = 0; i < V; i++) {
        for (struct Node *p = adj[i], *t; p; p = t) { t = p->n; free(p); }
        adj[i] = NULL;
    }
}

void create() {
    int dir, ne, u, v;
    made = 0;
    printf("Number of vertices (1-%d): ", V);   rd(&n);
    if (n < 1 || n > V) { printf("Invalid number of vertices.\n"); return; }
    printf("Directed graph? (1 = yes, 0 = no): ");  rd(&dir);
    printf("Number of edges: ");                rd(&ne);

    for (u = 0; u < V * V; u++) g[u / V][u % V] = 0;       // clear matrix

    printf("Enter each edge as: u v\n");
    while (ne-- > 0) {
        rd(&u); rd(&v);
        if (u < 0 || u >= n || v < 0 || v >= n || u == v) { printf("Invalid edge ignored.\n"); continue; }
        g[u][v] = 1;
        if (!dir) g[v][u] = 1;
    }

    freeList();
    for (u = 0; u < n; u++) {               // build the list from the matrix
        struct Node **pp = &adj[u];
        for (v = 0; v < n; v++)
            if (g[u][v]) {
                *pp = malloc(sizeof(struct Node));
                (*pp)->v = v;
                (*pp)->n = NULL;
                pp = &(*pp)->n;
            }
    }
    made = 1;  printf("Graph created.\n");
}

void show() {
    printf("\nAdjacency matrix:\n  ");
    for (int j = 0; j < n; j++) printf(" %d", j);
    for (int i = 0; i < n; i++) {
        printf("\n%d :", i);
        for (int j = 0; j < n; j++) printf(" %d", g[i][j]);
    }
    printf("\n\nAdjacency list:\n");
    for (int i = 0; i < n; i++) {
        printf("%d -> ", i);
        for (struct Node *p = adj[i]; p; p = p->n) printf("%d -> ", p->v);
        printf("NULL\n");
    }
}

void report(int s) {                        // end the order line, list unreached vertices
    int any = 0;
    printf("\n");
    for (int i = 0; i < n; i++)
        if (!vis[i]) {
            if (!any++) printf("Not reachable from %d:", s);
            printf(" %d", i);
        }
    if (any) printf("\n");
}

void bfs(int s) {
    int q[V], f = 0, r = 0;
    vis[s] = 1;
    q[r++] = s;
    printf("BFS : ");
    while (f < r) {
        int u = q[f++];
        printf("%d ", u);
        for (struct Node *p = adj[u]; p; p = p->n)
            if (!vis[p->v]) { vis[p->v] = 1; q[r++] = p->v; }
    }
    report(s);
}

void dfsR(int u) {
    vis[u] = 1;
    printf("%d ", u);
    for (struct Node *p = adj[u]; p; p = p->n)
        if (!vis[p->v]) dfsR(p->v);
}

void dfsI(int s) {
    int st[V * V + 1], top = -1;
    st[++top] = s;
    printf("DFS (iterative) : ");
    while (top >= 0) {
        int u = st[top--];
        if (vis[u]) continue;               // may have been pushed twice
        vis[u] = 1;
        printf("%d ", u);
        int nb[V], k = 0;                   // push neighbours in reverse so the
        for (struct Node *p = adj[u]; p; p = p->n) nb[k++] = p->v;   // smallest pops first
        while (k-- > 0)
            if (!vis[nb[k]]) st[++top] = nb[k];
    }
    report(s);
}

int main() {
    int ch, s;
    do {
        printf("\n----- GRAPH MENU -----\n1. Create graph\n2. Show matrix and list\n");
        printf("3. BFS\n4. DFS (recursive)\n5. DFS (iterative)\n6. Exit\nEnter your choice: ");
        rd(&ch);

        if (ch >= 2 && ch <= 5 && !made) { printf("Create a graph first (option 1).\n"); continue; }

        if (ch == 1) create();
        else if (ch == 2) show();
        else if (ch >= 3 && ch <= 5) {
            printf("Enter start vertex: ");
            rd(&s);
            if (s < 0 || s >= n) { printf("Invalid start vertex.\n"); continue; }
            for (int i = 0; i < V; i++) vis[i] = 0;
            if (ch == 3) bfs(s);
            else if (ch == 4) { printf("DFS (recursive) : "); dfsR(s); report(s); }
            else dfsI(s);
        }
        else if (ch == 6) printf("Exiting program.\n");
        else printf("Invalid choice. Try again.\n");
    } while (ch != 6);

    freeList();
    return 0;
}
