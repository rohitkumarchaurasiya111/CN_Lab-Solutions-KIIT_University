//Write a program in TCP to establish a connection between a client and a server. Display
// appropriate messages to confirm the connection establishment or error scenario.

//Server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5566
#define BUFFER_SIZE 1024

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];

    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("[-] Socket creation error");
        exit(EXIT_FAILURE);
    }
    printf("[+] TCP server socket created.\n");

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("[-] Bind error");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    printf("[+] Bind to port %d.\n", PORT);

    // Listen for incoming connections
    if (listen(server_sock, 5) < 0) {
        perror("[-] Listen error");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    printf("[+] Listening for connections...\n");

    // Accept a client connection
    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    if (client_sock < 0) {
        perror("[-] Accept error");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    printf("[+] Client connected.\n");

    // Communicate with the client
    memset(buffer, 0, BUFFER_SIZE);
    recv(client_sock, buffer, sizeof(buffer), 0);
    printf("Client: %s\n", buffer);

    // Send a response to the client
    char *response = "Hello, this is the server!";
    send(client_sock, response, strlen(response), 0);

    // Close the sockets
    close(client_sock);
    close(server_sock);
    printf("[+] Disconnected from client.\n");
    return 0;
};

