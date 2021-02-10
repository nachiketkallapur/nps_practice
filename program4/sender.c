#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<string.h>

#define HELLO_PORT 12345
#define HELLO_GROUP "225.0.0.37" 

int main(){
    char message[] = "RVCE_CSE";
    message[8]='\0';
    int sockfd;
    struct sockaddr_in addr;

    if((sockfd = socket(AF_INET,SOCK_DGRAM,0))>0){
        printf("\nSocket created successfully\n");
    } else {
        printf("\nError in socket creation\n");
        exit(0);
    }

    bzero(&addr,sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(HELLO_GROUP);
    addr.sin_port = htons(HELLO_PORT);

    while(1){
        int n = sendto(sockfd,message,strlen(message),0,(struct sockaddr*)&addr,sizeof(addr));
        if(n<0){
            printf("\nError in sendto");
            // close(sockfd);
            exit(0);
        }
        sleep(1);
    }

    return 0;
}
