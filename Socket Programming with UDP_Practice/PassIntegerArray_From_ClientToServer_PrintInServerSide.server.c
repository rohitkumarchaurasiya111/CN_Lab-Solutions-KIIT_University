/* 2. Write a program to pass an integer array from client to server and print the array in server side.*/
// server.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int buffer[BUFFER_SIZE];
    int array_size;

  
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
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

   
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    
    read(new_socket, &array_size, sizeof(array_size));

    printf("Received array size: %d\n", array_size);

    
    read(new_socket, buffer, array_size * sizeof(int));

    
    printf("Received array elements:\n");
    for (int i = 0; i < array_size; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    close(new_socket);
    close(server_fd);
    return 0;
}


