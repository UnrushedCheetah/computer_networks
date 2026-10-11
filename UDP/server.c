
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

// Create UDP socket
int createSocket() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    return sockfd;
}

// Bind socket
void bindSocket(int sockfd, struct sockaddr_in *addr) {
    addr->sin_family = AF_INET;
    addr->sin_port = htons(PORT);
    addr->sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)addr,
             sizeof(*addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(1);
    }
}

// Reverse string
void reverseString(char str[]) {
    int i, j;
    char temp;

    for (i = 0, j = strlen(str) - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[1024];
    int n;

    // Create and bind socket
    sockfd = createSocket();
    printf("UDP socket created.\n");

    bindSocket(sockfd, &server_addr);
    printf("Socket bound to port %d.\n", PORT);

    printf("Server is waiting for a message...\n");

    // Receive string from client
    n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                 (struct sockaddr *)&client_addr, &addr_len);

    if (n < 0) {
        perror("Receive failed");
        close(sockfd);
        return 1;
    }

    buffer[n] = '\0';
    printf("Received string: %s\n", buffer);

    // Process string
    reverseString(buffer);

    // Send reversed string to client
    sendto(sockfd, buffer, strlen(buffer), 0,
           (struct sockaddr *)&client_addr, addr_len);

    printf("Reversed string sent to client.\n");

    close(sockfd);
    return 0;
}
