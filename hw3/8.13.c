#include <stdio.h>
#include <stdlib.h>

typedef struct LNode{
    int start;
    int size;
    struct LNode *llink, *rlink;
} Space;

void AddBlock(Space *pav, int start, int size);
int GetTag(Space *pav, int addr);
void RecycleL1R0(Space *pav, int start, int size);
void RecycleL0R1(Space *pav, int start, int size);
void RecycleL0R0(Space *pav, int start, int size);
void PrintSpace(Space *pav);

int main(){
    Space *pav = (Space *)malloc(sizeof(Space));
    pav->rlink=NULL;
    int tag, start, size;
    while(scanf("%d %d %d", &tag, &start, &size)!=EOF){
        if(!tag){
            AddBlock(pav, start, size);
        }else{
            int L=GetTag(pav, start-1);
            int R=GetTag(pav, start+size);
            if(L==1 && R==1) AddBlock(pav, start, size);
            else if(L==1 && R==0) RecycleL1R0(pav, start, size);
            else if(L==0 && R==1) RecycleL0R1(pav, start, size);
            else RecycleL0R0(pav, start, size);
        }
    }
    PrintSpace(pav);
}

void AddBlock(Space *pav, int start, int size){
    Space *p=(Space *)malloc(sizeof(Space));
    p->start=start;
    p->size=size;
    Space *q=pav;
    while(q->rlink && q->rlink->start < start) q=q->rlink;
    p->rlink=q->rlink;
    p->llink=q;
    q->rlink=p;
}

int GetTag(Space *pav, int addr){
    if(!pav->rlink || pav->rlink->start>addr) return 1;
    Space *p=pav;
    while(p->rlink && p->rlink->start <= addr) p=p->rlink;
    if(p->start <= addr && p->start+p->size-1 >= addr) return 0;
    else return 1;
}

void RecycleL1R0(Space *pav, int start, int size){
    Space *p=pav->rlink;
    while(p!=NULL && p->start!=start+size) p=p->rlink;
    p->start=start;
    p->size+=size;
}

void RecycleL0R1(Space *pav, int start, int size){
    Space *p=pav->rlink;
    while(p!=NULL && (p->start+p->size)!=start) p=p->rlink;
    p->size+=size;
}

void RecycleL0R0(Space *pav, int start, int size){
    Space *p=pav->rlink;
    while(p!=NULL && (p->start+p->size)!=start) p=p->rlink;
    Space *q=p->rlink;
    p->size = p->size + size + q->size;
    p->rlink = q->rlink;
    if(q->rlink) q->rlink->llink=p;
    free(q);
}

void PrintSpace(Space *pav){
    Space *p=pav->rlink;
    if(!p) {
        printf("0 0 0");
        return ;
    }
    while(p!=NULL){
        if(p->size) printf("0 %d %d", p->start, p->size);
        else {
            p=p->rlink;
            continue;
        }
        p=p->rlink;
        if(p) printf("\n");
    }
}