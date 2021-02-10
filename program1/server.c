#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

int main(int argc, char *argv[]){
    if(argc< 3){
        printf("\nInsufficient aarguments\n");
        exit(0);
    }

    int sockfd, newsock, buffsize=1024;
    char buff[buffsize];

    struct sockaddr_in addr;

    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) > 0){
        printf("\n Socket created successfuly");
    } else {
        printf("\nSocket creation failed\n");
        exit(0);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    if(inet_pton(AF_INET,argv[1],&addr.sin_addr) <=0){
        printf("\nError in inet_pton\n");
        exit(0);
    }

    if(bind(sockfd,(struct sockaddr*)&addr,sizeof(addr))==0){
        printf("\nBinding socket to IP: %s ...,port: %d ...",inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));
    } else{
        printf("\nError in bind\n");
        exit(0);
    }

    listen(sockfd,3);
    int addrlen = sizeof(addr);
    if((newsock=accept(sockfd,(struct sockaddr*)&addr,&addrlen))>0){
        printf("\nClient %s is connected...",inet_ntoa(addr.sin_addr));
    } else {
        printf("\nError in accept call\n");
        exit(0);
    }

    char fname[255];
    int cont = recv(newsock,fname,255,0);
    // fname[cont]='\0';

    printf("\nFile requested is : %s..",fname);

    int fd;

    if((fd=open(fname,O_RDONLY))<0){
        printf("\nFailed to open file\n");
        exit(0);
    }
    
    while((cont = read(fd,buff,buffsize)) > 0){
        printf("\nReading contents of the file....");
        printf("\nSending file contents to client..\n");
        send(newsock,buff,cont,0);
    }

    close(newsock);
    close(sockfd);

    return 0;
}
