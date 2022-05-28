#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000

typedef enum{ATOM, LIST} ElemTag;
typedef struct GLNode{
    ElemTag tag;
    union {
        char atom;
        struct GLNode *hp;
    };
    struct GLNode *tp;
}Glist;
int CreateList(Glist *L, char s[]);
void myserver(char sub[], char hsub[]);
void PrintList(Glist *L);
Glist *DeleteList(Glist *L, char x);
int NumOfAtoms(Glist *L);

int CreateList(Glist *L, char s[]){
    if(!strcmp(s,"()")){
        L->tag=LIST;
        L->hp=NULL;
    } else {
        // L=malloc(sizeof(Glist));
        if(!L) return 0;
        if(strlen(s)==1){   // 创建单原子广义表
            L->tag=ATOM;
            L->atom=s[0];
            // L->tp=NULL;
        }else{              // 递归创建广义表
            L->tag=LIST;
            L->hp=malloc(sizeof(Glist));
            Glist *p=L->hp;
            char sub[MAX];
            strcpy(sub,"");
            if(s[0]=='(') {strncpy(sub, s+1, strlen(s)-2); sub[strlen(s)-2]='\0';} //脱括号
            else strcpy(sub,s);
            Glist *q;
            do{
                char hsub[MAX];
                myserver(sub, hsub);
                // p->hp=malloc(sizeof(Glist));
                CreateList(p,hsub);     // 递归
                q=p;
                if(strcmp(sub,"")){
                    p=malloc(sizeof(Glist));
                    q->tp=p;
                }
            }while(strcmp(sub,""));
            q->tp=NULL;
        }
    }
    L->tp=NULL;
    return 1;
}

void myserver(char sub[], char hsub[]){
    int n=strlen(sub);
    int i=0,k=0;
    char c;
    do{
        c=sub[i++];
        if(c=='(') ++k;
        else if(c==')') --k;
    }while(i<n && (c!=',' || k!=0));
    if(i<n){
        strncpy(hsub, sub, i-1);
        strncpy(sub, sub+i, n-i);
        sub[n-i]='\0';
    }else{
        strcpy(hsub,sub);
        strcpy(sub,"");
    }
}

void PrintList(Glist *L){
    if(L==NULL) return;
    if(L->tag==LIST && L->hp!=NULL){
        printf("(");
        PrintList(L->hp);
        printf(")");
        if(L->tp!=NULL && L->tp->hp!=NULL){
            printf(",");
            PrintList(L->tp);
        }
    }else if(L->tag==ATOM){
        printf("%c", L->atom);
        if(L->tp!=NULL && L->tp->hp!=NULL){
            printf(",");
            PrintList(L->tp);
        }
    }
}

Glist *DeleteList(Glist *L, char x){
    if(L){
        Glist *head;
        head=L;
        while(head->tp!=NULL){
            if(head->tp->tag==ATOM && head->tp->atom==x){
                Glist *q=head->tp;
                head->tp=q->tp;
                free(q);
            }else if(head->tp->tag==LIST){
                head->tp=DeleteList(head->tp, x);
                head=head->tp;
            }else{
                head=head->tp;
            }
        }
        if(L->tag==ATOM && L->atom==x) L=L->tp;
        else if(L->tag==LIST) L->hp=DeleteList(L->hp, x);
    }
    return L;
}

int NumOfAtoms(Glist *L){
    int num=0;
    Glist *head=L;
    while(head!=NULL){
        if(head->tag==ATOM){
            num++;
            head=head->tp;
        }else{
            num+=NumOfAtoms(head->hp);
            head=head->tp;
        }
    }
    return num;
}

int main(){
    Glist *L=malloc(sizeof(Glist));
    // CreateList(L,"(a,(b,(c,b)),d)");
    char str[MAX];
    char x;
    scanf("%s %c",&str,&x);
    CreateList(L,str);
    DeleteList(L,x);
    if(!NumOfAtoms(L)) printf("-1\n");
    else PrintList(L);
    system("pause");
}