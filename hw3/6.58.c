#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

typedef struct BiTNode{
    int data;                     // 结点内容
    struct BiTNode *lchild, *rchild;    // 左右孩子指针
} BiTree;

void GetTree(BiTree *T, int L[], int R[], int n);
BiTree *find(BiTree *T, int d);
void inorderTraverse(BiTree *T);
BiTree *insert(BiTree *T1, BiTree *T2, int p);

int main(){
    int L1[MAX], R1[MAX], L2[MAX], R2[MAX];
    int L[MAX], R[MAX];
    int p;

    // get input
    // first tree
    int i=0, j=0;
    do{
        scanf("%d",&L1[i++]);
    }while(getchar()!='\n');
    i=0;
    do{
        scanf("%d",&R1[i++]);
    }while(getchar()!='\n');
    // pointer *p
    scanf("%d", &p);
    // second tree
    do{
        scanf("%d",&L2[j++]);
    }while(getchar()!='\n');
    j=0;
    do{
        scanf("%d",&R2[j++]);
    }while(getchar()!='\n');

    BiTree *T1, *T2;
    T1 = (BiTree *)malloc(sizeof(BiTree));
    T2 = (BiTree *)malloc(sizeof(BiTree));
    GetTree(T1, L1, R1, i-1);
    GetTree(T2, L2, R2, j-1);
    // inorderTraverse(T1);
    // printf("\n");
    // inorderTraverse(T2);
    T1 = insert(T1, T2, p);
    inorderTraverse(T1);
}

void GetTree(BiTree *T, int L[], int R[], int n){
    int p=0;
    T->data=L[p++];
    BiTree *q, *next;
    q=T;
    while(p<=n && q){
        if(L[p]){
            q->lchild = (BiTree *)malloc(sizeof(BiTree));
            q->lchild->data = L[p];
            q->lchild->lchild = q->lchild->rchild = NULL;
        }else{
            q->lchild=NULL;
        }
        if(R[p]){
            q->rchild = (BiTree *)malloc(sizeof(BiTree));
            q->rchild->data = R[p];
            q->rchild->lchild = q->rchild->rchild = NULL;
        }else{
            q->rchild=NULL;
        }
        q=find(T, ++p+T->data-1);
    }
}  

BiTree *find(BiTree *T, int d){
    if(!T) return NULL;
    if(T->data == d) return T;
    BiTree *f = (BiTree *)malloc(sizeof(BiTree));
    if(f = find(T->lchild, d)) return f;
    if(f = find(T->rchild, d)) return f;
    return NULL;
}

void inorderTraverse(BiTree *T){
    if(!T) return;
    inorderTraverse(T->lchild);
    printf("%d ", T->data);
    inorderTraverse(T->rchild);
}

BiTree *insert(BiTree *T1, BiTree *T2, int p){
    BiTree *fp=find(T1, p);
    if(fp->lchild){
        T2->rchild=fp->lchild;
        fp->lchild=T2;
    }else{
        fp->lchild=T2;
    }
    return T1;
}