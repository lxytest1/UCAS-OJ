#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 100
#define INCREMENT 10

typedef struct{
    int top;
    int stacksize;
    int *base;
}SqStack;

typedef struct{
    int key;
} RcdType;

typedef struct{
    RcdType r[INITSIZE];
    int length;
} SqList;

SqList *QuickSort(SqList *L, SqStack *S);
SqList *GetList(SqList *L);
void InitList(SqList *L);
int InitStack(SqStack *s);
int push(SqStack *s, int e);
int pop(SqStack *s, int *e);
void PrintList(SqList *L);

int main(){
    SqStack *S=(SqStack *)malloc(sizeof(SqStack));
    InitStack(S);
    SqList *L=(SqList *)malloc(sizeof(SqList));
    InitList(L);
    L=GetList(L);
    L=QuickSort(L, S);
    PrintList(L);
}

SqList *QuickSort(SqList *L, SqStack *S){
    int low=1, high=L->length;
    int pivotkey;
    int stacknotempty=1;
    while(low<high && stacknotempty){
        while(high-low>=2){
            // ---partition
            int tmplow=low, tmphigh=high;
            L->r[0]=L->r[tmplow];
            pivotkey=L->r[tmplow].key;
            while(tmplow<tmphigh){
                while(tmplow<tmphigh && L->r[tmphigh].key>=pivotkey) --tmphigh;
                L->r[tmplow]=L->r[tmphigh];
                while(tmplow<tmphigh && L->r[tmplow].key<=pivotkey) ++tmplow;
                L->r[tmphigh]=L->r[tmplow];
            }
            L->r[tmplow]=L->r[0];
            // ---push & sort
            push(S, high);
            push(S, tmplow+1);
            high=tmplow-1;
        }

        int num=high-low;
        while(num>1){
            if(L->r[low].key > L->r[low+1].key){
                RcdType tmp=L->r[low];
                L->r[low]=L->r[low+1];
                L->r[low+1]=tmp;
            }
            num--;
        }

        stacknotempty = pop(S, &low);
        stacknotempty = pop(S, &high);
    }
    return L;
}

SqList *GetList(SqList *L){
    char c='\0';
    int i=1;
    while(c!='\n'){
        scanf("%d", &L->r[i++].key);
        L->length++;
        c=getchar();
    }
    return L;
}

void InitList(SqList *L){
    L->length=0;
}

int InitStack(SqStack *s){
    s->base=malloc(sizeof(int) * INITSIZE);
    if(!s->base) return 0;
    s->top=0;
    s->stacksize=INITSIZE;
    return 1;
}

int push(SqStack *s, int e){
    if(s->top >= s->stacksize) {
		s->base=realloc(s->base, 
			(s->stacksize + INCREMENT)*sizeof(int));
		if(!s->base) return 0;
		s->stacksize+=INCREMENT;
	}
    s->base[s->top++]=e;
    return 1;
}

int pop(SqStack *s, int *e){
    if(!s->top) return 0;
    *e=s->base[--s->top];
    return 1;
}

void PrintList(SqList *L){
    int i;
    for(i=1;i<=L->length;i++){
        printf("%d", L->r[i].key);
        if(i+1<=L->length) printf(" ");
    }
}