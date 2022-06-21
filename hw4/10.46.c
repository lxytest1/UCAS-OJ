#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int main(){
    int length;
    scanf("%d", &length);
    getchar();
    int a[MAX];
    GetElem(a, length);
    Arrange(a, length);
    PrintElem(a, length);
}

void GetElem(int a[], int length){
    int i=1;
    while(i<=length){
        scanf("%d", &a[i++]);
        getchar();
    }
}

void Arrange(int a[], int length){
    int i, j, tmp;
    if(length == 1) return;
    for(i=1, j=2; j<=length; i++, j++){
        if(a[i]>a[j]){
            tmp=a[i];
            a[i]=a[j];
            a[j]=tmp;
        }
    }
    Arrange(a, length-1);
}

void PrintElem(int a[], int length){
    int i=1;
    while(i<=length){
        printf("%d", a[i++]);
        if(i<=length) printf(" ");
    }
}