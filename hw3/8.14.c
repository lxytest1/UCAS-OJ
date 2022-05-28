#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 16
#define MAX 500

typedef struct WORD_b{
    struct WORD_b *llink, *rlink;
    int start;
    int size;
} WORD_b;

typedef struct HeadNode{
    struct {
        int num;
        WORD_b *first;
    } node[M+1];
} FreeList;

int main(){
    char c;
    FreeList *FL=(FreeList *)malloc(sizeof(FreeList));
    InitList(FL);
    while(1){
        char tmp[MAX]="";
        int offset=0;
        fgets(tmp, MAX, stdin);
        if(!strcmp(tmp, "\n")) break;
        // printf("%s",tmp);
        int i=0;
        int k, start;
        char sk[MAX]="", sstart[MAX]="";
        while(tmp[i]!=' ') i++;
        strncpy(sk, tmp, i);
        k=atoi(sk);
        offset=i++;
        while(1){
            while(tmp[i]!=' ' && tmp[i] !='\n') i++;
            strncpy(sstart, tmp+offset+1, i-offset-1);
            start=atoi(sstart);
            AddNode(FL, start, k);
            if(tmp[i]=='\n') break;
            offset=i++;
        }
    }

    while(1){
        char tmp[MAX]="";
        int offset=0;
        if(fgets(tmp, MAX, stdin)=='\0') break;
        // if(tmp[0] == EOF) break;
        int i=0;
        int k, start;
        char sk[MAX]="", sstart[MAX]="";
        while(tmp[i]!=' ') i++;
        strncpy(sk, tmp, i);
        k=atoi(sk);
        offset=i++;
        while(1){
            while(tmp[i]!=' ' && tmp[i] !='\n') i++;
            strncpy(sstart, tmp+offset+1, i-offset-1);
            start=atoi(sstart);
            AddNode(FL, start, k);
            if(tmp[i]=='\n') break;
            offset=i++;
        }
    }

    int *k=(int *)malloc(sizeof(int));
    int *addr1=(int *)malloc(sizeof(int));
    int *addr2=(int *)malloc(sizeof(int));
    // int *k, *addr1, *addr2;
    while(CheckMerge(FL, k, addr1, addr2)){
        MergeNode(FL, *k, *addr1, *addr2);
    }
    PrintList(FL);
}

void InitList(FreeList *FL){
    int i;
    for(i=0;i<M+1;i++){
        FL->node[i].num=0;
        FL->node[i].first=(WORD_b *)malloc(sizeof(WORD_b));
        FL->node[i].first->rlink=NULL;
    }
}

void AddNode(FreeList *FL, int start, int k){
    FL->node[k].num++;
    WORD_b *p=FL->node[k].first;
    while(p->rlink!=NULL && p->rlink->start < start) p=p->rlink;
    WORD_b *w=(WORD_b *)malloc(sizeof(WORD_b));
    w->start=start;
    w->size=pow(2, k);
    w->rlink=p->rlink;
    w->llink=p;
    if(p->rlink) p->rlink->llink=w;
    p->rlink=w;
}

int CheckMerge(FreeList *FL, int *k, int *addr1, int *addr2){
    for(*k=0;(*k) < M+1; (*k)++){
        WORD_b *p=FL->node[*k].first->rlink;
        if(p==NULL) continue;
        while(p->rlink!=NULL){
            if(!(p->start % (int)(pow(2, (*k)+1))) && p->rlink->start == p->start + p->size){
                *addr1=p->start;
                *addr2=p->rlink->start;
                FL->node[*k].num-=2;
                return 1;
            }
            p=p->rlink;
        }
    }
    return 0;
}

void MergeNode(FreeList *FL, int k, int addr1, int addr2){
    WORD_b *p=FL->node[k].first->rlink;
    if(p->start!=addr1) p=p->rlink;
    WORD_b *pr=p->rlink->rlink;
    WORD_b *pl=p->llink;
    pl->rlink=pr;
    if(pr) pr->llink=pl;
    AddNode(FL, addr1, k+1);
}

void PrintList(FreeList *FL){
    int i;
    for(i=0;i<M+1;i++){
        if(!FL->node[i].num) continue;
        WORD_b *p=FL->node[i].first->rlink;
        printf("%d ", i);
        while(p){
            printf("%d", p->start);
            p=p->rlink;
            if(p) printf(" ");
        }
        printf("\n");
    }
}