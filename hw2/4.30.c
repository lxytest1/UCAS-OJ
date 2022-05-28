#include <stdio.h>
#include <string.h>

#define MAX 100
typedef char String[MAX];

int main(){
    // char s[MAX], ss[MAX][MAX], maxs[MAX];
    String s, ss[MAX], maxs;
    int m=-1;
    scanf("%s",s);
    int i, j, k;
    int len=strlen(s);
    if(len==1){
        printf("-1\n");
        return 0;
    }

    for(j=1;j<len;j++){// length of slice
        for(i=0;i+j<=len;i++){// start position
            strncpy(ss[i],s+i,j);
            for(k=0;k<i;k++){
                if(!strcmp(ss[k],ss[i])){
                    strcpy(maxs, ss[k]);
                    m=k;
                    break;
                }
            }
        }
    }

    if(m==-1) printf("%d\n",m);
    else printf("%s %d\n",maxs, m);
}