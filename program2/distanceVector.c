#include<stdio.h>
#include<stdlib.h>

int n,d[10],p[10],A[10][10];

int bellman_ford(){

    for(int i=0;i<n;i++){
        for(int u=0;u<n;u++){
            for(int v=0;v<n;v++){
                if(d[v]>d[u]+A[u][v]){
                    d[v] = d[u] +A[u][v];
                    p[v]=u;
                }
            }
        }
    }

    for(int u=0;u<n;u++){
        for(int v=0;v<n;v++){
            if(d[v]>d[u]+A[u][v]){
                printf("\nNegative cycle detected\n");
                return -1;
            }
        }
    }

    return 0;
}

int main(){

    printf("\nEnter N: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++){
            scanf("%d",&A[i][j]);
        }
    }

    for(int source = 0;source<n;source++){
        for(int destination=0;destination<n;destination++){

            for(int i=0;i<n;i++){
                d[i]=999;
                p[i]=-1;
            }
            d[source]=0;

            int valid = bellman_ford();

            if(valid==-1) return 0;

            printf("\nFrom Router%d to Router%d\n ",source+1,destination+1);
            printf("Cost: %2d | Path: ",d[destination]);

            if(destination!=source){
                int j=destination;
                while(p[j]!=-1){
                    printf("%d <- ",j+1);
                    j=p[j];
                }
            }
            printf("%d\n",source+1);


        }
    }

}