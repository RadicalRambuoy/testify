#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr*)&server, sizeof(server));

    char first[50], msg[100], result[100];
    double a, b;
    char op;

    while (1) {
        printf("\nEnter first number (exit to quit): ");
        scanf("%s", first);

        if (strcmp(first, "exit") == 0) {
            send(sock, "exit", 4, 0);
            break;
        }
        a = atof(first);

        printf("Enter operator (+ - * /): "); scanf(" %c", &op);
        printf("Enter second number: ");      scanf("%lf", &b);

        sprintf(msg, "%g %c %g", a, op, b);
        send(sock, msg, strlen(msg), 0);

        int n = recv(sock, result, sizeof(result) - 1, 0);
        if (n <= 0) break;
        result[n] = '\0';
        printf("Result from server: %s\n", result);
    }

    close(sock);
    return 0;
}
