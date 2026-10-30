#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    char msg[1024], buffer[1024];
    while (1) {
        printf("Enter a string (exit to quit): ");
        fgets(msg, sizeof(msg), stdin);
        msg[strcspn(msg, "\n")] = '\0';

        sendto(sock, msg, strlen(msg), 0, (struct sockaddr*)&server, sizeof(server));

        if (strcmp(msg, "exit") == 0)
            break;

        int n = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, NULL, NULL);
        buffer[n] = '\0';
        printf("Converted string: %s\n", buffer);
    }

    close(sock);
    return 0;
}
