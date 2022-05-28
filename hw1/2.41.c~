#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 10

typedef struct PolyTerm{
	int c;
	int e;
	char sgn;
}PolyTerm;

typedef struct PolyNode{
  PolyTerm data;
  struct PolyNode *next;
} PolyNode, *PolyLink;

typedef PolyLink LinkedPoly;

void InitPoly(LinkedPoly P);
void PrintPoly(LinkedPoly P);
void AddTerm(LinkedPoly P, int sign, char term[]);

int main(){
	LinkedPoly P=(LinkedPoly)malloc(sizeof(PolyNode));
	InitPoly(P);
	Derivative(P);
	DeleteZeros(P);
	PrintPoly(P);
}

void InitPoly(LinkedPoly P){
	P->next=P;
	
	char term[MAXLEN];
	int sign=1;
	do{
		scanf("%s",term);
		if(!strcmp(term, "-")) {
			sign=-1;
			scanf("%s",term);
		}else if(!strcmp(term, "+")) {
			sign=1;
			scanf("%s",term);
		}
		AddTerm(P,sign,term);
	}while(getchar()!='\n');
}

void AddTerm(LinkedPoly P, int sign, char term[]){
	int i=0,e,c;
	char coef[MAXLEN],expo[MAXLEN];
	
	if(term[i]=='x'){
		strcpy(coef,"1");
	}else{
		for(;i<strlen(term) && term[i]!='x';i++){
			coef[i]=term[i];
		}
		coef[i]='\0';
	}
	c=atoi(coef) * sign;
	
	int len_coef = c*sign==1 ? 0 : (strlen(coef));
	if(strlen(term)==len_coef){
		strcpy(expo,"0");
	}else if(strlen(term)-len_coef==1){
		strcpy(expo,"1");
	}else{
		for(i=i+2;i<strlen(term);i++){
			expo[i - len_coef - 2] = term[i];
		}
	}
	e=atoi(expo);
	
	if(!strcmp(term, "1")){
		c=1;
		e=0;
	}
//	printf("1-->%d %d\n",c,e);
	//添加结点 
	LinkedPoly q=P;
	while(q->next->data.e>=e){
		//已有相同幂次的结点，与现有结点合并 
//		printf("%d\n",q->data.e);
		if(q->next==q) break;  //空表直接退出 
		if(q->next->data.e==e){
			q->next->data.c += c;
			return;
		}
		q=q->next;
	}
	//无相同幂次的结点，新增结点并降幂排列 
	LinkedPoly r=(LinkedPoly)malloc(sizeof(PolyNode));
	r->data.c=c;		
	r->data.e=e;
	r->next=q->next;
	q->next=r;
//	printf("2-->%d %d\n",r->data.c,r->data.e);
}

void Derivative(LinkedPoly P){
	LinkedPoly q=P->next;
	int c,e;
	while(q!=P){
		c=q->data.c;
		e=q->data.e;
		if(e==0) q->data.c=0;
		else{
			q->data.c=c*e;
			q->data.e=e-1;
		}
		q=q->next;
	}
}

void DeleteZeros(LinkedPoly P){
	LinkedPoly q=P->next,r=P;
	while(q!=P){
		if(q->data.c==0){
			r->next=q->next;
			q=r->next;
			continue;
		}
		q=q->next;
		r=r->next;
	}
}

void PrintPoly(LinkedPoly P){
	if(P->next==P) {		//空表直接输出0 
		printf("0");
		return; 
	}
	
	LinkedPoly q=P->next;
	char sign=(q->data.c<0) ? '-' : '+';
	if(sign=='-'){
		printf("- ");
	}
	PrintUnsignedTerm(q->data.c,q->data.e);
	q=q->next;
	while(q!=P){
		sign=(q->data.c<0) ? '-' : '+';
		printf("%c ",sign);
		PrintUnsignedTerm(q->data.c,q->data.e);
		q=q->next;
	}
}

void PrintUnsignedTerm(int c,int e){
	c=abs(c);
	if(c==0) return;
	if(c!=1) printf("%d",c);
	else if(c==1 && e==0) printf("1");
	if(e==1){
		printf("x ");
	}else if(e){
		printf("x^%d ",e);
	}

}
