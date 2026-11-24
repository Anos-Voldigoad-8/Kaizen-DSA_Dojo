#include <stdio.h>
int a[50];
void hp(int n, int i) {
    int m = i, l = 2 * i + 1, r = l + 1, t;
    if (l < n && a[l] > a[m]) m = l;
    if (r < n && a[r] > a[m]) m = r;
    if (m != i) { t = a[i]; a[i] = a[m]; a[m] = t; hp(n, m); }
}
int main() {
    int n, i, t;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter elements: ");
    for (i = 0; i < n; i++) scanf("%d", &a[i]);
    for (i = n / 2 - 1; i >= 0; i--) hp(n, i);
    for (i = n - 1; i > 0; i--) { t = a[0]; a[0] = a[i]; a[i] = t; hp(i, 0); }
    printf("\nSorted: ");
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    return 0;
}
