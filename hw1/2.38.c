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
	//��ʼ�� 
	LinkedList L=(LinkedList)malloc(sizeof(LNode));
	int len;
	scanf("%d",&len);
	InitList(L,len);
	//������order��¼�����ʵ��Ⱥ���� 
	LinkedList order=(LinkedList)malloc(sizeof(LNode));
	order->next=order;
	order->prior=order; 
	//���뱻���ʵ�Ԫ�� 
	int x;
	do{
		scanf("%d",&x);
		UpdateOrder(order,x);
		locate(L,order,x);
	}while(getchar()!='\n');
	//��ӡ����
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
			//�������˳��
			LinkedList q=L->next;
			//��q�ߵ�Ƶ��С�ڵ���p�Ľ�㴦����ͷ��㴦��������н���Ƶ�ʶ��ϸ����p��Ƶ�ʣ� 
			while(q->freq>p->freq && q!=L) q=q->next;
			//��ͬƵ�ʵĽ���У�����order�ķ��ʴ���ȷ��q��λ�� 
			LinkedList o=order;
			while(o->data!=x) o=o->next;
			o=o->next;
			while(q->freq==p->freq){
				if(q->data==o->data) break;
				q=q->next;
			}

			//��p�ƶ���q->priorλ��
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
	//��ӡL 
	LinkedList q=L->next;
	while(q->next!=L){
		printf("%d ",q->data);
		q=q->next;
	}
	printf("%d\n",q->data);
}
