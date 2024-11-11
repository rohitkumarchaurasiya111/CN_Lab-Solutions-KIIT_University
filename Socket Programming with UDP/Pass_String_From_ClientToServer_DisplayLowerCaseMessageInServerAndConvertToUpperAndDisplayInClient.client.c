/* Write a program to pass a string from client to server. Display the lower case message in the
server. Further, convert the message from lower case to upper case and display the converted
message in client side.*/
// for Client
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ctype.h>

#define SERVER_IP "127.0.0.1"  
#define PORT 8080
#define BUFFER_SIZE 1024


void to_uppercase(char *str) {
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);
    char buffer[BUFFER_SIZE];
    ssize_t sent_len, recv_len;

    
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

    
    const char *message = "Hello from Client";
    sent_len = sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&server_addr, addr_len);
    if (sent_len < 0) {
        perror("Send failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Message sent: %s\n", message);

    
    recv_len = recvfrom(sockfd, (char*)buffer, BUFFER_SIZE, 0, NULL, NULL);
    if (recv_len < 0) {
        perror("Receive failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    
    buffer[recv_len] = '\0';
    printf("Received lowercase message: %s\n", buffer);

    
    to_uppercase(buffer);

    printf("Uppercase message: %s\n", buffer);

   
    close(sockfd);
    return 0;
}


