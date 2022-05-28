#include <stdio.h>
#include <stdlib.h>

typedef struct LNode{
    int start;
    int size;
    struct LNode *llink, *rlink;
} Space;

int GetTag(Space *pav, int addr);
void AddBlock(Space *pav, int start, int size);
void RecycleL0R1(Space *pav, int start, int size);
void PrintSpace(Space *pav);

int main(){
    int low, high, blocksize;
    scanf("%d %d %d", &low, &high, &blocksize);
    getchar();
    char c;
    int cnt=low;
    Space *pav=(Space *)malloc(sizeof(Space));
    pav->rlink=NULL;
    do{
        c=getchar();
        if(c == '0'){
            if(!GetTag(pav, cnt-1)) RecycleL0R1(pav, cnt, blocksize);
            else AddBlock(pav, cnt, blocksize);
        }
        cnt+=blocksize;
    }while((getchar()) != '\n');
    PrintSpace(pav);
}

int GetTag(Space *pav, int addr){
    if(!pav->rlink || pav->rlink->start>addr) return 1;
    Space *p=pav;
    while(p->rlink && p->rlink->start <= addr) p=p->rlink;
    if(p->start <= addr && p->start+p->size-1 >= addr) return 0;
    else return 1;
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

void RecycleL0R1(Space *pav, int start, int size){
    Space *p=pav->rlink;
    while(p!=NULL && (p->start+p->size)!=start) p=p->rlink;
    p->size+=size;
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