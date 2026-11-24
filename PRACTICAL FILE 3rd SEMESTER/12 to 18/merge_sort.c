#include <stdio.h>
int a[50], b[50];
void ms(int l, int r) {
    int m, i, j, k;
    if (l >= r) return;
    m = (l + r) / 2;
    ms(l, m);
    ms(m + 1, r);
    for (i = l, j = m + 1, k = l; i <= m && j <= r; k++)
        b[k] = a[i] <= a[j] ? a[i++] : a[j++];
    while (i <= m) b[k++] = a[i++];
    while (j <= r) b[k++] = a[j++];
    for (k = l; k <= r; k++) a[k] = b[k];
}
int main() {
    int n, i;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter elements: ");
    for (i = 0; i < n; i++) scanf("%d", &a[i]);
    ms(0, n - 1);
    printf("\nSorted: ");
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    return 0;
}
