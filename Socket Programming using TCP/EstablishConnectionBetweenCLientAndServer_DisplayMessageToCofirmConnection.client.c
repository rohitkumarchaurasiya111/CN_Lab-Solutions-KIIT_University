//Write a program in TCP to establish a connection between a client and a server. Display
// appropriate messages to confirm the connection establishment or error scenario.

//Client

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5566
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("[-] Socket creation error");
        exit(EXIT_FAILURE);
    }
    printf("[+] TCP client socket created.\n");

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("[-] Connection error");
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf("[+] Connected to the server.\n");

    // Send a message to the server
    char *message = "Hello, this is the client!";
    send(sock, message, strlen(message), 0);
    printf("Client: %s\n", message);

    // Receive a response from the server
    memset(buffer, 0, BUFFER_SIZE);
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

    // Close the socket
    close(sock);
    printf("[+] Disconnected from the server.\n");
    return 0;
}

