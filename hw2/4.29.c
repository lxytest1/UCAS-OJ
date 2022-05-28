#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char chdata;
    struct node *succ;
    struct node *next;
}String;

void getstr(String *s);
// void getmode(String *s);
void initStr(String *s);
void printstr(String *s);
void getnext_main(String *s);
void getnext_mode(String *s);

int main(){
    int lmain,lmode;
    scanf("%d %d",&lmain, &lmode);
    getchar();
    String *mainstr=malloc(sizeof(String));
    String *modestr=malloc(sizeof(String));
    initStr(mainstr);
    initStr(modestr);
    getstr(mainstr);
    getstr(modestr);
    getnext_main(mainstr);
    getnext_mode(modestr);
    String *i, *j;
    int counter=0;
    i=mainstr->succ;
    j=modestr->succ;
    while(i!=mainstr && j!=modestr){
        if(j->next==modestr || i->chdata == j->chdata){
            if(i->chdata == j->chdata) j=j->succ;
            i=i->succ;
            counter++;
        }else j=j->next;
    }
    if(j==modestr) printf("%d\n",counter-lmode);
    else printf("-1\n");
}

void initStr(String *s){
    s->next=s;
    s->succ=s;
}

void getstr(String *s){
    char c;
    String *p;
    String *str=s;
    while((c=getchar())!='\n'){
        p=malloc(sizeof(String));
        p->chdata=c;
        str->succ=p;
        // p->next=str;
        p->succ=s;
        // s->next=p;
        str=p;
    }
}

void getnext_main(String *s){
    String *p1, *p2;
    p1=s;
    p2=s->succ;
    while(p1!=s){
        p2->next=p1;
        p1=p1->succ;
        p2=p2->succ;
    }
}

void getnext_mode(String *s){
    String *head, *tail, *t;
    head=s->succ;
    head->next=s;
    t=head->succ;
    t->next=head;
    t=t->succ;
    tail=t;
    while(t!=s){
        while(1){
            t->next=head;
            if(tail->chdata!=head->chdata || head->succ==t) break;
            head=head->succ;
            String *front=s;
            while(front->succ!=tail) front=front->succ;
            tail=front;
        }
        t=t->succ;
    }
}

void printstr(String *s){
    String *str=s->succ;
    while(str!=s){
        printf("%c",str->chdata);
        str=str->succ;
    }
    printf("\n");
}