#include <stdio.h>
#include <stdlib.h>

typedef struct BiTree{
    // int tag; // -1: lchild; 1: rchild; 0: root
    int data;
    struct BiTree *lchild, *rchild;
} BiTree;

BiTree *Construct(BiTree *T);
BiTree *Merge(BiTree *T1, BiTree *T2);
void AddNode(BiTree *T, int n);
BiTree *Search(BiTree *T, BiTree *f, int n, int *res);
void MidTraverse(BiTree *T, int isroot);



int main(){
    BiTree *T1, *T2;
    T1=(BiTree *)malloc(sizeof(BiTree));
    T2=(BiTree *)malloc(sizeof(BiTree));
    T1 = Construct(T1);
    T2 = Construct(T2);
    T1 = Merge(T1, T2);
    MidTraverse(T1, 1);
    return 0;
}

BiTree *Construct(BiTree *T){
    int new;
    scanf("%d", &new);
    getchar();
    if(new==-1) T=NULL;
    else{
        T->data=new;
        T->lchild=(BiTree *)malloc(sizeof(BiTree));
        T->rchild=(BiTree *)malloc(sizeof(BiTree));
        T->lchild = Construct(T->lchild);
        T->rchild = Construct(T->rchild);
    }
    return T;
}

BiTree *Merge(BiTree *T1, BiTree *T2){
    AddNode(T1, T2->data);
    if(T2->lchild) T1=Merge(T1, T2->lchild);
    if(T2->rchild) T1=Merge(T1, T2->rchild);
    return T1;
}

void AddNode(BiTree *T, int n){
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

void MidTraverse(BiTree *T, int isroot){
    if(T->lchild) MidTraverse(T->lchild, 0);
    printf("%d", T->data);
    if(!isroot || (isroot && T->rchild)) printf(" ");
    if(T->rchild) MidTraverse(T->rchild, 0);
}