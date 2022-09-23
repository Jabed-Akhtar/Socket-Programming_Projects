// Source: https://youtu.be/LtXEMwSG5-8

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h> 
#include <sys/types.h>

#include <netinet/in.h>

int main(){
    char server_message[256] = "Server reached!";

    // create the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to our specified IP and port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // listen connections
    listen(server_socket, 2); // waiting for at least 2 clients

    // accept client
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    // send the message to the client
    send(client_socket, server_message, sizeof(server_message), 0);

    // close the socket
    close(server_socket);

    return 0;
}