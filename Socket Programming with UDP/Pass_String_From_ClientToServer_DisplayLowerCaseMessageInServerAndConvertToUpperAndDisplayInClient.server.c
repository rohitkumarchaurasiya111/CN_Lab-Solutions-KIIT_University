/* Write a program to pass a string from client to server. Display the lower case message in the
server. Further, convert the message from lower case to upper case and display the converted
message in client side.*/
// For server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ctype.h>

#define PORT 8080
#define BUFFER_SIZE 1024


void to_lowercase(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    int recv_len;

    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Server socket created successfully.\n");

    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Socket bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Server bound to port %d.\n", PORT);

    
    recv_len = recvfrom(sockfd, (char*)buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &addr_len);
    if (recv_len < 0) {
        perror("Receive failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    
    buffer[recv_len] = '\0';
    printf("Received message: %s\n", buffer);

   
    to_lowercase(buffer);

    
    if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, addr_len) < 0) {
        perror("Send failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Lowercase message sent: %s\n", buffer);

    
    close(sockfd);
    return 0;
}


