// Source: https://youtu.be/LtXEMwSG5-8

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h> 
#include <sys/types.h>

#include <netinet/in.h>

int main(){
    // create a socket
    int network_socket;

    network_socket = socket(AF_INET, SOCK_STREAM, 0); //0->TCP

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connected_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    // check for error with the connection
    if (connected_status == -1){
        printf("There was an error making connection to the remote socket.\n");
    }

    // receive data from the server
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    // print out the server's response
    printf("The server sent the data: %s", server_response);

    // at the end, close the socket
    close(network_socket);

    return 0;
}