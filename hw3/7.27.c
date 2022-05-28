#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 300
#define MAXLEN 100000

typedef struct node{
    int vindex;
    struct node *next;
} NodeLink;

typedef struct {
    int vexnum, edgenum;
    struct {
        int vertex;
        int layer;
        NodeLink *first;
    } v[MAX];
} AGraph;

typedef struct QNode{
    int data;
    struct QNode *next;
} QNode;

typedef struct {
    struct QNode *front, *rear;
} LinkedQueue;

void GraphAdd(AGraph *G, char edge[], int len);
void GraphInit(AGraph *G);
int BFS(AGraph *G, int start, int end, int k);
void Enqueue(LinkedQueue *Q, int c);
void Dequeue(LinkedQueue *Q, int *c);

int visited[MAX];

int main(){
    int vtnum,k;
    scanf("%d,%d",&vtnum, &k);
    int s,t;
    scanf("%d,%d",&s,&t);
    AGraph *G=(AGraph *)malloc(sizeof(AGraph));
    // G->edgenum=ednum;
    G->vexnum=vtnum;
    GraphInit(G);
    char edges[MAXLEN];
    scanf("%s",&edges);
    int i, last;
    last=0;
    for(i=0;edges[i]!='\0';i++){
        char curedge[MAXLEN];
        while(edges[i]!=',' && edges[i]!='\0') i++;
        strncpy(curedge, edges+last, i-last);
        GraphAdd(G, curedge, i-last);
        last=i+1;
    }
    // PrintGraph(G);
    int len=BFS(G, s, t, k);
    if(len) printf("yes");
    else printf("no");
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
    // if(vex1 == 0 || vex2 == 0) G->start_mark=0;

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

    for(i=0;i<vex2;i++) ;
    p=G->v[vex2].first;
    q=(NodeLink *)malloc(sizeof(NodeLink));
    q->vindex = vex1;
    if(p->next==NULL){
        q->next = NULL;
        G->v[vex2].first->next = q;
    }else{
        while(p->next!=NULL && p->next->vindex>vex1) p=p->next;
        if(p->next==NULL || p->next->vindex<=vex1) {
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
    // G->start_mark=1;
}

int BFS(AGraph *G, int start, int end, int k){
    LinkedQueue *Q=(LinkedQueue *)malloc(sizeof(LinkedQueue));
    Q->front=Q->rear=(QNode *)malloc(sizeof(QNode));
    Q->front->next=NULL;
    if(!visited[start]){
        visited[start]=1;
        Enqueue(Q, start);
        G->v[start].layer=0;
        while(Q->front != Q->rear){
            int *u=(int *)malloc(sizeof(int));
            Dequeue(Q, u);
            int w;
            NodeLink *linkw=G->v[*u].first->next;
            while(linkw){
                w=linkw->vindex;
                if(!visited[w]){
                    visited[w]=1;
                    Enqueue(Q, w);
                    G->v[w].layer = G->v[*u].layer+1;
                    if(G->v[w].layer == k && w==end) return 1;
                    if(G->v[w].layer > k) return 0;
                }
                linkw=linkw->next;
            }
        }
        return 0;
    }
}

void Enqueue(LinkedQueue *Q, int c){
    QNode *q=(QNode *)malloc(sizeof(QNode));
    q->data=c;
    q->next=NULL;
    Q->rear->next=q;
    Q->rear=q;
}

void Dequeue(LinkedQueue *Q, int *c){
    QNode *q=Q->front->next;
    if(Q->front == Q->rear) return ;
    *c=q->data;
    Q->front->next=q->next;
    if(Q->rear==q) Q->rear=Q->front;
}