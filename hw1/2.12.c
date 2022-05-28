#include <stdio.h>

#define LIST_INIT_SIZE 100

typedef struct{
	char *elem;
	int length;
	int listsize;
}SqList;

int main(){
	//初始化 
	SqList *va = (SqList *)malloc(sizeof(SqList));
	va->elem=(char *)malloc(sizeof(char)*LIST_INIT_SIZE);
	va->length=0;
	va->listsize=100;
	
	SqList *vb = (SqList *)malloc(sizeof(SqList));
	vb->elem=(char *)malloc(sizeof(char)*LIST_INIT_SIZE);
	vb->length=0;
	vb->listsize=100;
	//填入结点数值 
	char ch;
	int i=0;
	do{
		scanf("%c",&va->elem[i]);
		i++;
	}while((ch=getchar())!='\n');
	
	i=0;
	do{
		scanf("%c",&vb->elem[i]);
		i++;
	}while((ch=getchar())!='\n');
	
	int comp=compare(va,vb);
	printf("%d",comp);
}

int compare(SqList *va,SqList *vb){
	char *p,*q;
	p=&(va->elem[0]);
	q=&(vb->elem[0]);
	int i;
	for(i=0;;i++){
		if(!*p || !*q || *p!=*q) break;
		p++;
		q++;
	}
	if(!*p && !*q) return 0;
	else if(!*p && *q) return 1;
	else if(*p<*q) return 1;
	else return 2;
}
