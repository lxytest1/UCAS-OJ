#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX 100

typedef struct node {
    int vindex;
    int weight;
    struct node *next;
} NodeLink;

typedef struct {
    int vexnum;
    struct {
        int data;
        NodeLink *first;
        int mark; // 在Dijkstra算法中是(1)否(0)已经被选择
        int length; // 在Dijkstra算法中从源点到它的距离
    } v[MAX];
} AGraph;

void InitGraph(AGraph *G);
void GetEdge(char edge[], int *v1, int *v2);
void AddEdge(AGraph *G, int v1, int v2, int weight);
void Dijkstra(AGraph *G, int source);
int AllVerticesPicked(AGraph *G);
void UpdatePath(AGraph *G);


int main(){
    AGraph *G=(AGraph *)malloc(sizeof(AGraph));
    int source;
    scanf("%d %d", &G->vexnum, &source);
    getchar();
    InitGraph(G);
    char edge[MAX];
    int weight;
    while(scanf("%s %d", &edge, &weight)!=EOF){
        getchar();
        int v1, v2;
        GetEdge(edge, &v1, &v2);
        AddEdge(G, v1, v2, weight);
        // printf("%d-%d %d\n", v1, v2, weight);
        // printf("\n");
    }
    Dijkstra(G, source);
    int start = (G->v[0].first->next) ? 0 : 1;
    int i;
    for(i=0;i<G->vexnum;i++){
        if(G->v[start].length != INT_MAX && start!=source){
            printf("%d",G->v[start].length);
            if(i!=G->vexnum-1) printf(",");
        } 
        start++;
    }
    return 0;
}

void InitGraph(AGraph *G){
    int vnum=G->vexnum;
    int i;
    for(i=0;i<=vnum;i++){
        G->v[i].data=i;
        G->v[i].first=(NodeLink *)malloc(sizeof(NodeLink));
        G->v[i].first->next=NULL;
        G->v[i].mark=0;
        G->v[i].length=INT_MAX;
    }
}

void GetEdge(char edge[], int *v1, int *v2){
    int i;
    for(i=0;edge[i]!='-';i++) ;
    int len=strlen(edge);
    char vex1[MAX]="", vex2[MAX]="";
    strncpy(vex1, edge, i);
    strncpy(vex2, edge+i+1, len-i-1);
    *v1=atoi(vex1);
    *v2=atoi(vex2);
}

void AddEdge(AGraph *G, int v1, int v2, int weight){
    // NodeLink *p=(NodeLink *)malloc(sizeof(NodeLink));
    NodeLink *p=G->v[v1].first;
    while(p->next) p=p->next;
    NodeLink *q=(NodeLink *)malloc(sizeof(NodeLink));
    q->vindex=v2;
    q->weight=weight;
    q->next=NULL;
    p->next=q;

    p=G->v[v2].first;
    while(p->next) p=p->next;
    q=(NodeLink *)malloc(sizeof(NodeLink));
    q->vindex=v1;
    q->weight=weight;
    q->next=NULL;
    p->next=q;
}

void Dijkstra(AGraph *G, int source){
    G->v[source].length=0;
    G->v[source].mark=1;
    while(!AllVerticesPicked(G)) {
        UpdatePath(G);
        int i, minvex, minlen=INT_MAX;
        for(i=0;i<=G->vexnum;i++){
            if(!G->v[i].mark && G->v[i].length<minlen){
                minvex=i;
                minlen=G->v[i].length;
            }
        }
        G->v[minvex].mark=1;
    }
}

int AllVerticesPicked(AGraph *G){
    int start = (G->v[0].first->next) ? 0 : 1;
    int i;
    for(i=0;i<G->vexnum;i++){
        if(!G->v[start++].mark) return 0;
    }
    return 1;
}

void UpdatePath(AGraph *G){
    int i;
    for(i=0;i<=G->vexnum;i++){
        NodeLink *p=G->v[i].first->next;
        while(p && G->v[i].mark){
            int adj=p->vindex;
            if((G->v[adj].length > G->v[i].length + p->weight) && !G->v[adj].mark) 
                G->v[adj].length = G->v[i].length + p->weight;
            p=p->next;
        }
    }
}