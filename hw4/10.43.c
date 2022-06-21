#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int GetA(int a[]);
int CountC(int a[], int num, int length);
void PrintArr(int c[], int length);

int main(){
    int a[MAX + 1], c[MAX + 1];
    int length;
    length = GetA(a);
    int i;
    for(i=1; i<=length; i++)
        c[i] = CountC(a, i, length);
    PrintArr(c, length);
}

int GetA(int a[]){
    char c='\0';
    int i=1;
    while(c!='\n'){
        scanf("%d", &a[i++]);
        c=getchar();
    }
    return i-1;
}

int CountC(int a[], int num, int length){
    int cnt=0;
    int i;
    for(i=1; i<=length; i++){
        if(a[i]<a[num]) cnt++;
    }
    return cnt;
}

void PrintArr(int c[], int length){
    int i;
    for(i=1; i<=length; i++){
        printf("%d", c[i]);
        if(i+1 <= length) printf(" ");
    }
}