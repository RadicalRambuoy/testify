#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr, client;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    printf("UDP server waiting...\n");

    char buffer[1024];
    while (1) {
        socklen_t len = sizeof(client);
        int n = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&client, &len);
        buffer[n] = '\0';

        if (strcmp(buffer, "exit") == 0) {
            printf("Client exited\n");
            break;
        }
        printf("Received: %s\n", buffer);

        for (int i = 0; buffer[i]; i++)
            buffer[i] = toupper(buffer[i]);

        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&client, len);
        printf("Sent back: %s\n", buffer);
    }

    close(sock);
    return 0;
}
