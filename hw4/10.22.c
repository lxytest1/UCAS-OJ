#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXSIZE 1000

typedef struct {
    int key;
    int next;
} SLNode;

typedef struct {
    SLNode r[MAXSIZE];
    int length;
} SLinkedList;

SLinkedList *CreateList(SLinkedList *SL, int n);
SLinkedList *ListInsertSort(SLinkedList *SL, int n);
void PrintList(SLinkedList *SL);

int main(){
    int n;
    scanf("%d\n", &n);
    SLinkedList *SL=(SLinkedList *)malloc(sizeof(SLinkedList));
    SL->length=n;
    SL=CreateList(SL, n);
    SL=ListInsertSort(SL, n);
    PrintList(SL);
    return 0;
}

SLinkedList *CreateList(SLinkedList *SL, int n){
    int i;
    for(i=1; i<=n; i++){
        scanf("%d", &SL->r[i].key);
        getchar();
        SL->r[i].next=i+1;
    }
    SL->r[i-1].next=0;
    return SL;
}

SLinkedList *ListInsertSort(SLinkedList *SL, int n){
    int i, j, k;
    SL->r[0].key=INT_MAX;
    SL->r[0].next=1;
    SL->r[1].next=0;
    for(i=2; i<=SL->length; i++){
        for(j=0, k=SL->r[0].next; SL->r[k].key <= SL->r[i].key; j=k, k=SL->r[k].next) ;
        SL->r[j].next=i;
        SL->r[i].next=k;
    }
    return SL;
}

void PrintList(SLinkedList *SL){
    int n=SL->length;
    int i;
    int nxt=SL->r[0].next;
    for(i=0; i<n; i++){
        printf("%d", SL->r[nxt].key);
        if(i!=n-1) printf(" ");
        nxt=SL->r[nxt].next;
    }
}