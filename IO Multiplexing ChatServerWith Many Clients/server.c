////Write the client side and server side of a connection-oriented socket where the server will
// behave as a chart server serving multiple chart clients. When the chart server receives a “logout”
// message from a particular client then it terminates the respective connection with that client.

//Server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = read(client_socket, buffer, BUFFER_SIZE)) > 0) {
        buffer[bytes_read] = '\0';
        if (strcmp(buffer, "logout\n") == 0) {
            printf("Client disconnected.\n");
            break;
        }

        printf("Client: %s", buffer);
        send(client_socket, buffer, strlen(buffer), 0);
    }

    close(client_socket);
}

int main() {
    int server_socket, client_socket, addr_len;
    struct sockaddr_in server_addr, client_addr;

    
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

   
    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server started, waiting for connections...\n");

    
    addr_len = sizeof(client_addr);
    while ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, (socklen_t *)&addr_len)) >= 0) {
        printf("New client connected.\n");

        
        if (fork() == 0) {
            close(server_socket);
	    handle_client(client_socket);
            exit(0);
        }

        
        close(client_socket);
    }

    if (client_socket < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    close(server_socket);
    return 0;
}


