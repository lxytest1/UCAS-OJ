#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 300000
#define MAXLEN 100000

typedef struct node{
    int vindex;
    struct node *next;
} NodeLink;

typedef struct {
    int vexnum, edgenum;
    struct {
        int vertex;
        NodeLink *first;
    } v[MAX];
} AGraph;

int visited[MAX];

void GraphAdd(AGraph *G, char edge[], int len);
void GraphInit(AGraph *G);
int DFS(AGraph *G, int start, int end);

int main(){
    int vtnum;
    scanf("%d",&vtnum);
    AGraph *G=(AGraph *)malloc(sizeof(AGraph));
    // G->edgenum=ednum;
    G->vexnum=vtnum;
    GraphInit(G);
    char edges[MAXLEN];
    scanf("%s",&edges);
    int start, end;
    scanf("%d,%d", &start, &end);
    int i, last;
    last=0;
    for(i=0;edges[i]!='\0';i++){
        char curedge[MAXLEN];
        while(edges[i]!=',' && edges[i]!='\0') i++;
        strncpy(curedge, edges+last, i-last);
        GraphAdd(G, curedge, i-last);
        last=i+1;
    }

    // DFS
    if(start==end || !DFS(G, start, end)) printf("no");
    else printf("yes");
}

void GraphAdd(AGraph *G, char edge[], int len){
    char v1[MAX]="", v2[MAX]="";
    int i;
    for(i=0;edge[i]!='-';i++) ;
    strncpy(v1, edge, i);
    strncpy(v2, edge+i+1, len-i-1);
    int vex1, vex2;
    vex1=atoi(v1);
    vex2=atoi(v2);

    for(i=0;i<vex1;i++) ;
    NodeLink *p=G->v[vex1].first;
    NodeLink *q=(NodeLink *)malloc(sizeof(NodeLink));
    q->vindex = vex2;
    if(p->next==NULL){
        q->next = NULL;
        G->v[vex1].first->next = q;
    }else{
        while(p->next!=NULL && p->next->vindex>vex2) p=p->next;
        if(p->next==NULL || p->next->vindex<=vex2) {
            q->next = p->next;
            p->next = q;
        }
    }
}

void GraphInit(AGraph *G){
    int i;
    for(i=0;i<=G->vexnum;i++){
        G->v[i].vertex = i;
        G->v[i].first = (NodeLink *)malloc(sizeof(NodeLink));
        G->v[i].first->next=NULL;
        G->v[i].first->vindex=MAX;
    }
}

int DFS(AGraph *G, int start, int end){
    NodeLink *p;
    // int path=0;
    visited[start]=1;
    if(start==end){
        return 1;
    }
    p=G->v[start].first;
    while(p){
        if(!visited[p->vindex])
            if(DFS(G, p->vindex, end)) return 1;
        p=p->next;
    }
    return 0;
}