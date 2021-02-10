#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

int main()
{

    int sockfd, newsock, buffsize = 1024;
    char buff[buffsize];
    struct sockaddr_in addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) > 0)
    {
        printf("\nSocket creation successful...");
    }
    else
    {
        printf("\nError in socket creation\n");
        exit(0);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(15002);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == 0)
    {
        printf("\nBinding to IP: %s.....", inet_ntoa(addr.sin_addr));
    }
    else
    {
        printf("\nError in bind\n");
        exit(0);
    }

    listen(sockfd, 3);
    int addrlen = sizeof(addr);
    if ((newsock = accept(sockfd, (struct sockaddr *)&addr, &addrlen)) > 0)
    {
        printf("\nClient %s is connected...", inet_ntoa(addr.sin_addr));
    }
    else
    {
        printf("\nError in accept system call\n");
        exit(0);
    }
    int cont;

    while (1)
    {
        cont = recv(newsock, buff, buffsize, 0);
        // buff[cont] = '\0';
        if (strcmp(buff, "end") == 0)
        {
            close(newsock);
            close(sockfd);
            return 0;
        }
        else
        {
            printf("\nCommand received : %s", buff);
            system(buff);
            printf("\n");
        }
    }
}