#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

void dg_echo(int sockfd){
    struct sockaddr_in cli;
    int clilen = sizeof(cli);
    int cont;
    int buffsize=1024;
    char buff[buffsize];
    while(1){
        cont = recvfrom(sockfd,buff,buffsize,0,(struct sockaddr*)&cli,&clilen);
        sendto(sockfd,buff,strlen(buff),0,(struct sockaddr*)&cli,clilen);
        bzero(buff,buffsize);
    }
}

int main(){

    int sockfd;
    struct sockaddr_in addr;

    sockfd = socket(AF_INET,SOCK_DGRAM,0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(15001);

    bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));

    dg_echo(sockfd);

    return close(sockfd);
    
}