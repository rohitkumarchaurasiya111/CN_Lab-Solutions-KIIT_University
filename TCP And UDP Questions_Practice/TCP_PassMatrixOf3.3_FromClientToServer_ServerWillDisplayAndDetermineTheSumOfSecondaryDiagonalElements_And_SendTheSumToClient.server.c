/* Write a c program in TCP to pass a matrix of size 3*3 from client to sever. The server will display the matrix further it will determine the sum of secondary diagonal element and this sum is sent back to the client where it is displayed accordingly. */

//Server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <arpa/inet.h> 

#define PORT 8080
#define SIZE 3


int sum_secondary_diagonal(int matrix[SIZE][SIZE]) {
    int sum = 0;
    for (int i = 0; i < SIZE; i++) {
        sum += matrix[i][SIZE - i - 1];
    }
    return sum;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int matrix[SIZE][SIZE];
    int received_bytes;
    char buffer[1024];

    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    
    received_bytes = read(new_socket, matrix, sizeof(matrix));
    if (received_bytes < 0) {
        perror("read failed");
        close(new_socket);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    
    printf("Received matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    
    int sum = sum_secondary_diagonal(matrix);

    
    snprintf(buffer, sizeof(buffer), "Sum of secondary diagonal: %d", sum);
    send(new_socket, buffer, strlen(buffer), 0);

    
    close(new_socket);
    close(server_fd);

    return 0;
}


