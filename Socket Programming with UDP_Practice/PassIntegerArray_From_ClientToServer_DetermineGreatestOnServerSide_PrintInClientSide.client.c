/* Write a program to pass an integer array from client to server. Determine the greatest element
on the server side and print it in the client side. */
// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    int array_size;
    int buffer[BUFFER_SIZE];
    int greatest;

    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }

    
    printf("Enter the number of elements: ");
    scanf("%d", &array_size);

   
    send(sock, &array_size, sizeof(array_size), 0);

    
    printf("Enter the array elements:\n");
    for (int i = 0; i < array_size; i++) {
        scanf("%d", &buffer[i]);
    }
    send(sock, buffer, array_size * sizeof(int), 0);

    
    read(sock, &greatest, sizeof(greatest));
    printf("Greatest element received: %d\n", greatest);

    close(sock);
    return 0;
}


