#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
    int sockfd, buffsize = 1024;
    char buff[buffsize];

    struct sockaddr_in addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) > 0)
    {
        printf("\nSocket created successfully");
    }
    else
    {
        printf("\nError in creating socket\n");
        exit(0);
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(15002);

    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == 0)
    {
        printf("\nConnection established with server IP: %s.....", inet_ntoa(addr.sin_addr));
    }
    else
    {
        printf("\nError in connect\n");
        exit(0);
    }
    char command[50];

    while (1)
    {
        printf("\nEnter the command: ");
        gets(command);
        command[strlen(command)]='\0';
        printf("\nCommand: %s, length: %d",command,strlen(command));

        if (strcmp(command, "end") == 0)
        {
            send(sockfd, command, strlen(command), 0);
            close(sockfd);
            return 0;
        }

        else if (strcmp(command, "") == 0)
        {
        }
        else
        {
            send(sockfd, command, strlen(command), 0);
        }
    }

    return 0;
}