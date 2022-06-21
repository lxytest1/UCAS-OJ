#include <stdio.h>
#include <stdlib.h>

typedef struct qa{
    int query;
    int answer;
    struct qa *next;
} qa;

typedef struct LinkedList{
    int data;
    struct LinkedList *next;
} LinkedList;

LinkedList *CreateList(LinkedList *L);
qa *CreateQA(qa *qaSeries);
int inList(LinkedList *L, int query, LinkedList *h, LinkedList *t);

int main(){
    LinkedList *L=(LinkedList *)malloc(sizeof(LinkedList));
    L=CreateList(L);
    LinkedList *h, *t;
    h = t = L;
    qa *qaSeries=(qa *)malloc(sizeof(qa));
    qaSeries=CreateQA(qaSeries);
    qa *pqa=qaSeries->next;
    while(pqa){
        pqa->answer=inList(L, pqa->query, h, t);
        pqa=pqa->next;
    }
    pqa=qaSeries->next;
    while(pqa){
        printf("%d", pqa->answer);
        if(pqa->next) printf(" ");
        pqa=pqa->next;
    }
}

LinkedList *CreateList(LinkedList *L){
    LinkedList *p=L;
    p->next=NULL;
    do{
        LinkedList *q=(LinkedList *)malloc(sizeof(LinkedList));
        scanf("%d", &q->data);
        q->next=NULL;
        p->next=q;
        p=p->next;
    }while(getchar()!='\n');
    return L;
}

qa *CreateQA(qa *qaSeries){
    qa *p=qaSeries;
    p->next=NULL;
    do{
        qa *q=(qa *)malloc(sizeof(qa));
        scanf("%d", &q->query);
        q->next=NULL;
        p->next=q;
        p=p->next;
    }while(getchar()!='\n');
    return qaSeries;
}

int inList(LinkedList *L, int query, LinkedList *h, LinkedList *t){
    LinkedList *start;
    if(query==t->data){
        return 1;
    }else if(query>t->data){
        start=t->next;
    }else{
        start=h;
    }

    while(start){
        if(query==start->data) return 1;
        start=start->next;
    }
    return 0;
}