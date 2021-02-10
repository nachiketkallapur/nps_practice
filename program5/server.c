#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

void str_echo(int new_sock)
{

    int cont, buffsize = 10240;
    char send_buff[buffsize];
    char receive_buff[buffsize];

    while ((cont = recv(new_sock, receive_buff, buffsize, 0)) > 0)
    {
        printf("\nClient:  %s\n", receive_buff);
        printf("\nMe: ");
        if(fgets(send_buff,buffsize,stdin)!=NULL){
            send_buff[strlen(send_buff)]='\0';
            send(new_sock,send_buff,strlen(send_buff),0);
        }

        bzero(send_buff,buffsize);
        bzero(receive_buff,buffsize);
    }
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
    addr.sin_port = htons(15002);

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == 0)
    {
        printf("\n Binding to IP:%s.. port:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
    }
    else
    {
        printf("\nError in bind\n");
        exit(0);
    }

    listen(sockfd, 3);
    int pid;
    while (1)
    {
        int addrlen = sizeof(struct sockaddr_in);
        int new_sock = accept(sockfd, (struct sockaddr *)&addr, &addrlen);
        if ((pid = fork()) == 0)
        {
            printf("\nInside child\n");
            close(sockfd);
            str_echo(new_sock);
            exit(0);
        }
        close(new_sock);
    }

    return close(sockfd);
}