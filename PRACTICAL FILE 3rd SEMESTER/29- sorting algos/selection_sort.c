#include <stdio.h>
int main() {
    int a[50], n, i, j, m, t;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter elements: ");
    for (i = 0; i < n; i++) scanf("%d", &a[i]);
    for (i = 0; i < n - 1; i++) {
        m = i;
        for (j = i + 1; j < n; j++)
            if (a[j] < a[m]) m = j;
        t = a[i]; a[i] = a[m]; a[m] = t;
    }
    printf("\nSorted: ");
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    return 0;
}
