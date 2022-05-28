#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

typedef struct{
    int vernum;         // 顶点数
    int A[MAX][MAX];            // 存放边的信息
} MGraph;

void InsertVex(MGraph *G, int v);
void InsertArc(MGraph *G, int v, int w);
void DeleteVex(MGraph *G, int v);
void DeleteArc(MGraph *G, int v, int w);
void PrintGraph(MGraph *G);

int main(){
    MGraph *G=(MGraph *)malloc(sizeof(MGraph));
    int v;
    scanf("%d", &v);
    getchar();
    G->vernum=v;
    int i, j;
    for(i=0;i<v;i++){
        for(j=0;j<v;j++){
            G->A[i][j]=getchar()-'0';
            getchar();
        }
    }
    char op[MAX];
    while(scanf("%s",&op)!=EOF){
        char opcode[MAX]="", op1[MAX]="", op2[MAX]="";
        strncpy(opcode, op, 2);
        int operand1, operand2;
        if(!strcmp(op, "IV") || !strcmp(opcode, "DV")) {
            scanf("%s", &op1);
            getchar();
            operand1 = atoi(op1);
            if(!strcmp(opcode, "IV")) InsertVex(G, operand1);
            else DeleteVex(G, operand1);
        } else if(!strcmp(opcode, "IA") || !strcmp(opcode, "DA")){
            scanf("%s %s", &op1, &op2);
            getchar();
            operand1 = atoi(op1);
            operand2 = atoi(op2);
            if(!strcmp(opcode, "IA")) InsertArc(G, operand1, operand2);
            else DeleteArc(G, operand1, operand2);
        }
        strcpy(op, "");
    }
    PrintGraph(G);
}

void InsertVex(MGraph *G, int v){
    G->vernum++;
    int B[MAX][MAX];
    int i,j;
    for(i=0;i<G->vernum;i++){
        B[i][v]=0;
    }
    for(j=0;j<G->vernum;j++){
        B[v][j]=0;
    }
    for(i=0;i<v;i++){
        for(j=0;j<v;j++){
            B[i][j]=G->A[i][j];
        }
    }
    for(i=v+1;i<G->vernum;i++){
        for(j=0;j<v;j++){
            B[i][j]=G->A[i-1][j];
        }
    }
    for(i=0;i<v;i++){
        for(j=v+1;j<G->vernum;j++){
            B[i][j]=G->A[i][j-1];
        }
    }
    for(i=v+1;i<G->vernum;i++){
        for(j=v+1;j<G->vernum;j++){
            B[i][j]=G->A[i-1][j-1];
        }
    }
    for(i=0;i<G->vernum;i++){
        for(j=0;j<G->vernum;j++){
            G->A[i][j]=B[i][j];
        }
    }
}

void InsertArc(MGraph *G, int v, int w){
    G->A[v][w]++;
    G->A[w][v]++;
}

void DeleteVex(MGraph *G, int v){
    G->vernum--;
    int B[MAX][MAX];
    int i,j;
    for(i=0;i<v;i++){
        for(j=0;j<v;j++){
            B[i][j]=G->A[i][j];
        }
    }
    for(i=v;i<G->vernum;i++){
        for(j=0;j<v;j++){
            B[i][j]=G->A[i+1][j];
        }
    }
    for(i=0;i<v;i++){
        for(j=v;j<G->vernum;j++){
            B[i][j]=G->A[i][j+1];
        }
    }
    for(i=v;i<G->vernum;i++){
        for(j=v;j<G->vernum;j++){
            B[i][j]=G->A[i+1][j+1];
        }
    }
    for(i=0;i<G->vernum;i++){
        for(j=0;j<G->vernum;j++){
            G->A[i][j]=B[i][j];
        }
    }
}

void DeleteArc(MGraph *G, int v, int w){
    G->A[v][w]--;
    G->A[w][v]--;
}

void PrintGraph(MGraph *G){
    int i, j;
    for(i=0;i<G->vernum;i++){
        for(j=0;j<G->vernum;j++){
            printf("%d", G->A[i][j]);
            if(j!=G->vernum-1) printf(" ");
        }
        if(i!=G->vernum-1) printf("\n");
    }
}