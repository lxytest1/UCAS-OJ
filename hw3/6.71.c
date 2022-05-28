#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

typedef struct BiTNode{
    char data;                     // 结点内容
    int datanum, lchildnum, rchildnum;
    struct BiTNode *lchild, *rchild;    // 左右孩子指针
} BiTree;

BiTree *findchild(BiTree *T, int i, int *pos);
void PreorderTraverse(BiTree *T, int prefix);

int main(){
    BiTree *T=(BiTree *)malloc(sizeof(BiTree));
    int i=1;
    int *pos = malloc(sizeof(int));
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
    PreorderTraverse(T, 0);
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

void PreorderTraverse(BiTree *T, int prefix){
    if(!T) return;
    int i;
    for(i=prefix;i>0;i--) printf("-");
    printf("%c\n",T->data);
    PreorderTraverse(T->lchild, prefix+1);
    PreorderTraverse(T->rchild, prefix);
}