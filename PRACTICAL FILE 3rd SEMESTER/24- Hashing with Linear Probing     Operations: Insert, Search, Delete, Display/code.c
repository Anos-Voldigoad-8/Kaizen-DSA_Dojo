/*
    DSA Practical: Hashing with Linear Probing
    Operations: Insert, Search, Delete, Display
    ----------------------------------------------------
    Compile : gcc hashing_linear_probing.c -o hashing_linear_probing
    Run     : ./hashing_linear_probing
    Hash    : h(k) = k % SZ
    Collision: linear probing -> try (h + 1) % SZ, (h + 2) % SZ, ...
    Note    : only non-negative keys are allowed. A deleted slot is marked
              DEL (not EMP) so that searches can still pass over it.
*/

#include <stdio.h>

#define SZ  10      // table size
#define EMP -1      // slot never used
#define DEL -2      // slot used earlier, now deleted

int t[SZ];          // hash table
int c = 0;          // number of keys currently stored

int hash(int k) {
    return k % SZ;
}

// returns index of key k, or -1 if not present
int find(int k) {
    int h = hash(k);
    for (int i = 0; i < SZ; i++) {
        int p = (h + i) % SZ;
        if (t[p] == EMP) return -1;      // reached a never-used slot: k is absent
        if (t[p] == k) return p;
    }
    return -1;
}

void insert() {
    int k;
    printf("Enter key to insert: ");
    scanf("%d", &k);

    if (k < 0) {
        printf("Only non-negative keys allowed.\n");
        return;
    }
    if (find(k) != -1) {
        printf("%d already exists.\n", k);
        return;
    }
    if (c == SZ) {
        printf("Table is full. Cannot insert.\n");
        return;
    }

    int h = hash(k);
    for (int i = 0; i < SZ; i++) {
        int p = (h + i) % SZ;
        if (t[p] == EMP || t[p] == DEL) {
            t[p] = k;
            c++;
            if (i == 0) printf("%d inserted at index %d.\n", k, p);
            else        printf("%d inserted at index %d (%d collision%s, h = %d).\n",
                               k, p, i, i == 1 ? "" : "s", h);
            return;
        }
    }
}

void search() {
    int k;
    printf("Enter key to search: ");
    scanf("%d", &k);

    int p = find(k);
    if (p == -1) printf("%d not found.\n", k);
    else         printf("%d found at index %d.\n", k, p);
}

void delete_key() {
    int k;
    printf("Enter key to delete: ");
    scanf("%d", &k);

    int p = find(k);
    if (p == -1) {
        printf("%d not found.\n", k);
        return;
    }
    t[p] = DEL;
    c--;
    printf("%d deleted from index %d.\n", k, p);
}

void display() {
    printf("Index : Key\n");
    for (int i = 0; i < SZ; i++) {
        if (t[i] == EMP)      printf("  %d   : --\n", i);
        else if (t[i] == DEL) printf("  %d   : (deleted)\n", i);
        else                  printf("  %d   : %d\n", i, t[i]);
    }
}

int main() {
    int ch;

    for (int i = 0; i < SZ; i++) t[i] = EMP;

    do {
        printf("\n----- HASHING (LINEAR PROBING) MENU -----\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: insert(); break;
            case 2: search(); break;
            case 3: delete_key(); break;
            case 4: display(); break;
            case 5: printf("Exiting program.\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (ch != 5);

    return 0;
}