#include <stdio.h>

typedef struct LNode{
	int data;
	int freq;
	struct LNode *prior;
	struct LNode *next;
}LNode, *LinkedList;

void InitList(LinkedList L,int len);
void PrintList(LinkedList L);
void locate(LinkedList L,LinkedList order,int x);
void UpdateOrder(LinkedList order, int x);

int main(){
	//初始化 
	LinkedList L=(LinkedList)malloc(sizeof(LNode));
	int len;
	scanf("%d",&len);
	InitList(L,len);
	//用链表order记录结点访问的先后次序 
	LinkedList order=(LinkedList)malloc(sizeof(LNode));
	order->next=order;
	order->prior=order; 
	//输入被访问的元素 
	int x;
	do{
		scanf("%d",&x);
		UpdateOrder(order,x);
		locate(L,order,x);
	}while(getchar()!='\n');
	//打印链表
	PrintList(L); 
}

void InitList(LinkedList L,int len){
	L->freq=0;
	L->prior=L;
	L->next=L;
	int i;
	LinkedList p,tail=L;
	for(i=0;i<len;i++){
		p=(LinkedList)malloc(sizeof(LNode));
		scanf("%d",&p->data);
		p->freq=0;
		getchar();
		tail->next=p;
		L->prior=p;
		p->next=L;
		p->prior=tail;
		tail=p;
	}
}

void UpdateOrder(LinkedList order, int x){
	LinkedList p=order->next;
	while(p!=order){
		if(p->data==x) return;
		p=p->next;
	}
	LinkedList q=(LinkedList) malloc(sizeof(LNode));
	q->data=x;
	q->next=order;
	q->prior=order->prior;
	q->prior->next=q;
	q->next->prior=q;
}

void locate(LinkedList L,LinkedList order,int x){
	LinkedList p=L->next;
	while(p!=L){
		if(p->data==x){
			p->freq++;
			//调换结点顺序
			LinkedList q=L->next;
			//让q走到频率小于等于p的结点处（或头结点处，如果所有结点的频率都严格大于p的频率） 
			while(q->freq>p->freq && q!=L) q=q->next;
			//在同频率的结点中，依据order的访问次序确定q的位置 
			LinkedList o=order;
			while(o->data!=x) o=o->next;
			o=o->next;
			while(q->freq==p->freq){
				if(q->data==o->data) break;
				q=q->next;
			}

			//将p移动到q->prior位置
			p->prior->next=p->next;
			p->next->prior=p->prior;
			p->prior=q->prior;
			p->next=q;
			q->prior->next=p;
			q->prior=p;
		}
		p=p->next;
	}
}

void PrintList(LinkedList L){
	//打印L 
	LinkedList q=L->next;
	while(q->next!=L){
		printf("%d ",q->data);
		q=q->next;
	}
	printf("%d\n",q->data);
}
