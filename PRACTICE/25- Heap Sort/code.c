/*
    DSA Practical: Heap Sort
    ----------------------------------------------------
    Compile : gcc heap_sort.c -o heap_sort
    Run     : ./heap_sort
    Idea    : 1) build a max-heap (largest element at a[0])
              2) swap a[0] with the last element, shrink the heap by one,
                 and re-heapify. Repeat. The array ends up sorted ascending.
    Index   : for node i  ->  left child = 2i+1, right child = 2i+2
*/

#include <stdio.h>

// push a[i] down until the subtree rooted at i is a max-heap (heap size = n)
void heapify(int a[], int n, int i) {
    int lg = i;              // index of the largest among i, left, right
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && a[l] > a[lg]) lg = l;
    if (r < n && a[r] > a[lg]) lg = r;

    if (lg != i) {
        int t = a[i]; a[i] = a[lg]; a[lg] = t;
        heapify(a, n, lg);
    }
}

void display(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

void heapSort(int a[], int n) {
    // step 1: build max-heap (start from last non-leaf node)
    for (int i = n / 2 - 1; i >= 0; i--) heapify(a, n, i);

    printf("Max-heap built : ");
    display(a, n);

    // step 2: repeatedly move the max to the end
    for (int i = n - 1; i > 0; i--) {
        int t = a[0]; a[0] = a[i]; a[i] = t;
        heapify(a, i, 0);
    }
}

int main() {
    int a[100], n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    heapSort(a, n);

    printf("Sorted array   : ");
    display(a, n);

    return 0;
}