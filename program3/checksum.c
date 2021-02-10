#include<stdio.h>
unsigned fields[10];

unsigned short checksum(){
    int i, sum=0;

    for(i=0;i<9;i++){
        printf("\nField %d: ",i+1);
        scanf("%x",fields+i);
        sum = sum + (unsigned short)fields[i];

        while(sum>>16)
            sum = (sum&0xFFFF) + (sum>>16);
    }

    sum=~sum;
    return (unsigned short)sum;
}


int main(){

    unsigned short result1, result2;

    printf("\nAt sender\n");
    result1 = checksum();
    printf("\nChecksum calculated at sender: %x",result1);
    printf("\nAt Receiver\n");
    result2 = checksum();
    printf("\nChecksum calculated at receiver: %x",result2);

    if(result1==result2)
        printf("\nNo Error\n");
    else 
        printf("\nError at data received\n");

    return 0;
}
