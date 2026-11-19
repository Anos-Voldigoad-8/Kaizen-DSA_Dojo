#include <stdio.h>
int main() {
    int a[50], n, i, j, k;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter elements: ");
    for (i = 0; i < n; i++) scanf("%d", &a[i]);
    for (i = 1; i < n; i++) {
        k = a[i];
        for (j = i - 1; j >= 0 && a[j] > k; j--) a[j + 1] = a[j];
        a[j + 1] = k;
    }
    printf("\nSorted: ");
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    return 0;
}
