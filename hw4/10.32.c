#include <stdio.h>
#include <stdlib.h>

int main(){
    int i=0, j=0, k=0;
    char c='\0';
    int num;
    while(c!='\n'){
        scanf("%d", &num);
        c=getchar();
        if(num==1) i++;
        else if(num==2) j++;
        else if(num==3) k++;
    }
    while(i--!=0) printf("1 ");
    while(j--!=0) printf("2 ");
    while(k--!=0){
        printf("3");
        if(k!=0) printf(" ");
    }
}