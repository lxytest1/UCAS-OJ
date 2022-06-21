#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXKEYLEN 27
#define MAXFIND 100

typedef struct {
    char ch[MAXKEYLEN];
    int num;
} KeysType;

typedef struct TrieNode{
    int kind; // 0: branch 1: leaf
    union{
        struct {
            KeysType K;
        } lf;
        struct {
            struct TrieNode *ptr[MAXKEYLEN];
            int num;
        } bh;
    } node;
} TrieNode, TrieTree;

TrieTree *init(TrieTree *T);
TrieTree *insert(TrieTree *T, char word[]);
TrieTree *delete(TrieTree *T, char word[]);
int finddata(TrieTree *T, char word[]);
TrieTree *findnode(TrieTree *T, char word[], int num);
int AllNull(TrieTree *ptr[]);

int main(){
    TrieTree *T=(TrieTree *)malloc(sizeof(TrieTree));
    T=init(T);
    int type;
    char word[MAXKEYLEN]="";
    int result[MAXFIND];
    int find=0;
    while(scanf("%d %s", &type, word)!=EOF){
        getchar();
        switch(type){
            case 1:
                T = insert(T, word);
                break;
            case 2:
                T = delete(T, word);
                break;
            case 3:
                result[find++] = finddata(T, word);
                break;
            default: break;
        }
        int i;

    }
        // for(i=0; i<find; i++) 
        //     printf("%s\n", (result[i] == 1) ? "True" : "False");
        // strcpy(word, "");
    int i;
    for(i=0; i<find; i++){
        printf("%s\n", (result[i] == 1) ? "True" : "False");
    }
}

TrieTree *init(TrieTree *T){
    int j;
    for(j=0;j<MAXKEYLEN;j++){
        T->node.bh.ptr[j]=NULL;
    }
    return T;
}

TrieTree *insert(TrieTree *T, char word[]){
    int i=0;
    TrieTree *p=T;
    TrieTree *q;
    KeysType last;
    int uselast=0;
    while(word[i]!='\0'){
        int j=word[i]-'a'+1;
        if(uselast==1){
            p->node.bh.ptr[0]=(TrieTree *)malloc(sizeof(TrieTree));
            TrieTree *new=p->node.bh.ptr[0];
            new->kind=1;
            new->node.lf.K.num=last.num;
            strcpy(new->node.lf.K.ch, last.ch);
            uselast=0;
        }
        if(p->kind==1){
            last=p->node.lf.K;
            p->kind=0;
            uselast=1;
            p=init(p);
        }
        if(p->node.bh.ptr[j]==NULL){
            q=(TrieTree *)malloc(sizeof(TrieTree));
            q=init(q);
            p->node.bh.ptr[j]=q;
            p->kind=0;
        }else{
            q=p->node.bh.ptr[j];
            p->kind=0;
        }
        p=q;
        i++;
    }
    // if(p->node.bh.ptr[word[i-1] - 'a' + 1]==NULL){
    if(AllNull(p->node.bh.ptr)){
        p->node.lf.K.num=strlen(word);
        p->kind=1;
        strcpy(p->node.lf.K.ch, word);
    }else{
        p->node.bh.ptr[0]=(TrieTree *)malloc(sizeof(TrieTree));
        p=p->node.bh.ptr[0];
        p->node.lf.K.num=strlen(word);
        p->kind=1;
        strcpy(p->node.lf.K.ch, word);
    }
    return T;
}

TrieTree *delete(TrieTree *T, char word[]){
    int i=strlen(word)-1;
    TrieTree *p;
    TrieTree *q;
    while(i>=0){
        q=findnode(T, word, i);
        // q->node.bh.ptr[word[i] - 'a' + 1] = NULL;
        p=q->node.bh.ptr[word[i] - 'a' + 1];
        if(p && p->kind==0) p->node.bh.ptr[0] = NULL;
        else q->node.bh.ptr[word[i] - 'a' + 1] = NULL;
        if(!AllNull(q->node.bh.ptr)) return T;
        i--;
    }
}

int finddata(TrieTree *T, char word[]){
    if(!T){
        return 0;
    }else if(T->kind==1){
        if(!strcmp(T->node.lf.K.ch, word)) return 1;
        else return 0;
    }else{
        int res=0, i;
        for(i=0; i<MAXKEYLEN; i++){
            res |= finddata(T->node.bh.ptr[i], word);
        }
        return res;
    }
}

int AllNull(TrieTree *ptr[]){
    int i;
    for(i=0; i<MAXKEYLEN; i++){
        if(ptr[i] != NULL) return 0;
    }
    return 1;
}

TrieTree *findnode(TrieTree *T, char word[], int num){
    int i;
    TrieTree *p=T;
    for(i=0;i<num;i++){
        p=p->node.bh.ptr[word[i] - 'a' + 1];
    }
    return p;
}