#include <stdio.h>
#include <math.h>
#include <limits.h> 
#define ERROR -1
int fact(int n);

int main(){
	int n,arrsize;
	scanf("%d %d",&n,&arrsize);
	if(arrsize<n){
		printf("%d",ERROR);
		return 0;
	}else{
		int a[arrsize];
		int i;
		for(i=0;i<n;i++){
			a[i]=pow(2,i)*fact(i);
			if(a[i]<=0 || a[i]> INT_MAX){
				printf("%d",ERROR);
				return 0;	
			}
		}
		for(i=0;i<n-1;i++){
			printf("%d ",a[i]);
		}
		printf("%d",a[n-1]);
		return 0;
	}
}
//
//long long power(int a,int k){
//	int i;
//	long long prod=1;
//	for(i=0;i<k;i++){
//		prod*=a;
//	}
//	return (prod>0)?prod:0;
//}

int fact(int n){
	int prod=1;
	if(n==0) return 1;
	else{
		while(n>=1){
			prod*=n;
			n--;
		}
	}
	return (prod>0)?prod:0;
}
