/*
    DSA Practical: Huffman Coding
    ----------------------------------------------------
    Compile : gcc huffman_coding.c -o huffman_coding
    Run     : ./huffman_coding
    Idea    : count how often each character occurs, then repeatedly
              merge the two least-frequent nodes into one. Frequent
              characters end up near the root (short codes), rare ones
              deep in the tree (long codes). No code is a prefix of
              another, so the bit string can be decoded unambiguously.
*/

#include <stdio.h>
#include <string.h>

#define MAXN 512            // at most 256 leaves + 255 internal nodes

struct H {
    int f;                  // frequency
    int ch;                 // character (only meaningful for leaves)
    int l, r;               // child indexes, -1 for a leaf
    int alive;              // still waiting to be merged?
} t[MAXN];
int m = 0;                  // number of nodes created

char code[256][64];         // code string for each character
int  root;

// make a new node and return its index
int node(int f, int ch, int l, int r) {
    t[m].f = f; t[m].ch = ch; t[m].l = l; t[m].r = r; t[m].alive = 1;
    return m++;
}

// pick the alive node with the smallest frequency (ties: earlier index)
int pickMin() {
    int b = -1;
    for (int i = 0; i < m; i++)
        if (t[i].alive && (b == -1 || t[i].f < t[b].f)) b = i;
    return b;
}

// walk the tree, building each leaf's code in s[]
void gen(int x, char s[], int d) {
    if (t[x].l == -1) {                         // leaf
        s[d] = '\0';
        strcpy(code[t[x].ch], d == 0 ? "0" : s);   // lone symbol still needs 1 bit
        return;
    }
    s[d] = '0'; gen(t[x].l, s, d + 1);
    s[d] = '1'; gen(t[x].r, s, d + 1);
}

int main() {
    char txt[101], s[64];
    int fr[256] = {0}, leaves = 0, alive = 0;

    printf("Enter text (max 100 characters): ");
    fgets(txt, sizeof(txt), stdin);
    txt[strcspn(txt, "\n")] = '\0';

    int len = strlen(txt);
    if (len == 0) {
        printf("Empty text.\n");
        return 0;
    }

    for (int i = 0; i < len; i++) fr[(unsigned char)txt[i]]++;

    // one leaf per distinct character
    for (int c = 0; c < 256; c++)
        if (fr[c]) { node(fr[c], c, -1, -1); leaves++; alive++; }

    // merge the two smallest until one node (the root) is left
    while (alive > 1) {
        int a = pickMin(); t[a].alive = 0;
        int b = pickMin(); t[b].alive = 0;
        node(t[a].f + t[b].f, -1, a, b);
        alive--;
    }
    root = pickMin();

    gen(root, s, 0);

    // ---- print code table ----
    printf("\nChar   Freq   Code\n");
    long bits = 0;
    for (int c = 0; c < 256; c++) {
        if (!fr[c]) continue;
        if (c == ' ') printf("space  ");
        else          printf("%c      ", c);
        printf("%-6d %s\n", fr[c], code[c]);
        bits += (long)fr[c] * strlen(code[c]);
    }

    // ---- encode ----
    printf("\nEncoded : ");
    for (int i = 0; i < len; i++) printf("%s", code[(unsigned char)txt[i]]);
    printf("\n");

    // ---- decode (walk the tree bit by bit) ----
    printf("Decoded : ");
    int cur = root;
    for (int i = 0; i < len; i++) {
        const char *cs = code[(unsigned char)txt[i]];
        for (int k = 0; cs[k]; k++) {
            if (t[root].l == -1) {                      // only one distinct symbol
                printf("%c", t[root].ch);
                break;
            }
            cur = (cs[k] == '0') ? t[cur].l : t[cur].r;
            if (t[cur].l == -1) { printf("%c", t[cur].ch); cur = root; }
        }
    }
    printf("\n");

    printf("\nOriginal size : %d bits (8 bits per character)\n", len * 8);
    printf("Encoded size  : %ld bits\n", bits);

    return 0;
}