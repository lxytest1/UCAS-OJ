#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int GetElem(int a[]);
void Arrange(int a[], int length);
void PrintElem(int a[], int length);

int main(){
    int a[MAX];
    int length=GetElem(a);
    Arrange(a, length);
    PrintElem(a, length);
    return 0;
}

int GetElem(int a[]){
    int i=1, length=0;
    char c='\0';
    while(c!='\n'){
        scanf("%d", &a[i++]);
        c=getchar();
        length++;
    }
    return length;
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