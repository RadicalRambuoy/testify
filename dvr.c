#include <stdio.h>
 
int main() {
    int n, i, j, k, updated;
    int dist[10][10], nextHop[10][10];
 
    printf("Enter number of routers: ");
    scanf("%d", &n);
    printf("Enter cost matrix (0 = self, 999 = no direct link):\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
            nextHop[i][j] = j;
        }
 
    do {
        updated = 0;
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                for (k = 0; k < n; k++)
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        nextHop[i][j] = nextHop[i][k];
                        updated = 1;
                    }
    } while (updated);
 
    for (i = 0; i < n; i++) {
        printf("\nRouting table of Router %c\n", 'A' + i);
        printf("Destination  NextHop  Cost\n");
        for (j = 0; j < n; j++)
            printf("     %c          %c       %d\n", 'A' + j, 'A' + nextHop[i][j], dist[i][j]);
    }
    return 0;
}