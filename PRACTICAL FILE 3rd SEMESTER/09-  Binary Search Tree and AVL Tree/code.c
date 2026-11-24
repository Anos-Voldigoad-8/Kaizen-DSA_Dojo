/*
    DSA Assignment 09: Binary Search Tree and AVL Tree
    Operations: Insert, Delete, Search, Inorder, Preorder, Postorder,
                Min/Max, Height, Balanced check, Show tree
    ----------------------------------------------------
    Compile : gcc bst_avl_operations.c -o bst_avl_operations
    Run     : ./bst_avl_operations
    Note    : the same insert/delete code runs for both trees;
              the flag 'a' = 1 turns on AVL rebalancing.
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int d;                 // data
    int h;                 // height of this node
    struct Node *l, *r;    // left, right child
};

// -------------------- HELPERS --------------------
int ht(struct Node *t) { return t ? t->h : 0; }
int mx(int a, int b)   { return a > b ? a : b; }
int bf(struct Node *t) { return t ? ht(t->l) - ht(t->r) : 0; }   // balance factor

struct Node *newNode(int v) {
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    n->d = v;
    n->h = 1;
    n->l = n->r = NULL;
    return n;
}

// -------------------- ROTATIONS (AVL) --------------------
struct Node *rotR(struct Node *y) {
    struct Node *x = y->l;
    y->l = x->r;
    x->r = y;
    y->h = 1 + mx(ht(y->l), ht(y->r));
    x->h = 1 + mx(ht(x->l), ht(x->r));
    return x;
}

struct Node *rotL(struct Node *x) {
    struct Node *y = x->r;
    x->r = y->l;
    y->l = x;
    x->h = 1 + mx(ht(x->l), ht(x->r));
    y->h = 1 + mx(ht(y->l), ht(y->r));
    return y;
}

struct Node *balance(struct Node *t) {
    int b = bf(t);

    if (b > 1) {                               // left heavy
        if (bf(t->l) < 0) t->l = rotL(t->l);   // LR case
        return rotR(t);                        // LL case
    }
    if (b < -1) {                              // right heavy
        if (bf(t->r) > 0) t->r = rotR(t->r);   // RL case
        return rotL(t);                        // RR case
    }
    return t;
}

// -------------------- INSERT --------------------
struct Node *insert(struct Node *t, int v, int a) {
    if (t == NULL) return newNode(v);

    if (v < t->d) t->l = insert(t->l, v, a);
    else          t->r = insert(t->r, v, a);

    t->h = 1 + mx(ht(t->l), ht(t->r));
    return a ? balance(t) : t;
}

// -------------------- SEARCH --------------------
struct Node *search(struct Node *t, int v) {
    if (t == NULL || t->d == v) return t;
    if (v < t->d) return search(t->l, v);
    return search(t->r, v);
}

// -------------------- DELETE --------------------
struct Node *minNode(struct Node *t) {
    while (t->l) t = t->l;
    return t;
}

struct Node *maxNode(struct Node *t) {
    while (t->r) t = t->r;
    return t;
}

struct Node *del(struct Node *t, int v, int a) {
    if (t == NULL) return NULL;

    if (v < t->d) {
        t->l = del(t->l, v, a);
    } else if (v > t->d) {
        t->r = del(t->r, v, a);
    } else {
        if (t->l == NULL || t->r == NULL) {          // 0 or 1 child
            struct Node *c = t->l ? t->l : t->r;
            free(t);
            return c;
        }
        struct Node *s = minNode(t->r);              // 2 children: inorder successor
        t->d = s->d;
        t->r = del(t->r, s->d, a);
    }

    t->h = 1 + mx(ht(t->l), ht(t->r));
    return a ? balance(t) : t;
}

// -------------------- TRAVERSALS --------------------
void inorder(struct Node *t) {
    if (t == NULL) return;
    inorder(t->l);
    printf("%d ", t->d);
    inorder(t->r);
}

void preorder(struct Node *t) {
    if (t == NULL) return;
    printf("%d ", t->d);
    preorder(t->l);
    preorder(t->r);
}

void postorder(struct Node *t) {
    if (t == NULL) return;
    postorder(t->l);
    postorder(t->r);
    printf("%d ", t->d);
}

// -------------------- BALANCED CHECK --------------------
int isBalanced(struct Node *t) {
    if (t == NULL) return 1;
    int b = bf(t);
    if (b < -1 || b > 1) return 0;
    return isBalanced(t->l) && isBalanced(t->r);
}

// -------------------- SHOW TREE (sideways, root at left) --------------------
void show(struct Node *t, int lvl, int a) {
    if (t == NULL) return;
    show(t->r, lvl + 1, a);
    printf("%*s%d", lvl * 6, "", t->d);
    if (a) printf(" (bf=%d)", bf(t));
    printf("\n");
    show(t->l, lvl + 1, a);
}

// -------------------- MENU FOR ONE TREE --------------------
void treeMenu(struct Node **root, int a) {
    int ch, v;

    do {
        printf("\n----- %s MENU -----\n", a ? "AVL TREE" : "BINARY SEARCH TREE");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Inorder\n");
        printf("5. Preorder\n");
        printf("6. Postorder\n");
        printf("7. Minimum and Maximum\n");
        printf("8. Height\n");
        printf("9. Is Balanced?\n");
        printf("10. Show Tree\n");
        printf("11. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &v);
                if (search(*root, v)) {
                    printf("%d already exists. Duplicates not allowed.\n", v);
                } else {
                    *root = insert(*root, v, a);
                    printf("%d inserted.\n", v);
                }
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &v);
                if (search(*root, v)) {
                    *root = del(*root, v, a);
                    printf("%d deleted.\n", v);
                } else {
                    printf("%d not found.\n", v);
                }
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &v);
                if (search(*root, v)) printf("%d found.\n", v);
                else printf("%d not found.\n", v);
                break;
            case 4:
                printf("Inorder   : "); inorder(*root);   printf("\n");
                break;
            case 5:
                printf("Preorder  : "); preorder(*root);  printf("\n");
                break;
            case 6:
                printf("Postorder : "); postorder(*root); printf("\n");
                break;
            case 7:
                if (*root == NULL) printf("Tree is empty.\n");
                else printf("Min = %d, Max = %d\n", minNode(*root)->d, maxNode(*root)->d);
                break;
            case 8:
                printf("Height = %d\n", ht(*root));
                break;
            case 9:
                if (isBalanced(*root)) printf("Tree is balanced (every bf is -1, 0 or 1).\n");
                else printf("Tree is NOT balanced.\n");
                break;
            case 10:
                if (*root == NULL) printf("Tree is empty.\n");
                else show(*root, 0, a);
                break;
            case 11:
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (ch != 11);
}

// -------------------- MAIN --------------------
int main() {
    struct Node *bst = NULL;    // root of the BST
    struct Node *avl = NULL;    // root of the AVL tree
    int ch;

    do {
        printf("\n===== TREE TYPE =====\n");
        printf("1. Binary Search Tree\n");
        printf("2. AVL Tree\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        if (ch == 1) treeMenu(&bst, 0);
        else if (ch == 2) treeMenu(&avl, 1);
        else if (ch == 3) printf("Exiting program.\n");
        else printf("Invalid choice. Try again.\n");

    } while (ch != 3);

    return 0;
}
