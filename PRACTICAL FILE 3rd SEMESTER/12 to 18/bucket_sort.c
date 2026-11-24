#include <stdio.h>
int main() {
    int a[50], b[10][50], c[10] = {0}, n, i, j, k, t, x = 0;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter elements (0 to 99): ");
    for (i = 0; i < n; i++) scanf("%d", &a[i]);
    for (i = 0; i < n; i++) b[a[i] / 10][c[a[i] / 10]++] = a[i];
    for (i = 0; i < 10; i++) {
        for (j = 1; j < c[i]; j++) {
            t = b[i][j];
            for (k = j - 1; k >= 0 && b[i][k] > t; k--) b[i][k + 1] = b[i][k];
            b[i][k + 1] = t;
        }
        for (j = 0; j < c[i]; j++) a[x++] = b[i][j];
    }
    printf("\nSorted: ");
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    return 0;
}
