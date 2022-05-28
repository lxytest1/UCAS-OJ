#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 300

typedef struct node{
    int vindex;
    struct node *next;
} NodeLink;

typedef struct {
    int vexnum;
    struct {
        char data;
        NodeLink *first;
    } v[MAX];
} AGraph;

void PrintReversePoland(AGraph *G, int start);

int main(){
    AGraph *G=(AGraph *)malloc(sizeof(AGraph));
    scanf("%d", &G->vexnum);
    getchar();
    int num;
    char c;
    for(num=0;num<G->vexnum;num++){
        c=getchar();
        G->v[num].data=c;
        G->v[num].first=(NodeLink *)malloc(sizeof(NodeLink));
        NodeLink *p=G->v[num].first;
        p->next=NULL;
        while(getchar()!='\n'){
            NodeLink *q=(NodeLink *)malloc(sizeof(NodeLink));
            scanf("%d", &q->vindex);
            q->next=NULL;
            p->next=q;
            p=q;
        }
    }
    PrintReversePoland(G, 0);
    return 0;
}

void PrintReversePoland(AGraph *G, int start){
    NodeLink *q=G->v[start].first->next;
    if(q) {
        PrintReversePoland(G, q->next->vindex);
        PrintReversePoland(G, q->vindex);
    }
    printf("%c", G->v[start].data);
}