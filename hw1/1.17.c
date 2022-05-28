#include <stdio.h>

int main(){
	int k,m;
	scanf("%d %d",&k,&m);
	long a[m];
	int i;
	//前k-1个数为0 
	for(i=0;i<k-1;i++){
		a[i]=0;
	}
	//第k-1个数为1 
	a[k-1]=1;
	//之后每个数为它前面k个数之和 
	for(i=k;i<=m;i++){
		int j;
		a[i]=0;
		for(j=i-k;j<i;j++){
			a[i]+=a[j];
		}
	}
	printf("%ld",a[m]);
}
