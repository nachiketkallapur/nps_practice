#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<string.h>

void str_cli(int sockfd){
    char send_buff[1024],receive_buff[1024];
    int cont;

    while(fgets(send_buff,1024,stdin)){
        send_buff[strlen(send_buff)]='\0';
        send(sockfd,send_buff,strlen(send_buff),0);
        if(recv(sockfd,receive_buff,1024,0)==0){
            printf("\nServer terminated prematurely\n");
            exit(0);
        }

        fputs(receive_buff,stdout);
        bzero(receive_buff,1024);
        bzero(send_buff,1024);
    }
}

int main(){

    int sockfd;
    struct sockaddr_in addr;

    if((sockfd=socket(AF_INET,SOCK_STREAM,0))>0){
        printf("\nSocket created successfully");
    } else {
        printf("\nError in socket creation\n");
        exit(0);
    }
    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    addr.sin_port = htons(9002);

    if(connect(sockfd,(struct sockaddr*)&addr,sizeof(addr)) == 0){
        printf("\nConnection succesfully established with the server %s...\n",inet_ntoa(addr.sin_addr));
    } else {
        printf("\nError in connect syscall\n");
        exit(0);
    }
    
    
    str_cli(sockfd);
    close(sockfd);
    return 0;
}