#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 100
#define INCREMENT 10
#define OPSETSIZE 7

typedef struct{
    int top;
    int stacksize;
    char *base;
}SqStack;

int initStack(SqStack *s);
int push(SqStack *s, char e);
int pop(SqStack *s, char *e);
int judge(SqStack *s);
int isOperator(char test);
char precede(char Aop, char Bop);

char OPSET[OPSETSIZE]={'+', '-', '*', '/', '(', ')', '\n'};
unsigned char Prior[OPSETSIZE][OPSETSIZE]={
    '<', '<', '<', '<', '>', '<', '>',
    '<', '<', '<', '<', '>', '<', '>',
    '>', '>', '<', '<', '>', '<', '>',
    '>', '>', '<', '<', '>', '<', '>',
    '>', '>', '>', '>', '>', ' ', ' ',
    '<', '<', '<', '<', '=', '<', '>', 
    '<', '<', '<', '<', '<', ' ', '='
};

int main(){
    SqStack *op;
    op=malloc(sizeof(SqStack));
    initStack(op);
    push(op, '\n');
    char c, opord, gettop;
    while(c=getchar()){
        if(!isOperator(c)){
            printf("%c",c);
            continue;
        }
        opord = precede(c, op->base[op->top-1]);
        switch (opord)
        {
        case '>':
            push(op, c);
            break;
        case '<':
            // pop(op, &gettop);
            // printf("%c",c);
            // // if(gettop != '(' && gettop != ')' ) 
            //     printf("%c",gettop);
            // break;
            do{
                pop(op, &gettop);
                if(gettop!='(' && gettop!='\n') printf("%c", gettop);
            }while(precede(c, op->base[op->top-1])=='<');
            if(c!=')') push(op, c);
            else pop(op, &gettop);
            break;
        case '=':
            // pop(op, &gettop);
            // if(gettop == '(') continue;
            // return 0;
            pop(op, &gettop);
            break;
        default:
            printf("Syntax error!\n");
            break;
        }
        if(c=='\n') return 0;
    }
    return 0;
}

int isOperator(char test){
    int i;
    for(i=0;i<OPSETSIZE;i++){
        if(test == OPSET[i]) return 1;
    }
    return 0;
}

char precede(char Aop, char Bop){
    int i, j;
    for(i=0;i<OPSETSIZE;i++){
        for(j=0;j<OPSETSIZE;j++){
            if(OPSET[i]==Aop && OPSET[j]==Bop) 
                return Prior[i][j];
        }
    }
    return ' ';
}

int initStack(SqStack *s){
    s->base = malloc(sizeof(char) * INITSIZE);
    if(!s->base) return 0;
    s->top = 0;
    s->stacksize = INITSIZE;
    return 1;
}

int push(SqStack *s, char e){
    if(s->top>=s->stacksize){
        s->base = realloc(s->base, (s->stacksize+INCREMENT)*sizeof(char));
        if(!s->base) return 0;
        s->stacksize += INCREMENT;
    }
    s->base[s->top++] = e;
    return 1;
}

int pop(SqStack *s, char *e){
    if(!s->top) return 0;
    *e = s->base[--s->top];
    return 1;
}

