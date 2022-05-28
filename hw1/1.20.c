#include <stdio.h>
#include <math.h>
int main(){
	int x0, n;
	scanf("%d %d",&x0,&n);
	int i;
	int a[n];
	for(i=0;i<=n;i++){
		scanf("%d",&a[i]);
		getchar();
	}
	int sum=0;
	for(i=0;i<=n;i++){
		sum+=a[i]*pow(x0,i);
	}
	printf("%d",sum);
}
