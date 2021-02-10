#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

void str_echo(int new_sock){
    char buff[1024];

    int cont;

again:
    while((cont=recv(new_sock,buff,1024,0)) > 0){
        send(new_sock,buff,cont,0);
        bzero(buff,1024);
    }

    if(cont<0) goto again;
}

int main()
{
    int sockfd;
    struct sockaddr_in addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) > 0)
    {
        printf("\nSocket created successfully\n");
    }
    else
    {
        printf("\nError in socket creation\n");
        exit(0);
    }

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9002);

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == 0)
    {
        printf("\nBinding to IP: %s...\n", inet_ntoa(addr.sin_addr));
    }
    else
    {
        printf("\nError in bind\n");
        exit(0);
    }
    listen(sockfd, 3);
    int new_sock,pid;
    while (1)
    {
        int addrlen = sizeof(addr);
        new_sock = accept(sockfd, (struct sockaddr *)&addr, &addrlen);

        if((pid=fork())==0){
            close(sockfd);
            str_echo(new_sock);
            exit(0);
        }
        close(new_sock);
    }

    return 0;
}