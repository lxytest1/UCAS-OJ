#include <stdio.h>

void swap(int *a,int *b);

int main(){
	int x,y,z;
	scanf(" %d %d %d",&x, &y, &z);
	if(y<z){
		swap(&y,&z);
	}
	if(x<y){
		swap(&x,&y);
	}
	if(y<z){
		swap(&y,&z);
	}
	printf("%d %d %d",x,y,z);
}

void swap(int *a,int *b){
	int t;
	t=*a;
	*a=*b;
	*b=t;
}
