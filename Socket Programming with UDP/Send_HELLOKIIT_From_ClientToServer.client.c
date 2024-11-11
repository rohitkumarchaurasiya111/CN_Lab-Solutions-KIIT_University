/* Write a C program in UDP to send a message "Hello KIIT" from client to server. Display the
message on the server side.*/
// For client
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"  
#define PORT 8080
#define MESSAGE "Hello KIIT"

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);
    ssize_t sent_len;

   
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Client socket created successfully.\n");

    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);

    
    sent_len = sendto(sockfd, MESSAGE, strlen(MESSAGE), 0, (struct sockaddr*)&server_addr, addr_len);
    if (sent_len < 0) {
        perror("Send failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Message sent: %s\n", MESSAGE);

    
    close(sockfd);
    return 0;
}


