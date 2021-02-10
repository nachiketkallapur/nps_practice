#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<errno.h>

void str_cli(int sockfd){

    char send_buff[1024], receive_buff[1024];
    
    while(fgets(send_buff,1024,stdin)){

        send_buff[strlen(send_buff)]='\0';

        send(sockfd,send_buff,strlen(send_buff),0);

        if(recv(sockfd,receive_buff,1024,0)==0){
            printf("\nServer shutdown prematurely\n");
            close(sockfd);
            exit(0);
        }

        fputs(receive_buff,stdout);
        bzero(send_buff,1024);
        bzero(receive_buff,1024);


    }


}

int main(){

    int sockfd;
    struct sockaddr_in addr;

    if((sockfd=socket(AF_INET,SOCK_STREAM,0))>0){
        printf("\nSocket created successfully\n");
    } else {
        printf("\nError in socket\n");
        exit(0);
    }

    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(9002);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(connect(sockfd,(struct sockaddr*)&addr,sizeof(addr))==0){
        printf("\nConnected to server IP: %s\n", inet_ntoa(addr.sin_addr));
    } else {
        printf("\nError in connect\n");
        exit(0);
    }

    str_cli(sockfd);
    close(sockfd);

    return 0;

}