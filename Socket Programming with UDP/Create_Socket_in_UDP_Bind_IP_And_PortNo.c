// Write a C program for UDP to create a socket and display if the socket is created successfully or not. Using this socket, apply bind() to associate an IP address and port number and display if the socket is bound successfully else display the error message
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 12345
#define IP_ADDRESS "127.0.0.1" // Localhost

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;

    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully.\n");

    // Prepare the sockaddr_in structure
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    servaddr.sin_port = htons(PORT);

    // Bind the socket to the IP address and port number
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Socket bound successfully to %s:%d\n", IP_ADDRESS, PORT);

    // Close the socket
    close(sockfd);
    return 0;
}
