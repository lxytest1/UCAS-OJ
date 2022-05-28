#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

typedef struct BiTNode{
    struct state{
        int casenum;
        char gang;
    } state;
    struct BiTNode *lchild, *rchild, *parent;
} BiTree;

void Query(BiTree *T, int case1, int case2, char result[]);
char CheckType(BiTree *T, int case2);
void ConstructTree(BiTree *T, int n, int root);
void FindAndChnode(BiTree *T, int casenum, char gang);
void Delete(BiTree *T, int case1, int case2);

int main(){
    int group;
    scanf("%d", &group);
    int i;
    char result[MAX]="";
    for(i=group; i>0; i--){
        // ...
        BiTree *T=(BiTree *)malloc(sizeof(BiTree));
        int n, m, j;
        scanf("%d %d", &n, &m);
        getchar();
        ConstructTree(T, n, 1);
        for(j=m; j>0; j--){
            char type;
            int case1, case2;
            scanf("%c %d %d",&type, &case1, &case2);
            getchar();
            if(type == 'A') (case1 < case2) ? 
                Query(T->lchild, case1, case2, result) : 
                Query(T->lchild, case2, case1, result) ; // 可以只看一个分支，因为对称性
            if(type == 'D') (case1 < case2) ? Delete(T, case1, case2) : Delete(T, case2, case1);
        }
    }
    printf("%s", result);
}

void Query(BiTree *T, int case1, int case2, char result[]){
    int qresult = 0; // 0: 不确定 1: 是同一个 -1: 不是同一个
    if(T->state.casenum != case1){
        (T->lchild != NULL) ? 
            Query(T->lchild, case1, case2, result) :
            Query(T->rchild, case1, case2, result) ;
    }else{
        // CheckType
        char ct = CheckType(T, case2);
        if(ct == 'D'){
            strcat(result, "不确定\n");
        }else if(ct == T->state.gang){
            strcat(result, "是同一个团伙所为\n");
        }else{
            strcat(result, "不是同一个团伙所为\n");
        }
    }
}

char CheckType(BiTree *T, int case2){
    // D: 两种类型的团伙都有 A: A团伙 B: B团伙
    char ct;
    if(T->state.casenum != case2){
        if(T->lchild!=NULL && T->rchild != NULL) {
            (CheckType(T->lchild, case2) == CheckType(T->rchild, case2)) ?
                (ct = CheckType(T->lchild, case2)) : (ct = 'D');
        }
        else if(T->lchild != NULL) ct = CheckType(T->lchild, case2);
        else ct = CheckType(T->rchild, case2);
        return ct;
    }else{
        return T->state.gang;
    }
}

void ConstructTree(BiTree *T, int n, int root){
    if(n==0){
        T->lchild = T->rchild = NULL;
    // }else if(n==1){
    //     T->lchild = (BiTree *)malloc(sizeof(BiTree));
    //     T->rchild = (BiTree *)malloc(sizeof(BiTree));
    //     T->lchild->state.casenum = T->rchild->state.casenum = root;
    //     T->lchild->state.gang = 'A';
    //     T->rchild->state.gang = 'B';
    //     T->lchild->parent = T->rchild->parent = T;
    //     T->lchild->lchild = T->lchild->rchild = T->rchild->lchild = T->rchild->rchild = NULL;
    //     return T;
    }else{
        T->lchild = (BiTree *)malloc(sizeof(BiTree));
        T->rchild = (BiTree *)malloc(sizeof(BiTree));
        T->lchild->state.casenum = T->rchild->state.casenum = root;
        T->lchild->state.gang = 'A';
        T->rchild->state.gang = 'B';
        T->lchild->parent = T->rchild->parent = T;
        ConstructTree(T->lchild, n-1, root+1);
        ConstructTree(T->rchild, n-1, root+1);
    }
}

void FindAndChnode(BiTree *T, int casenum, char gang){
    if(!T){
        return;
    }else if(T->state.casenum != casenum){
        FindAndChnode(T->lchild, casenum, gang);
        FindAndChnode(T->rchild, casenum, gang);
    }else if(T->state.gang != gang){
        return;
    }else{
        if(T->state.gang == 'A') T->parent->lchild=NULL;
        else T->parent->rchild=NULL;
    }
}

void Delete(BiTree *T, int case1, int case2){
    if(!T){ // 该路分支为空
        return;
    }else if(T->lchild != NULL && T->lchild->state.casenum == 1){ // 头结点到首结点的特殊处理
        Delete(T->lchild, case1, case2);
        Delete(T->rchild, case1, case2);
    }else if(T->state.casenum != case1){  // 正式处理：如果当前指向的结点不是case1，继续寻找
        Delete(T->lchild, case1, case2);
        Delete(T->rchild, case1, case2);
    }else{
        char c = T->state.gang;
        FindAndChnode(T, case2, c);
    }
}