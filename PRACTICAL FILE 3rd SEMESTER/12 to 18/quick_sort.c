#include <stdio.h>
int a[50];
void qs(int l, int r) {
    int p, i, j, t;
    if (l >= r) return;
    p = a[r];
    i = l - 1;
    for (j = l; j < r; j++)
        if (a[j] < p) { i++; t = a[i]; a[i] = a[j]; a[j] = t; }
    t = a[i + 1]; a[i + 1] = a[r]; a[r] = t;
    qs(l, i);
    qs(i + 2, r);
}
int main() {
    int n, i;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter elements: ");
    for (i = 0; i < n; i++) scanf("%d", &a[i]);
    qs(0, n - 1);
    printf("\nSorted: ");
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    return 0;
}
