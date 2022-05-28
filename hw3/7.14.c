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
    int start_mark;
} AGraph;

void GraphAdd(AGraph *G, char edge[], int len);
void GraphInit(AGraph *G);
void PrintGraph(AGraph *G);

int main(){
    int vtnum,ednum;
    scanf("%d,%d",&vtnum, &ednum);
    AGraph *G=(AGraph *)malloc(sizeof(AGraph));
    G->edgenum=ednum;
    G->vexnum=vtnum;
    GraphInit(G);
    char edges[MAXLEN];
    if(ednum!=0) scanf("%s",&edges);
    int i, last;
    last=0;
    for(i=0;edges[i]!='\0';i++){
        char curedge[MAXLEN];
        while(edges[i]!=',' && edges[i]!='\0') i++;
        strncpy(curedge, edges+last, i-last);
        GraphAdd(G, curedge, i-last);
        last=i+1;
    }
    // freopen("E:\\lxy\\a_courseware\\2_sem2\\data_structure\\hw3\\out.txt","w",stdout);
    PrintGraph(G);
    // fclose(stdout);
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
    if(vex1 == 0 || vex2 == 0) G->start_mark=0;

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

    // for(i=0;i<vex2;i++) ;
    // p=G->v[vex2].first->next;
    // q=(NodeLink *)malloc(sizeof(NodeLink));
    // q->vindex = vex1;
    // if(p==NULL){
    //     q->next = NULL;
    //     G->v[vex2].first->next = q;
    // }else{
    //     while(p->next!=NULL && p->next->vindex>vex1) p=p->next;
    //     if(p->next==NULL || p->next->vindex<vex1) {
    //         q->next = p->next;
    //         p->next = q;
    //     }
    // }
}

void GraphInit(AGraph *G){
    int i;
    for(i=0;i<=G->vexnum;i++){
        G->v[i].vertex = i;
        G->v[i].first = (NodeLink *)malloc(sizeof(NodeLink));
        G->v[i].first->next=NULL;
        G->v[i].first->vindex=MAX;
    }
    G->start_mark=1;
}

void PrintGraph(AGraph *G){
    int start;
    start = (G->start_mark) ? 1:0;
    int i;
    for(i=0;i<G->vexnum;i++,start++){
        NodeLink *p=G->v[start].first;
        printf("%d",start);
        if(p->next!=NULL) printf(" ");
        while(p!=NULL){
            if(p->vindex!=MAX) printf("%d",p->vindex);
            if(p->vindex!=MAX && p->next!=NULL) printf(",");
            p=p->next;
        }
        if(i!=G->vexnum-1) printf("\n");
    }
}