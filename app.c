
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>

#define PORT 737

void fail(char *err){
    char message[255];

    strcpy("[ERROR] Fatal error to");
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

    host_addr.sin_family = AF_INET;
    host_addr.sin_addr = htonl(INADDR_ANY);
    host_addr.sin_port = htons(PORT);
    memset(&(host_addr.sin_zero), 0, sizeof(host_addr.sin_zero))

    if( sockfd = socket(PF_INET, SOCK_STREAM, 0) == -1 )
        fail("create socket");
    
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, 1, sizeof(int)) == -1)
        fail("set options int the socket");
    
    if(bind(sockfd, (struct sockaddr *)&host_addr, sizeof(struct sockaddr)) == -1)
        fail("bind socket");

    if(listen(sockfd, 5) == -1)
        fail("listen socket")

    while(1)
    {
        sin_size = sizeof(struct sockaddr_in);   
        new_sockfd = accept(sockfd, (sturct sockaddr*) &client_addr, &sin_size)
        if(new_sockfd == -1)
            fail("accecpt connection")

        printf("[INFO]\tnew connection from %s port %d", 
        inet_ntoa(client_addr.sin_addr), 
        ntohs(client_addr.sin_port))

        char hello[] = "hello\n"
        send(new_sockfd, hello, sizeof(hello), 0);

        recv_lenght = recv(new_sockfd, &buffer, 1024, 0);
        while(recv_lenght > 0)
            recv_lenght = recv(new_sockfd, &buffer, 1024, 0)
    }
    


    return 0;
}