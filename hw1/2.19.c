#include <stdio.h>

typedef struct LNode{
	int data;
	struct LNode *next;
}LNode, *LinkedList;

void InitList(LinkedList L);
void PrintList(LinkedList L);
LinkedList ListDeleteValue(LinkedList L,int v);

int main(){
	LinkedList L;
	L=(LinkedList) malloc(sizeof(LNode));
	InitList(L);
	
	int mink,maxk;
	scanf("%d %d",&mink,&maxk);
	
	LinkedList p=L->next;
	while(p){
		int v=p->data;
		if(v>mink && v<maxk){
			L=ListDeleteValue(L,v);
			p=L->next;
			continue;
		}
		p=p->next;
	}
	PrintList(L);
}

void InitList(LinkedList L){
	//初始化链表，填入值
	int i;
	LinkedList q,p;
	L->next=NULL;
	p=L;
	do{
		q=(LinkedList)malloc(sizeof(LNode));
		scanf("%d",&(q->data));
		q->next=p->next;
		p->next=q;
		p=q;
	}while(getchar()!='\n');
}

LinkedList ListDeleteValue(LinkedList L,int v){
	LinkedList p=L,q;
	while(p){
		q=p->next;
		if(!q){
			return L;
		} 
		if(q->data==v){
			p->next=q->next;
			free(q);
			continue;
		}
		p=p->next;
	}
	return L;
	
}

void PrintList(LinkedList L){
	//打印L 
	LinkedList q=L->next;
	while(q->next){
		printf("%d ",q->data);
		q=q->next;
	}
	printf("%d\n",q->data);
}
