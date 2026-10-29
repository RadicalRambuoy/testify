#include <stdio.h>

int main() {
    int m, r = 0, n, i, j, k, p, pos;
    int d[32], h[64];

    printf("Enter number of data bits: ");
    scanf("%d", &m);

    while ((1 << r) < m + r + 1) r++;
    n = m + r;

    printf("Enter %d data bits (space separated): ", m);
    for (i = 0; i < m; i++) scanf("%d", &d[i]);

    j = 0;
    for (i = 1; i <= n; i++) {
        if ((i & (i - 1)) == 0) h[i] = 0;
        else h[i] = d[j++];
    }

    for (k = 0; k < r; k++) {
        p = 1 << k;
        for (i = 1; i <= n; i++)
            if ((i & p) && i != p) h[p] ^= h[i];
    }

    printf("Parity bits: %d, Total bits: %d\n", r, n);
    printf("Transmitted codeword: ");
    for (i = 1; i <= n; i++) printf("%d", h[i]);
    printf("\n");

    printf("Enter bit position to corrupt (1-%d): ", n);
    scanf("%d", &pos);
    h[pos] ^= 1;

    printf("Received codeword:    ");
    for (i = 1; i <= n; i++) printf("%d", h[i]);
    printf("\n");

    int err = 0;
    for (k = 0; k < r; k++) {
        p = 1 << k;
        int check = 0;
        for (i = 1; i <= n; i++)
            if (i & p) check ^= h[i];
        if (check) err += p;
    }

    if (err == 0) {
        printf("No error detected\n");
    } else {
        printf("Error detected at position %d\n", err);
        h[err] ^= 1;
        printf("Corrected codeword:   ");
        for (i = 1; i <= n; i++) printf("%d", h[i]);
        printf("\n");
    }

    printf("Data received: ");
    for (i = 1; i <= n; i++)
        if ((i & (i - 1)) != 0) printf("%d", h[i]);
    printf("\n");
    return 0;
}