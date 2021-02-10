#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

void str_echo(int new_sock)
{

    int cont, buffsize = 1024;
    char buff[buffsize];
again:
    while ((cont = recv(new_sock, buff, buffsize, 0)) > 0)
    {
        send(new_sock, buff, cont, 0);
        memset(buff,'\0',strlen(buff));
        // bzero(buff,1024);
    }

    if (cont < 0 )
        goto again;
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
    bzero(&addr,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9002);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == 0)
    {
        printf("\nBinding successfully to the IP: %s ... Port:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
    }
    else
    {
        printf("\nError in bind\n");
        exit(0);
    }

    listen(sockfd, 3);
    int new_sock,addrlen;
    struct sockaddr_in cliaddr;
    while (1)
    {
        addrlen = sizeof(struct sockaddr_in);
        if ((new_sock = accept(sockfd, (struct sockaddr *)&cliaddr, &addrlen)) > 0)
        {
            printf("\nClient %s connected....\n", inet_ntoa(addr.sin_addr));
        }
        else
        {
            printf("\nError in accept system call\n");
            exit(0);
        }

        str_echo(new_sock);
        close(new_sock);
    }

    // close(sockfd);
    return 0;
}
