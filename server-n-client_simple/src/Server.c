#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg);

int main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(stderr, "Port No. not provided. Programm terminated.\n");
        exit(1);
    }

    int sockfd, newsockfd, portno, n;
    char buffer[255];

    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        error("Error opening Socket.");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]); // atoi -> convers string to integer

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno); // htons -> host to network short

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("Binding Failed.");

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    if(newsockfd < 0)
        error("Error on Accept.");

    while(1){
        bzero(buffer, 256);
        n = read(newsockfd, buffer, 255);
        if(n<0)
            error("Error on reading.");
        printf("Client: %s\n", buffer);
    }
}

void error(const char *msg){
    perror(msg);
    exit(1);
}