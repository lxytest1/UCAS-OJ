#include <stdio.h>

int main(){
	int k,m;
	scanf("%d %d",&k,&m);
	long a[m];
	int i;
	//ǰk-1����Ϊ0 
	for(i=0;i<k-1;i++){
		a[i]=0;
	}
	//��k-1����Ϊ1 
	a[k-1]=1;
	//֮��ÿ����Ϊ��ǰ��k����֮�� 
	for(i=k;i<=m;i++){
		int j;
		a[i]=0;
		for(j=i-k;j<i;j++){
			a[i]+=a[j];
		}
	}
	printf("%ld",a[m]);
}
