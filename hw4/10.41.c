#include <stdio.h>
#include <stdlib.h>

#define KEYNUM 1000
#define KEYRANGE 10000

typedef struct SqList{
    int length;
    int keys[KEYRANGE];
} SqList;

void GetList(SqList *L);
void MergeSort(SqList *L);
void MSort(int SR[], int TR1[], int s, int t);
void Merge(int SR[], int TR[], int i, int m, int n);
void PrintList(SqList *L);

int main(){
    SqList *L=(SqList *)malloc(sizeof(SqList));
    L->length=KEYNUM;
    GetList(L);
    MergeSort(L);
    PrintList(L);
}

void GetList(SqList *L){
    int i;
    for(i=1; i<=L->length; i++){
        scanf("%d", &L->keys[i]);
        getchar();
    }
}

void MergeSort(SqList *L){
    MSort(L->keys, L->keys, 1, L->length);
}

void MSort(int SR[], int TR1[], int s, int t){
    int TR2[KEYNUM + 1];
    if(s==t) TR1[s]=SR[s];
    else{
        int m=(s+t)/2;
        MSort(SR, TR2, s, m);
        MSort(SR, TR2, m+1, t);
        Merge(TR2, TR1, s, m, t);
    }
}

void Merge(int SR[], int TR[], int i, int m, int n){
    int j, k;
    for(j=m+1, k=i; i<=m && j<=n; k++){
        if(SR[i] <= SR[j]) TR[k] = SR[i++];
        else               TR[k] = SR[j++];
    }
    if(i<=m){
        while(k<=n) TR[k++]=SR[i++];
    }
    if(j<=n){
        while(k<=n) TR[k++]=SR[j++];
    }
}

void PrintList(SqList *L){
    int i;
    for(i=1; i<=L->length; i++){
        printf("%d", L->keys[i]);
        if(i+1<=L->length) printf(" ");
    }
}