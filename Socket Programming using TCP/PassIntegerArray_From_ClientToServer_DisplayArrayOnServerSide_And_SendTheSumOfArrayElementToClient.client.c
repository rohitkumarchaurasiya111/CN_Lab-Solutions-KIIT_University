//Write a program in TCP to pass an integer array from client to server. Display the array on the
// server side and then determine the sum of elements of array. The server sends back this sum to
// the client side which will display the same.

//Client

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5566
#define BUFFER_SIZE 1024
#define MAX_ARRAY_SIZE 100

int main() {
    int sock;
    struct sockaddr_in server_addr;
    int array[MAX_ARRAY_SIZE];
    int array_size;

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

    // Get the size of the array
    printf("Enter the number of elements in the array (max %d): ", MAX_ARRAY_SIZE);
    scanf("%d", &array_size);
    if (array_size > MAX_ARRAY_SIZE || array_size <= 0) {
        printf("Invalid array size. Exiting.\n");
        close(sock);
        return 1;
    }

    // Get the array elements from the user
    printf("Enter %d integers:\n", array_size);
    for (int i = 0; i < array_size; i++) {
        scanf("%d", &array[i]);
    }

    // Send the size of the array to the server
    send(sock, &array_size, sizeof(int), 0);
    // Send the array to the server
    send(sock, array, sizeof(int) * array_size, 0);
    printf("Sent array: ");
    for (int i = 0; i < array_size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Receive the sum from the server
    int sum;
    recv(sock, &sum, sizeof(int), 0);
    printf("Sum of array elements received from server: %d\n", sum);

    // Close the socket
    close(sock);
    printf("[+] Disconnected from the server.\n");
    return 0;
}

