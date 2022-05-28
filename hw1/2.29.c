#include <stdio.h>

typedef struct LNode{
	char data;
	struct LNode *next;
}LNode, *LinkedList;

void InitAndReverseList(LinkedList L);
void PrintList(LinkedList L);
int ListHasValue(LinkedList L, char v);

int main(){
	LinkedList La,Lb,Lc;
	La=(LinkedList)malloc(sizeof(LNode));
	Lb=(LinkedList)malloc(sizeof(LNode));
	Lc=(LinkedList)malloc(sizeof(LNode));
	InitList(La);
	InitList(Lb);
	InitList(Lc);
	
	LinkedList p=Lb;
	while(p){
		if(ListHasValue(Lc,p->data)) {
//			printf("List Lc has value %c\n",p->data);
			ListDeleteValue(La,p->data);
		}
		p=p->next;
	}
	
	PrintList(La);
}

int InitList(LinkedList L){
	//初始化链表，填入值
	int i;
	LinkedList q,p;
	L->next=NULL;
	p=L;
	do{
		q=(LinkedList)malloc(sizeof(LNode));
		scanf("%c",&(q->data));
		q->next=p->next;
		p->next=q;
		p=q;
	}while(getchar()!='\n');
}

int ListHasValue(LinkedList L, char v){
	LinkedList p=L->next;
	while(p && p->data<=v){
		if(p->data==v) return 1;
		p=p->next;
	}
	return 0;
}

void ListDeleteValue(LinkedList L,char v){
	LinkedList p=L,q;
	while(p){
		q=p->next;
		if(!q) return;
		if(q->data==v){
			p->next=q->next;
			free(q);
			continue;
		}
		p=p->next;
	}
}

void PrintList(LinkedList L){
	//打印L 
	LinkedList q=L->next;
	while(q->next){
		printf("%c,",q->data);
		q=q->next;
	}
	printf("%c",q->data);
}
