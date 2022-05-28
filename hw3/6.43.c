#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

int main(){
    int L[MAX], R[MAX];
    int i=0;
    do{
        scanf("%d",&L[i++]);
    }while(getchar()!='\n');
    i=0;
    do{
        scanf("%d",&R[i++]);
    }while(getchar()!='\n');
    
    int j;
    for(j=0;j<i-1;j++){
        printf("%d ",R[j]);
    }
    printf("%d\n", R[j]);
    for(j=0;j<i-1;j++){
        printf("%d ",L[j]);
    }
    printf("%d\n", R[j]);
    return 0;
}