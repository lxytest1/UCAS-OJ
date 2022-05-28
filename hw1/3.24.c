#include <stdio.h>

int g(int m,int n);

int main(){
	int m,n;
	scanf("%d,%d",&m,&n);
	printf("%d",g(m,n));
}

int g(int m,int n){
	if(m==0) return 0;
	else return g(m-1,2*n)+n;
}
