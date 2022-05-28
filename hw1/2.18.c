#include <stdio.h>

typedef struct LNode{
	int data;
	struct LNode *next;
}LNode, *LinkedList;

void InitList(LinkedList L);
LinkedList DeleteList(LinkedList L, int i);
void PrintList(LinkedList L);

int main(){
	LinkedList L=(LinkedList) malloc(sizeof(LNode));
	
	InitList(L);
	
	int del;
	scanf("%d",&del);
	
	L=DeleteList(L,del);
	PrintList(L);
	return 0;
}

void InitList(LinkedList L){
	int i;
	LinkedList q,p;
	scanf("%d",&(L->data));
	L->next=NULL;
	p=L;
	while(getchar()!='\n'){
		q=(LinkedList)malloc(sizeof(LNode));
		scanf("%d",&(q->data));
		q->next=p->next;
		p->next=q;
		p=q;
	}
}

LinkedList DeleteList(LinkedList L, int i){
	int j;
	LinkedList p,q;
	p=L;
	if(!i){
		L=p->next;
		free(p);
	}else{
		for(j=0;j<i-1;j++){
			p=p->next;
		}
		q=p->next;
		p->next=q->next;
		free(q);
	}
	return L;
}

void PrintList(LinkedList L){
	//´òÓ¡L
	if(!L){
		printf("NULL");
		return;
	}
	LinkedList q=L;
	while(q){
		printf("%d ",q->data);
		q=q->next;
	}
}
