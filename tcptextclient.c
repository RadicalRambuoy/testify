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

    char msg[1024];
    while (1) {
        printf("Enter message (exit to quit): ");
        fgets(msg, sizeof(msg), stdin);
        msg[strcspn(msg, "\n")] = '\0';

        send(sock, msg, strlen(msg), 0);

        if (strcmp(msg, "exit") == 0)
            break;
        printf("Message sent\n");
    }

    close(sock);
    return 0;
}
