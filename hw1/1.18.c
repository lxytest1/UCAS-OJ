#include <stdio.h>

int main(){
	int m[5],f[5];
	int i=0;
	while(i<5){
		m[i]=0;
		f[i]=0;
		i++;
	}
	char event, gender, univ;
	int mark;
	while(scanf("%c %c %c %d",&event, &gender, &univ, &mark)!=EOF){
		getchar();
		if(gender == 'M') m[univ - 65]+=mark;
		else f[univ - 65]+=mark;
	}
	i=0;
	while(i<5){
		if(m[i]) printf("%c M %d\n",i+65, m[i]);
		if(f[i]) printf("%c F %d\n",i+65, f[i]);
		if(m[i]+f[i]) printf("%c %d\n",i+65, m[i]+f[i]);
		i++;
	}
	return 0;
}
