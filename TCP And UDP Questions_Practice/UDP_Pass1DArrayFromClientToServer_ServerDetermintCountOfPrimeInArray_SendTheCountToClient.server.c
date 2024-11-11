/* Write a program in UDP to pass a one dimensional array from client to server. The server will display the array. Further it will determine the count of prime numbers in the array and send the count to the count to the client where it is displayed accordingly. */

//Server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int is_prime(int num) {
    if (num <= 1)
        return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int main() {
    int sockfd;
    int buffer[MAXLINE];
    char response[50];
    struct sockaddr_in servaddr, cliaddr;

    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;
    len = sizeof(cliaddr);  

 
    int arr_size;
    n = recvfrom(sockfd, &arr_size, sizeof(arr_size), 0, (struct sockaddr *)&cliaddr, &len);
    printf("Array size received: %d\n", arr_size);

    
    n = recvfrom(sockfd, buffer, arr_size * sizeof(int), 0, (struct sockaddr *)&cliaddr, &len);
    printf("Array received from client: ");
    for (int i = 0; i < arr_size; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    
    int prime_count = 0;
    for (int i = 0; i < arr_size; i++) {
        if (is_prime(buffer[i])) {
            prime_count++;
        }
    }

    
    snprintf(response, sizeof(response), "Prime count: %d", prime_count);
    sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&cliaddr, len);

    printf("Prime count sent to client: %d\n", prime_count);

    return 0;
}


