#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITSIZE 100
#define INCREMENT 10
#define MAXLEN 100

typedef struct{
    int top;
    int stacksize;
    char *base;
}SqStack;

int InitStack(SqStack *s);
int judge(SqStack *s);
int push(SqStack *s, char e);
int pop(SqStack *s, char *e);
void str2stack(char str[], SqStack *seqs, SqStack *revs);
SqStack *reverse(SqStack *s);
int check(SqStack *s, SqStack *t);

int main(){
    char str[MAXLEN];
    SqStack *seqs,*revs;
    char output[MAXLEN];
    scanf("%s",str);
    seqs=malloc(sizeof(SqStack));
    revs=malloc(sizeof(SqStack));
    InitStack(seqs);
    InitStack(revs);
    str2stack(str, seqs, revs);
    revs=reverse(revs);
    if(check(seqs, revs)) printf("1\n");
    else printf("0\n");
    return 0;
}

void str2stack(char str[], SqStack *seqs, SqStack *revs){
    int len=strlen(str);
    str[len]='\0';
    int i;
    for(i=0;i<len-1;i++){
        push(seqs, str[i]);
        push(revs, str[i]);
    }
}

int check(SqStack *s, SqStack *t){
    char stop, ttop;
    while(s->top && t->top){
        pop(s, &stop);
        pop(t, &ttop);
        if(stop!=ttop) return 0;
    }
    // if(s->top || t->top) return 0;
    return 1;
}

SqStack *reverse(SqStack *s){
    SqStack *t=malloc(sizeof(SqStack));
    InitStack(t);
    char c;
    do{
        pop(s, &c);
        push(t, c);
    }while(s->top);
    return t;
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