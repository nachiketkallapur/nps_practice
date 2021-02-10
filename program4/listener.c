#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<fcntl.h>

#define HELLO_PORT 12345
#define HELLO_GROUP "225.0.0.37"

int main(){

    int sockfd;
    struct sockaddr_in addr;
    struct ip_mreq mreq;

    if((sockfd=socket(AF_INET,SOCK_DGRAM,0))>0){
        printf("\nSocket created successfully\n");
    } else{
        printf("\nSocket creation failed\n");
        exit(0);
    }
    u_int yes=1;
    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0){
        printf("\nError in setsockopt\n");
        exit(0);
    }

    bzero(&addr,sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port  = htons(HELLO_PORT);

    if(bind(sockfd,(struct sockaddr*)&addr,sizeof(addr))==0){
        printf("\nBinding successfull IP:%s\n",inet_ntoa(addr.sin_addr));
    } else{
        printf("\nError in bind\n");
        exit(0);
    }

    mreq.imr_multiaddr.s_addr = inet_addr(HELLO_GROUP);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    if(setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0){
        printf("\nError in setsockopt2\n");
        exit(0);
    }
    char buff[1024];
    while(1){
        int addrlen = sizeof(addr);
        int cont = recvfrom(sockfd,buff,1024,0,(struct sockaddr*)&addr,&addrlen);

        if(cont<0){
            printf("\nError in recvfrom\n");
            close(sockfd);
            exit(0);
        }

        write(1,buff,strlen(buff));
    }
    return 0;

}