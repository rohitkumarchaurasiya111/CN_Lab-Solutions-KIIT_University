/* Write a c program in TCP to pass a matrix of size 3*3 from client to sever. The server will display the matrix further it will determine the sum of secondary diagonal element and this sum is sent back to the client where it is displayed accordingly. */

//Client

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <arpa/inet.h> 

#define PORT 8080
#define SIZE 3

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    int matrix[SIZE][SIZE];
    char buffer[1024];

    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Connection to server failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    
    printf("Enter the 3x3 matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    
    send(sockfd, matrix, sizeof(matrix), 0);

    
    int n = read(sockfd, buffer, sizeof(buffer));
    buffer[n] = '\0'; 
    printf("Server response: %s\n", buffer);

    
    close(sockfd);

    return 0;
}


