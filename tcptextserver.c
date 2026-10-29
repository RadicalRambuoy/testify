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
    printf("Server waiting for connection...\n");

    int client = accept(server, NULL, NULL);
    printf("Client connected\n");

    char buffer[1024] = {0};
    recv(client, buffer, sizeof(buffer), 0);
    printf("Message received: %s\n", buffer);

    close(client);
    close(server);
    return 0;
}