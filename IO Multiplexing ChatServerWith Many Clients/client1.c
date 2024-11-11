//Write the client side and server side of a connection-oriented socket where the server will
// behave as a chart server serving multiple chart clients. When the chart server receives a “logout”
// message from a particular client then it terminates the respective connection with that client.

//Client 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE];

    
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Connection Failed\n");
        return -1;
    }

    printf("Connected to the server.\n");

    while (1) {
        
        printf("You: ");
        fgets(message, BUFFER_SIZE, stdin);

        
        send(client_socket, message, strlen(message), 0);

        if (strcmp(message, "logout\n") == 0) {
            printf("You have logged out.\n");
            break;
        }

        
        int valread = read(client_socket, buffer, BUFFER_SIZE);
        buffer[valread] = '\0'; 
        printf("Server: %s", buffer);
    }

    close(client_socket);
    return 0;
}


