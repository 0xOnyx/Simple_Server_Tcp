
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "Dump.h"

#define PORT 737

void fail(char *err){
    char message[255];

    strcpy(message, "[ERROR] Fatal error to ");
    strncat(message, err, 40);
    perror(message);

    exit(1);
}

int main(void)
{
    int sockfd;
    int new_sockfd;
    struct sockaddr_in host_addr;
    struct sockaddr_in client_addr;
    
    int recv_lenght;
    char buffer[1024];
    socklen_t sin_size;
    int yes;
    yes = 1;

    host_addr.sin_family = AF_INET;
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    host_addr.sin_port = htons(PORT);

    memset(&(host_addr.sin_zero), 0, sizeof(host_addr.sin_zero));

    sockfd = socket(PF_INET, SOCK_STREAM, 0);

    if( sockfd == -1 )
        fail("create socket");
    

    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        fail("set options in the socket");
    
    if(bind(sockfd, (struct sockaddr *)&host_addr, sizeof(struct sockaddr)) == -1)
        fail("bind socket");

    if(listen(sockfd, 5) == -1)
        fail("listen socket");

    while(1)
    {
        sin_size = sizeof(struct sockaddr_in);   
        new_sockfd = accept(sockfd, (struct sockaddr*) &client_addr, &sin_size);
        if(new_sockfd == -1)
            fail("accecpt connection");

        printf("[INFO]\tnew connection from %s port %d", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        char hello[] = "hello\n";
        send(new_sockfd, hello, sizeof(hello), 0);

        recv_lenght = recv(new_sockfd, &buffer, 1024, 0);
        while(recv_lenght > 0)
        {
            printf("[INFO]\trecv bytes from %d", recv_lenght);
            dump(buffer, recv_lenght);
            recv_lenght = recv(new_sockfd, &buffer, 1024, 0);

        }

        close(new_sockfd);
    }
    return 0;
}