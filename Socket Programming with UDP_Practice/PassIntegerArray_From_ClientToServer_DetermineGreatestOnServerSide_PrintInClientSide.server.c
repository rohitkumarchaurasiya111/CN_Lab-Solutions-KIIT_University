/* Write a program to pass an integer array from client to server. Determine the greatest element
on the server side and print it in the client side.*/
// server.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int findGreatest(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

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

    
    int greatest = findGreatest(buffer, array_size);

  
    send(new_socket, &greatest, sizeof(greatest), 0);
    printf("Greatest element sent: %d\n", greatest);

    close(new_socket);
    close(server_fd);
    return 0;
}


