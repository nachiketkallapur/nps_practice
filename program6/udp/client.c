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

void dg_cli(int sockfd,struct sockaddr* cli, int clilen){
    int buffsize = 1024,cont;
    char send_buff[buffsize],receive_buff[buffsize];

    while(fgets(send_buff,buffsize,stdin)){
        send_buff[strlen(send_buff)]='\0';

        sendto(sockfd,send_buff,strlen(send_buff),0,cli,clilen);

        if((cont = recvfrom(sockfd,receive_buff,buffsize,0,cli,&clilen)) == 0){
            printf("\nServer exited prematurely\n");
            exit(0);
        }

        fputs(receive_buff,stdout);
        bzero(receive_buff,buffsize);
        bzero(send_buff,buffsize);
    }


}

int main(){
    int sockfd;
    struct sockaddr_in addr;

    sockfd = socket(AF_INET,SOCK_DGRAM,0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(15001);

    dg_cli(sockfd,(struct sockaddr*)&addr,sizeof(addr));


}