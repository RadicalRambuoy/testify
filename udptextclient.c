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

    char msg[1024];
    printf("Enter a string: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = '\0';

    sendto(sock, msg, strlen(msg), 0, (struct sockaddr*)&server, sizeof(server));

    char buffer[1024] = {0};
    recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL);
    printf("Converted string: %s\n", buffer);

    close(sock);
    return 0;
}