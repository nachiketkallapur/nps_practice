#include<stdio.h>
#include<stdlib.h>

int main(){
    int data[8];
    printf("\nEnter 4(d3,d5,d6,d7) data at sender: ");
    scanf("%d",data+3);
    scanf("%d",data+5);
    scanf("%d",data+6);
    scanf("%d",data+7);

    data[1] = (data[3]+data[5]+data[7])%2;
    data[2] = (data[3]+data[6]+data[7])%2;
    data[4] = (data[5]+data[6]+data[7])%2;

    int data_recv[8];
    printf("\nInput data received: ");
    for(int i=7;i>=1;i--) scanf("%d",data_recv+i);

    int s0 = (data_recv[3]+data_recv[5]+data_recv[7]+data_recv[1])%2;
    int s1 = (data_recv[3]+data_recv[6]+data_recv[7]+data_recv[2])%2;
    int s2 = (data_recv[5]+data_recv[6]+data_recv[7]+data_recv[4])%2;

    int s = s0 + 2*s1 +4*s2;

    if(s==0){
        printf("\nNo error");
    } else {
        printf("\nError in bit number %d",s);

        if(data_recv[s]==0) data_recv[s]=1;
        else if(data_recv[s]==1) data_recv[s]=0;

        printf("\nCorrect data: ");
        for(int i=7;i>=1;i--) printf("%d",data_recv[i]);
        printf("\n");
    }


    return 0;
}