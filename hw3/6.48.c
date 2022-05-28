#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode{
    char data;
    struct BiTNode *lchild, *rchild;
    struct BiTNode *parent;
} BiTree;

BiTree *GetTree();
BiTree *findnode(BiTree *T, char n);
int isDescendant(BiTree *ans, BiTree *des);

int main(){
    BiTree *T=(BiTree *)malloc(sizeof(BiTree));
    T=GetTree();
    char n1, n2;
    getchar();
    scanf("%c %c", &n1, &n2);
    BiTree *p1=findnode(T, n1);
    BiTree *p2=findnode(T, n2);
    BiTree *p=p1->parent;
    if(p1==T) printf("%c\n", T->data);
    while(!isDescendant(p, p2))
        p = p->parent;
    printf("%c\n",p->data);
}

BiTree *GetTree(){
    char c;
    BiTree *p;
    c=getchar();
    if(c=='^') p = NULL;
    else{
        p=(BiTree *)malloc(sizeof(BiTree));
        p->data = c;
        p->lchild = GetTree();
        p->rchild = GetTree();
        if(p->lchild) p->lchild->parent = p;
        if(p->rchild) p->rchild->parent = p;
    }
    return p;
}

BiTree *findnode(BiTree *T, char n){
    if(!T) return NULL;
    if(T->data == n) return T;
    BiTree *f;
    if(f=findnode(T->lchild, n)) return f;
    if(f=findnode(T->rchild, n)) return f;
    return NULL;
}

int isDescendant(BiTree *ans, BiTree *des){
    if(findnode(ans, des->data)) return 1;
    else return 0;
}