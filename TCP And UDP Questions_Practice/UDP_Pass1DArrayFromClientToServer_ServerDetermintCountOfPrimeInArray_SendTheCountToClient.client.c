/* Write a program in UDP to pass a one dimensional array from client to server. The server will display the array. Further it will determine the count of prime numbers in the array and send the count to the count to the client where it is displayed accordingly. */
//Client

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>  

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sockfd;
    int arr[MAXLINE];
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;

    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int len, n;
    len = sizeof(servaddr);

    
    int arr_size;
    printf("Enter the size of the array: ");
    scanf("%d", &arr_size);

    
    printf("Enter %d elements of the array: ", arr_size);
    for (int i = 0; i < arr_size; i++) {
        scanf("%d", &arr[i]);
    }

    
    sendto(sockfd, &arr_size, sizeof(arr_size), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    
    sendto(sockfd, arr, arr_size * sizeof(int), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    
    n = recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr *)&servaddr, &len);
    buffer[n] = '\0';
    printf("Server's response: %s\n", buffer);

    
    close(sockfd);

    return 0;
}


