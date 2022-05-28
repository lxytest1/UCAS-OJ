#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3000

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

void CreateGraph(AGraph *G, int s[], int fst[], int lst[], int max, int n);
int DFS(AGraph *G, int start, int end);
int isPost(AGraph *G, int i, int j);
int Circuit(AGraph *G);

int main(){
    int n;
    int max=0;
    scanf("%d", &n);
    int s[MAX];
    int fst[n+1], lst[n+1];
    do{
        scanf("%d", &s[max++]);
    }while(getchar()!='\n');
    int i;
    for(i=0;i<=n;i++){
        scanf("%d", &fst[i]);
        // getchar();
    }
    for(i=0;i<=n;i++){
        scanf("%d", &lst[i]);
        // getchar();
    }

    AGraph *G=(AGraph *)malloc(sizeof(AGraph));
    CreateGraph(G, s, fst, lst, max, n);
    if(Circuit(G)) printf("yes");
    else printf("no");
}

void CreateGraph(AGraph *G, int s[], int fst[], int lst[], int max, int n){
    G->vexnum=n;
    G->edgenum=0;
    int i;
    for(i=1;i<=n;i++){
        int l=lst[i];
        int f=fst[i];
        int j;
        G->v[i].vertex=i;
        G->v[i].first=(NodeLink *)malloc(sizeof(NodeLink));
        NodeLink *q=G->v[i].first;
        q->next=NULL;
        for(j=f;j<l;j++){
            G->edgenum++;
            NodeLink *p=(NodeLink *)malloc(sizeof(NodeLink));
            p->vindex=s[j];
            p->next=q->next;
            q->next=p;
            // free(p);
        }
        // free(q);
    }
}

int DFS(AGraph *G, int start, int end){
    NodeLink *p;
    // int path=0;
    visited[start]=1;
    if(start==end){
        return 1;
    }
    p=G->v[start].first->next;
    while(p){
        if(!visited[p->vindex])
            if(DFS(G, p->vindex, end)) return 1;
        p=p->next;
    }
    return 0;
}

int isPost(AGraph *G, int i, int j){
    // j 是 i 的后继
    NodeLink *p=G->v[i].first->next;
    while(p!=NULL){
        if(p->vindex==j) return 1;
        p=p->next;
    }
    return 0;
}

int Circuit(AGraph *G){
    int n=G->vexnum;
    int i, j;
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(i==j) continue;
            if(DFS(G, i, j) && isPost(G, j, i
            )) return 1;

            int m;
            for(m=0;m<=n;m++){
                visited[m]=0;
            }
        }
    }
    return 0;
}