
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

// Create socket
int createSocket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

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

// Calculate result
float calculate(float a, float b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                printf("Error: Division by zero\n");
                return 0;
            }
            return a / b;
        default:
            printf("Invalid operator\n");
            return 0;
    }
}

// Main function
int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr;
    char buffer[100];
    float a, b, result;
    char op;

    // Create and bind socket
    server_fd = createSocket();
    printf("Server socket created.\n");

    bindSocket(server_fd, &server_addr);
    printf("Socket bound to port %d.\n", PORT);

    // Listen for client
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(1);
    }

    printf("Server is listening...\n");

    // Accept client
    client_fd = accept(server_fd, NULL, NULL);

    if (client_fd < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(1);
    }

    printf("Client connected.\n");

    // Receive expression
    int n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    if (n <= 0) {
        printf("Failed to receive data.\n");
        close(client_fd);
        close(server_fd);
        return 1;
    }

    buffer[n] = '\0';

    sscanf(buffer, "%f %c %f", &a, &op, &b);

    printf("Received: %.2f %c %.2f\n", a, op, b);

    // Calculate and send result
    result = calculate(a, b, op);

    snprintf(buffer, sizeof(buffer), "Result = %.2f", result);
    send(client_fd, buffer, strlen(buffer) + 1, 0);

    printf("Result sent to client.\n");

    // Close sockets
    close(client_fd);
    close(server_fd);

    printf("Server closed.\n");

    return 0;
}
