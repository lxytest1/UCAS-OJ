#include <stdio.h>

typedef struct LNode{
	int elem;
	struct LNode *next; 
}LNode, *LinkedList;

LinkedList ConcatList(LinkedList La,LinkedList Lb); 
void PrintList(LinkedList Lc);
void InitList(LinkedList L,int len);

int main(){
	LinkedList La,Lb;
	La=(LinkedList)malloc(sizeof(LNode));
	Lb=(LinkedList)malloc(sizeof(LNode));
	
	int len_a,len_b;
	scanf("%d %d",&len_a,&len_b);
	
	InitList(La,len_a);
	InitList(Lb,len_b);
	
	LinkedList Lc=(len_a>len_b) ? ConcatList(Lb,La) : ConcatList(La,Lb);
	PrintList(Lc);
}

void InitList(LinkedList L,int len){
	//初始化链表，填入值
	int i;
	LinkedList q,p;
	L->next=NULL;
	p=L;
	for(i=0;i<len;i++){
		q=(LinkedList)malloc(sizeof(LNode));
		scanf("%d",&(q->elem));
		getchar();
		q->next=p->next;
		p->next=q;
		p=q;
	}
}

LinkedList ConcatList(LinkedList La,LinkedList Lb){
	//把Lb接到La后面
	LinkedList q,Lc;
	q=Lc=La;
	while(q->next){
		q=q->next;
	}
	LinkedList p=(LinkedList)malloc(sizeof(LinkedList));
	p=Lb;
	q->next=p->next;
	return Lc;
}

void PrintList(LinkedList Lc){
	//打印Lc 
	LinkedList q=Lc->next;
	while(q){
		printf("%d ",q->elem);
		q=q->next;
	}
}
