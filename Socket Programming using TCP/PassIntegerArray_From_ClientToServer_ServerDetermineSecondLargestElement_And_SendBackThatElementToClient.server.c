//Write a program in TCP to pass an integer array from client to server. On the server side
// determine the second largest element of the array and send back that element to the client. The
// client will then display that element.

//Server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5566
#define BUFFER_SIZE 1024
#define MAX_ARRAY_SIZE 100

// Function to find the second largest element in an array
int find_second_largest(int arr[], int size) {
    int largest = arr[0];
    int second_largest = -1;

    for (int i = 1; i < size; i++) {
        if (arr[i] > largest) {
            second_largest = largest;
            largest = arr[i];
        } else if (arr[i] != largest && (second_largest == -1 || arr[i] > second_largest)) {
            second_largest = arr[i];
        }
    }

    return second_largest;
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    int array[MAX_ARRAY_SIZE];
    int array_size;

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

    // Receive the size of the array
    recv(client_sock, &array_size, sizeof(int), 0);
    printf("Received array size: %d\n", array_size);

    // Receive the array from the client
    recv(client_sock, array, sizeof(int) * array_size, 0);
    printf("Received array: ");
    for (int i = 0; i < array_size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Find the second largest element in the array
    int second_largest = find_second_largest(array, array_size);
    printf("Second largest element: %d\n", second_largest);

    // Send the second largest element back to the client
    send(client_sock, &second_largest, sizeof(int), 0);

    // Close the sockets
    close(client_sock);
    close(server_sock);
    printf("[+] Disconnected from client.\n");
    return 0;
}

