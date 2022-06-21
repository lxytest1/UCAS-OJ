#include <stdio.h>
#include <stdlib.h>

typedef struct BiTree{
    int num;
    int data;
    struct BiTree *lchild, *rchild;
} BiTree;

BiTree *FindNum(BiTree *T, int num);
BiTree *Add(BiTree *p, int data, int lnum, int rnum);
int isBSTree(BiTree *T);

int main(){
    BiTree *T=(BiTree *)malloc(sizeof(BiTree)), *p;
    T->num=0;
    int num=0, data, lnum, rnum;
    while((scanf("%d %d %d", &data, &lnum, &rnum))!=EOF){
        p=FindNum(T, num++);
        p=Add(p, data, lnum, rnum);
    }
    printf("%d", isBSTree(T));
    return 0;
}

BiTree *FindNum(BiTree *T, int num){
    if(!T || T->num==num) return T;
    else if(FindNum(T->lchild, num)) return FindNum(T->lchild, num);
    else return FindNum(T->rchild, num);
}

BiTree *Add(BiTree *p, int data, int lnum, int rnum){
    p->data=data;
    if(lnum!=-1){
        p->lchild=(BiTree *)malloc(sizeof(BiTree)); 
        p->lchild->num=lnum;
        p->lchild->lchild=NULL;
        p->lchild->rchild=NULL;
    }else p->lchild=NULL;
    if(rnum!=-1){
        p->rchild=(BiTree *)malloc(sizeof(BiTree));
        p->rchild->num=rnum;
        p->rchild->lchild=NULL;
        p->rchild->rchild=NULL;
    }else p->rchild=NULL;
    return p;
}

int isBSTree(BiTree *T){
    if(!T) return 1;
    else{
        if(((T->lchild && T->lchild->data < T->data) || !T->lchild) &&
           ((T->rchild && T->rchild->data > T->data) || !T->rchild)){
            return isBSTree(T->lchild) && isBSTree(T->rchild);
        }
        else return 0;
    }
}