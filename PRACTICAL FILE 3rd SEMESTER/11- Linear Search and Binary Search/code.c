/*  DSA Practical: Linear Search and Binary Search
    Compile : gcc linear_binary_search.c -o linear_binary_search
    Run     : ./linear_binary_search
    Linear search checks elements one by one (works on any array).
    Binary search needs a sorted array: it compares with the middle
    element and throws away half of the array each step. */

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int a[MAX], n;                      // the array and its size

void rd(int *x) {                   // read an int; stop cleanly on bad input / end of input
    if (scanf("%d", x) != 1) { printf("\nInvalid input. Exiting.\n"); exit(0); }
}

void show(int b[], int m) {
    for (int i = 0; i < m; i++) printf("%d ", b[i]);
    printf("\n");
}

void input() {
    printf("Number of elements (1-%d): ", MAX);
    rd(&n);
    if (n < 1 || n > MAX) { printf("Invalid size.\n"); n = 0; return; }
    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        rd(&a[i]);
    }
}

void linear() {
    int k, c = 0;
    printf("Enter key to search: ");
    rd(&k);
    for (int i = 0; i < n; i++) {
        c++;
        if (a[i] == k) {
            printf("Linear search: %d found at index %d (position %d), %d steps.\n", k, i, i + 1, c);
            return;
        }
    }
    printf("Linear search: %d not found after %d steps.\n", k, c);
}

void binary() {
    int b[MAX], k, lo = 0, hi = n - 1, c = 0, sorted = 1;

    for (int i = 0; i < n; i++) b[i] = a[i];             // work on a copy
    for (int i = 0; i < n - 1; i++)
        if (b[i] > b[i + 1]) sorted = 0;

    if (!sorted) {                                       // binary search needs sorted data
        for (int i = 0; i < n - 1; i++)
            for (int j = 0; j < n - 1 - i; j++)
                if (b[j] > b[j + 1]) { int t = b[j]; b[j] = b[j + 1]; b[j + 1] = t; }
        printf("Array is not sorted. Searching a sorted copy: ");
        show(b, n);
    }

    printf("Enter key to search: ");
    rd(&k);

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        c++;
        printf("  low=%d high=%d mid=%d value=%d\n", lo, hi, mid, b[mid]);
        if (b[mid] == k) {
            printf("Binary search: %d found at index %d (position %d) of the sorted array, %d steps.\n",
                   k, mid, mid + 1, c);
            return;
        }
        if (b[mid] < k) lo = mid + 1;                    // key is in the right half
        else            hi = mid - 1;                    // key is in the left half
    }
    printf("Binary search: %d not found after %d steps.\n", k, c);
}

int main() {
    int ch;

    do {
        printf("\n----- SEARCH MENU -----\n");
        printf("1. Enter array\n2. Display array\n3. Linear search\n");
        printf("4. Binary search\n5. Exit\nEnter your choice: ");
        rd(&ch);

        if (ch >= 2 && ch <= 4 && n == 0) { printf("Enter the array first (option 1).\n"); continue; }

        switch (ch) {
            case 1: input(); break;
            case 2: printf("Array: "); show(a, n); break;
            case 3: linear(); break;
            case 4: binary(); break;
            case 5: printf("Exiting program.\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (ch != 5);

    return 0;
}
