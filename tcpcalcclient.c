#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr*)&server, sizeof(server));

    double a, b;
    char op;
    printf("Enter first number: ");       scanf("%lf", &a);
    printf("Enter operator (+ - * /): "); scanf(" %c", &op);
    printf("Enter second number: ");      scanf("%lf", &b);

    char msg[100];
    sprintf(msg, "%g %c %g", a, op, b);
    send(sock, msg, strlen(msg), 0);

    char result[100] = {0};
    recv(sock, result, sizeof(result), 0);
    printf("Result from server: %s\n", result);

    close(sock);
    return 0;
}