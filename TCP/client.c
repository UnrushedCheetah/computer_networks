
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in server;
    char buffer[100];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&server,
            sizeof(server));

    printf("Enter expression (e.g., 10 + 5): ");
    fgets(buffer, sizeof(buffer), stdin);

    write(sock, buffer, strlen(buffer) + 1);

    read(sock, buffer, sizeof(buffer));
    printf("Server response: %s\n", buffer);

    close(sock);

    return 0;
}
