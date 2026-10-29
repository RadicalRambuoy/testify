#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server, (struct sockaddr*)&addr, sizeof(addr));
    listen(server, 1);
    printf("Calculator server waiting...\n");

    int client = accept(server, NULL, NULL);
    printf("Client connected\n");

    char buffer[1024] = {0};
    recv(client, buffer, sizeof(buffer), 0);
    printf("Received: %s\n", buffer);

    double a, b;
    char op;
    sscanf(buffer, "%lf %c %lf", &a, &op, &b);

    char result[100];
    if (op == '+')      sprintf(result, "%g", a + b);
    else if (op == '-') sprintf(result, "%g", a - b);
    else if (op == '*') sprintf(result, "%g", a * b);
    else if (op == '/') {
        if (b == 0) strcpy(result, "Error: division by zero");
        else        sprintf(result, "%g", a / b);
    }
    else strcpy(result, "Error: invalid operator");

    send(client, result, strlen(result), 0);
    printf("Result sent: %s\n", result);

    close(client);
    close(server);
    return 0;
}