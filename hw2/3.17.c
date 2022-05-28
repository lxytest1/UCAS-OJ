#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 100
#define INCREMENT 10

typedef struct{
    int top;
    int stacksize;
    char *base;
}SqStack;

int InitStack(SqStack *s);
int judge(SqStack *s);
int push(SqStack *s, char e);
int pop(SqStack *s, char *e);

int main(){
    SqStack *s=malloc(sizeof(SqStack));
    InitStack(s);
    int j=1;
    j=judge(s);
    if(j==0) printf("0\n");
    else printf("1\n");
    return 0;
}

int judge(SqStack *s){
    char c;
    char *gettop=malloc(sizeof(char));
    int stackempty;
    while((c=getchar())!='&') push(s, c);
    while((c=getchar())!='@'){
        stackempty = pop(s, gettop);
        if(*gettop!=c || stackempty==0) return 0;
    }
    return 1;
}

int InitStack(SqStack *s){
    s->base=malloc(sizeof(char) * INITSIZE);
    if(!s->base) return 0;
    s->top=0;
    s->stacksize=INITSIZE;
    return 1;
}

int push(SqStack *s, char e){
    if(s->top >= s->stacksize) {
		s->base=realloc(s->base, 
			(s->stacksize + INCREMENT)*sizeof(char));
		if(!s->base) return 0;
		s->stacksize+=INCREMENT;
	}
    s->base[s->top++]=e;
    return 1;
}

int pop(SqStack *s, char *e){
    if(!s->top) return 0;
    *e=s->base[--s->top];
    return 1;
}