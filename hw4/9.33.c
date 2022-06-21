#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct BiTree{
    int data;
    struct BiTree *lchild, *rchild;
} BiTree;

BiTree *AddNode(BiTree *T, int n);
BiTree *Search(BiTree *T, BiTree *f, int n, int *res);
void PrintResult(BiTree *T, int n);

int res[MAX];
int a;

int main(){
    BiTree *T=NULL;
    // T->lchild=T->rchild=NULL;
    int new;
    do{
        scanf("%d", &new);
        T=AddNode(T, new);
    }while(getchar()!='\n');
    int query;
    scanf("%d", &query);
    PrintResult(T, query);
    int i=a-1;
    while(i>=0){
        printf("%d", res[i--]);
        if(i!=-1) printf(" ");
    }
    return 0;
}

BiTree *AddNode(BiTree *T, int n){
    BiTree *p, *s;
    int res;
    p=Search(T, NULL, n, &res);
    if(!res){
        s=(BiTree *)malloc(sizeof(BiTree));
        s->data=n;
        s->lchild = s->rchild = NULL;
        if(!p) T=s; // s为根节点
        else if(n<p->data) p->lchild=s;
        else p->rchild=s;
    }
    return T;
}

BiTree *Search(BiTree *T, BiTree *f, int n, int *res){
    if(!T) {
        *res=0;
        return f;
    }else if(T->data==n){
        *res=1;
        return T;
    }else if(T->data>n){
        return Search(T->lchild, T, n, res);
    }else{
        return Search(T->rchild, T, n, res);
    }
}

void PrintResult(BiTree *T, int n){
    if(!T) return;
    PrintResult(T->lchild, n);
    if(T->data >= n) res[a++]=T->data;
    PrintResult(T->rchild, n);
}
