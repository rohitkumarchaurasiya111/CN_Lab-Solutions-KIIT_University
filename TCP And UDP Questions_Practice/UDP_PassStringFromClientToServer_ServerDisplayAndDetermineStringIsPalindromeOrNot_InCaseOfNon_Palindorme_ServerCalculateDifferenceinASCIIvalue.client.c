/* Write a c program using UDP to pass a string from client to server. The server will display the string , further it will determine if the string is palindrome or not. In case of palindrome, the server will send a message to the client and client will display the same accordingly. In case of non palindrome string , the server will determine the difference in ascii values of those 2 characters where the strings became different. */

//Client

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sockfd;
    char buffer[MAXLINE];
    char message[MAXLINE];
    struct sockaddr_in servaddr;

    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;

    
    printf("Enter a string: ");
    fgets(message, MAXLINE, stdin);
    message[strcspn(message, "\n")] = '\0'; 

    
    sendto(sockfd, message, strlen(message), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    
    len = sizeof(servaddr);
    n = recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr *)&servaddr, &len);
    buffer[n] = '\0';
    printf("Server's response: %s\n", buffer);

    close(sockfd);
    return 0;
}


