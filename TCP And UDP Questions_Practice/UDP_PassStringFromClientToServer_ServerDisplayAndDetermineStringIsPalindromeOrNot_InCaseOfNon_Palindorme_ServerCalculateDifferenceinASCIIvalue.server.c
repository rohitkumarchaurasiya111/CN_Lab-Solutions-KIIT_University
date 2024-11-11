/* Write a c program using UDP to pass a string from client to server. The server will display the string , further it will determine if the string is palindrome or not. In case of palindrome, the server will send a message to the client and client will display the same accordingly. In case of non palindrome string , the server will determine the difference in ascii values of those 2 characters where the strings became different. */

//Server

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>

#define PORT 8080
#define MAXLINE 1024

int is_palindrome(char *str) {
    int len = strlen(str);
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        if (str[i] != str[j]) {
            return i;  
        }
    }
    return -1; 
}

int main() {
    int sockfd;
    char buffer[MAXLINE];
    char *palindrome_msg = "The string is a palindrome";
    char ascii_diff_msg[MAXLINE];
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

    
    n = recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr *)&cliaddr, &len);
    buffer[n] = '\0';
    printf("Client sent: %s\n", buffer);

    
    int result = is_palindrome(buffer);
    if (result == -1) {
        
        sendto(sockfd, palindrome_msg, strlen(palindrome_msg), 0, (struct sockaddr *)&cliaddr, len);
    } else {
        
        snprintf(ascii_diff_msg, sizeof(ascii_diff_msg), "Not a palindrome. ASCII difference at index %d: %d",
                 result, abs(buffer[result] - buffer[strlen(buffer) - 1 - result]));
        sendto(sockfd, ascii_diff_msg, strlen(ascii_diff_msg), 0, (struct sockaddr *)&cliaddr, len);
    }

    return 0;
}


