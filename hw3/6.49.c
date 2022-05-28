#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

typedef struct BiTNode{
    char data;                     // 结点内容
    int datanum, lchildnum, rchildnum;
    struct BiTNode *lchild, *rchild;    // 左右孩子指针
} BiTree;

BiTree *findchild(BiTree *T, int i, int *pos);
int isCompleteBTree(BiTree *T);

int main(){
    BiTree *T=(BiTree *)malloc(sizeof(BiTree));
    int i=1;
    int *pos = (int *)malloc(sizeof(int));
    BiTree *q;
    BiTree *p=T;
    while(scanf("%c %d %d",&p->data, &p->lchildnum, &p->rchildnum)!=EOF){
        getchar();
        p->datanum = i;
        p->lchild=NULL;
        p->rchild=NULL;
        q=findchild(T, i++, pos);
        if(*pos==0 && q) q->lchild = p;
        else if(*pos==1 && q) q->rchild = p;
        p=(BiTree *)malloc(sizeof(BiTree));
    }
    int m = isCompleteBTree(T);
    if(m) printf("Yes");
    else printf("No");
}

BiTree *findchild(BiTree *T, int i, int *pos){
    // pos: position, left(0) or right(1) child
    *pos = 0;
    if(!T) return NULL;
    BiTree *f;
    if(T->lchildnum == i){
        *pos = 0;
        return T;
    }else if(T->rchildnum == i){
        *pos = 1;
        return T;
    }else if(f=findchild(T->lchild, i, pos)){
        return f;
    }else if(f=findchild(T->rchild, i, pos)){
        return f;
    }else{
        return NULL;
    }
}

int isCompleteBTree(BiTree *T){
    if(!T->lchild && !T->rchild){
        return 1;
    }else if(T->lchildnum == T->datanum*2 && !T->rchild){
        if(!T->lchild->lchild && !T->lchild->rchild) return 1;
        else return 0;
    }else if(T->lchildnum == T->datanum*2 && T->rchildnum == T->datanum*2+1){
        if(isCompleteBTree(T->lchild) && isCompleteBTree(T->rchild)) return 1;
        else return 0;
    }else{
        return 0;
    }
}