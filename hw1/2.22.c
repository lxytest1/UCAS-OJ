#include <stdio.h>

typedef struct LNode{
	char data;
	struct LNode *next;
}LNode, *LinkedList;

void InitAndReverseList(LinkedList L);
void PrintList(LinkedList L);

int main(){
	LinkedList L=(LinkedList) malloc(sizeof(LNode));
	InitAndReverseList(L);
	PrintList(L);
}

void InitAndReverseList(LinkedList L){
	int i;
	LinkedList q;
	L->next=NULL;
	do{
		q=(LinkedList)malloc(sizeof(LNode));
		scanf("%c",&(q->data));
		q->next=L->next;
		L->next=q;
	}while(getchar()!='\n');
}

void PrintList(LinkedList L){
	//´òÓ¡Lc 
	LinkedList q=L->next;
	while(q->next){
		printf("%c,",q->data);
		q=q->next;
	}
	printf("%c",q->data);
}
