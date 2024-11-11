//Write a program in TCP to pass a string “Welcome to KIIT” from client to server. Display the
// string in server side. Further, determine the number of vowels in the string and send the same to
// the client. The client will display the number of vowels present.

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
    int vowel_count;

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

    // Send the string to the server
    char *message = "Welcome to KIIT";
    send(sock, message, strlen(message), 0);
    printf("Sent string: %s\n", message);

    // Receive the vowel count from the server
    recv(sock, &vowel_count, sizeof(int), 0);
    printf("Number of vowels: %d\n", vowel_count);

    // Close the socket
    close(sock);
    printf("[+] Disconnected from the server.\n");
    return 0;
}

