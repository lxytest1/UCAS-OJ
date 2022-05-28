#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 101
#define LISTINCREMENT 10

typedef struct{
	int *elem;
	int length;
	int listsize;
} SqList;

void ListInsert(SqList *va,int x);
void PrintList(SqList *va);

int main(){
	//初始化 
	SqList *va=(SqList *)malloc(sizeof(SqList));
	va->elem=(int *)malloc(sizeof(int) * LIST_INIT_SIZE);
	va->length=0;
	va->listsize=LIST_INIT_SIZE;
	//获取输入 
	char ch;
	int i=0;
	do{
		scanf("%d",&(va->elem[i]));
		va->length++;
		i++;
	}while((ch=getchar())!='\n');
	int x;
	scanf("%d",&x);
	//插入元素x并打印 
	ListInsert(va,x);
	PrintList(va);	
}

void ListInsert(SqList *va,int x){
	
	int i;
//	printf("va->length=%d, va->elem[va->length-1]=%d\n",va->length,va->elem[va->length-1]);
	for(i=0;va->elem[i]<x && i<=va->length-1;i++){
//		printf("i=%d: va->elem[%d]=%d\n",i,i,va->elem[i]);
	}
//	printf("-------%d-------\n",i);
	int *p, *q;
	p=&(va->elem[i]);
	for(q=&(va->elem[va->length-1]);q>=p;q--){
		*(q+1)=*q;
	}
	*p=x;
	va->length++;
}

void PrintList(SqList *va){
	int i;
	for(i=0;i<va->length-1;i++){
		printf("%d ",va->elem[i]);
	}
	printf("%d",va->elem[i]);
}
