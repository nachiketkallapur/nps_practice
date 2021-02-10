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

void str_cli(int sockfd){
    int cont,buffsize=10240;
    char send_buff[buffsize],receive_buff[buffsize];

        printf("\nMe:");

    while(fgets(send_buff,buffsize,stdin)){

        send_buff[strlen(send_buff)]='\0';
        // printf("\nMe: %s\n",send_buff);

        send(sockfd,send_buff,strlen(send_buff),0);
        printf("\nServer: ");
        if((cont = recv(sockfd,receive_buff,buffsize,0))>0){
            fputs(receive_buff,stdout);
        }

        bzero(send_buff,buffsize);
        bzero(receive_buff,buffsize);
        printf("\nMe: ");



    }
}

int main(){

    int sockfd;
    struct sockaddr_in addr;

    if((sockfd=socket(AF_INET,SOCK_STREAM,0))>0){
        printf("\nSocket created succsssfully\n");
    } else {
        printf("\nError in socket creation\n");
        exit(0);
    }

    bzero(&addr,sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(15002);

    if(connect(sockfd,(struct sockaddr*)&addr,sizeof(addr)) == 0){
        printf("\nConnected to the server %s \n",inet_ntoa(addr.sin_addr));
    } else{
        printf("\nError in connect syscall\n");
    } 

    str_cli(sockfd);
    return close(sockfd);

}