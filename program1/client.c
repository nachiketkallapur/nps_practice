#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>

int main(int argc, char *argv[]){
    int sockfd, newsock, buffsize=1024;
    char buff[buffsize];
    struct sockaddr_in addr;

    if(argc<3){
        printf("\nInsufficient arguments\n");
        exit(0);
    }

    if((sockfd=socket(AF_INET,SOCK_STREAM,0)) > 0){
        printf("\nSocket creation successful\n");
    } else{
        printf("\nError in socket creation\n");
        exit(0);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));

    if(inet_pton(AF_INET,argv[1],&addr.sin_addr) <=0){
        printf("\nError in inet_pton\n");
        exit(0);
    }

    if(connect(sockfd,(struct sockaddr*)&addr, sizeof(addr))==0){
        printf("\n Connection successfully established with server: %s...",inet_ntoa(addr.sin_addr));
    } else {
        printf("\nError in connect system call\n");
        exit(0);
    }

    char fname[255];
    printf("\nEnter the file name: ");
    scanf("%s",fname);
    fname[strlen(fname)]='\0';
    send(sockfd,fname,strlen(fname),0);
    int cont;

    while((cont = recv(sockfd,buff,buffsize,0)) > 0){
        buff[cont]='\0';
        printf("%s",buff);
        bzero(buff,buffsize);
    }

    printf("\nEOF\n");
    close(sockfd);

    return 0;
}
