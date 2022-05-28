#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct BiTree{
    char data;
    struct BiTree *lchild, *rchild;
} BiTree;

void postorderTraversal(BiTree *T);
BiTree *CreateTree(char pre[], char in[], int len);

int main(){
    char pre[MAX], in[MAX];
    scanf("%s", &pre);
    scanf("%s", &in);
    BiTree *T;
    int len = strlen(pre);
    T=CreateTree(pre, in, len);
    postorderTraversal(T);
}

BiTree *CreateTree(char pre[], char in[], int len){
    BiTree *tree = (BiTree *)malloc(sizeof(BiTree));
    tree->data = pre[0];

    if(len==0){
        return NULL;
    }else if(len==1){
        tree->lchild = tree->rchild = NULL;
    }else{
        int i;
        for(i=0;in[i] != pre[0];i++) ;
        char lin[MAX], lpre[MAX], rin[MAX], rpre[MAX];
        
        strncpy(lin, in, i);
        strncpy(rin, in+i+1, len-i-1);
        strncpy(lpre, pre+1, i);
        strncpy(rpre, pre+1+i, len-i-1);

        tree->lchild = CreateTree(lpre, lin, i);
        tree->rchild = CreateTree(rpre, rin, len-i-1);
    }
    return tree;
}

void postorderTraversal(BiTree *T){
    if(!T) return;
    postorderTraversal(T->lchild);
    postorderTraversal(T->rchild);
    printf("%c",T->data);
}