#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList{
    int key;
    int length;
    struct LinkedList *next;
} LinkedList;

void InitList(LinkedList *L);
void ConstructList(LinkedList *L);
LinkedList *SelectMinKey(LinkedList *Start);
void SelectSort(LinkedList *L);
void PrintList(LinkedList *L);

int main(){
    LinkedList *L=(LinkedList *)malloc(sizeof(LinkedList));
    InitList(L);
    ConstructList(L);
    SelectSort(L);
    PrintList(L);
}

void InitList(LinkedList *L){
    L->length=0;
    L->next=NULL;
}

void ConstructList(LinkedList *L){
    char c='\0';
    LinkedList *p=L, *q;
    while(c!='\n'){
        q=(LinkedList *)malloc(sizeof(LinkedList));
        scanf("%d", &q->key);
        q->next=NULL;
        c=getchar();
        p->next=q;
        p=q;
        L->length++;
    }
}

LinkedList *SelectMinKey(LinkedList *Start){
    LinkedList *p=Start;
    if(p->next==NULL) return p;
    int minkey=p->next->key;
    LinkedList *minl=p;
    p=p->next;
    while(p->next!=NULL){
        if(p->next->key < minkey){
            minl=p;
            minkey=p->next->key;
        }
        p=p->next;
    }
    return minl;
}

void SelectSort(LinkedList *L){
    int i;
    LinkedList *p, *Start=L;
    for(i=0; i<L->length; i++){
        p=SelectMinKey(Start);
        // if(p->next == NULL) return;
        if(p!=Start){
            int Startnext, pnext;
            Startnext=Start->next->key;
            pnext=p->next->key;
            Start->next->key=pnext;
            p->next->key=Startnext;
        }
        Start=Start->next;
    }
}

void PrintList(LinkedList *L){
    LinkedList *p=L->next;
    while(p){
        printf("%d", p->key);
        p=p->next;
        if(p) printf(" ");
    }
}