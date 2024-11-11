//Write a program in TCP to pass a string from client to server. On the server side first display
// the string and then check if the string is a palindrome or not.

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

    // Get input string from the user
    printf("Enter a string: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove the newline character

    // Send the string to the server
    send(sock, buffer, strlen(buffer), 0);
    printf("Sent string: %s\n", buffer);

    // Close the socket
    close(sock);
    printf("[+] Disconnected from the server.\n");
    return 0;
}

