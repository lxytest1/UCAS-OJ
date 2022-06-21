#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct SqList{
    int keys[MAX];
    int length;
} SqList;

void GetList(SqList *L);
void PrintList(SqList *L);
void MergeSort(SqList *L);
void MSort(int SR[], int TR1[], int s, int t);
void Merge(int SR[], int TR[], int i, int m, int n);

int main(){
    SqList *L=(SqList *)malloc(sizeof(SqList));
    scanf("%d", &L->length);
    getchar();
    GetList(L);
    MergeSort(L);
    PrintList(L);
    return 0;
}

void GetList(SqList *L){
    int i;
    for(i=1; i<=L->length; i++){
        scanf("%d", &L->keys[i]);
        getchar();
    }
}

void PrintList(SqList *L){
    int i;
    for(i=1; i<=L->length; i++){
        printf("%d", L->keys[i]);
        if(i+1<=L->length) printf(" ");
    }
}

void MergeSort(SqList *L){
    int TR1[MAX];
    MSort(L->keys, TR1, 1, L->length);
    // int i;
    // for(i=1; i<=L->length; i++){
    //     L->keys[i]=TR1[i];
    // }
}

void MSort(int SR[], int TR1[], int s, int t){
    if(s==t) TR1[s]=SR[s];
    else{
        int i, last, m1, m2;
        do{
            for(i=s+1, last=s; SR[i]>=SR[last] && i<=t; i++, last++) ;
            m1=last;
            if(m1==t){
                // int k;
                // for(k=s; k<=t; k++) TR1[k]=SR[k];
                return ;
            }
            if(m1==t-1) m2=t;
            else {
                for(i=m1+2, last=m1+1; SR[i]>=SR[last] && i<=t; i++, last++) ; 
                m2=last;
            }
            Merge(SR, TR1, s, m1, m2);
            for(i=s; i<=m2; i++)  SR[i]=TR1[i];
        }while(m2!=t);
    }
}

void Merge(int SR[], int TR[], int i, int m, int n){
    int j, k;
    for(j=m+1, k=i; i<=m && j<=n; k++){
        if(SR[i] <= SR[j]) TR[k]=SR[i++];
        else TR[k]=SR[j++];
    }
    if(i<=m){
        while(k<=n) TR[k++]=SR[i++];
    }
    if(j<=n){
        while(k<=n) TR[k++]=SR[j++];
    }
}