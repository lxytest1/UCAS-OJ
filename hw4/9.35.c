#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int main(){
    int data[MAX];
    int i;
    char c='\0';
    for(i=0; c!='\n'; i++){
        scanf("%d", &data[i]);
        c=getchar();
    }
    int n=i;
    int low, high;
    scanf("%d\n%d", &low, &high);
    for(i=0; i<n; i++){
        if(data[i] > low && data[i] < high){
            printf("%d", data[i]);
            if(data[i+1] > low && data[i+1] < high) printf(" "); 
        }
    }
}