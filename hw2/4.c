#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct cnode{
    char data;
    struct cnode *next;
}String, cnode;

void initial(String *s);
void catstr(String *s, char c);
void delstr(String *s);
void printstr(String *s);

int main(){
    char c;
    int mode=0; // 0: code 2: string("") 3: char('') 4: 注释中(/*)
    int esc=0; // escape character mark
    String *out=malloc(sizeof(String));
    initial(out);
    while((c=getchar())!=EOF){
        switch(mode){
        case 0:
            switch(c){
            case '\"':
                mode=2; catstr(out, c); continue;
            case '\'':
                mode=3; catstr(out, c); continue;
            case '/':
                catstr(out, c); 
                c=getchar();
                if(c=='*') {
                    mode=4;
                    delstr(out); 
                    continue;
                }else if(c==EOF){
                    break;
                }else{
                    catstr(out, c); 
                    continue;
                }
            default:
                catstr(out, c); 
                continue;
            }

        case 2:
            catstr(out, c);
            switch(c){
            case '\\':
                c=getchar();
                if(c==EOF) break;
                catstr(out, c);
                continue;
            case '\"':
                mode=0;
                // catstr(out, c);
                continue;
            default:
                // catstr(out, c);
                continue;
            }

        case 3:
            catstr(out, c);
            switch(c){
            case '\\':
                c=getchar();
                if(c==EOF) break;
                catstr(out, c);
                continue;
            case '\'':
                mode=0;
                // catstr(out, c);
                continue;
            default:
                // catstr(out, c);
                continue;
            }

        case 4:
            switch(c){
            case '*':
                if((c=getchar())=='/') mode=0;
                continue;
            default:
                continue;
            }
        }
    }
    printstr(out);
}

void initial(String *s){
    s->next=s;
}

void catstr(String *s, char c){
    cnode *p=malloc(sizeof(cnode));
    p->data=c;
    String *strend=s;
    while(strend->next!=s) strend=strend->next;
    p->next=s;
    strend->next=p;
}

void delstr(String *s){
    String *strend=s;
    while(strend->next->next!=s) strend=strend->next;
    strend->next=s;
}

void printstr(String *s){
    String *p=malloc(sizeof(String));
    p=s->next;
    while(p->next!=s){
        printf("%c",p->data);
        p=p->next;
    }
    free(p);
}