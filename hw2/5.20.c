#include <stdio.h>
#include <stdlib.h>

int main(){
    int m,n;
    scanf("%d %d",&m,&n);
    getchar();
    int mat[m][n];
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            scanf("%d",&mat[i][j]);
            getchar();
        }
    }
    for(i=m-1;i>=0;i--){
        for(j=n-1;j>=0;j--){
            if(mat[i][j]){
                if(mat[i][j]!=1) printf("%d",mat[i][j]);
                if(i) printf("xE%d",i);
                if(j) printf("yE%d",j);
                if(i+j) printf("+");
                // && (i+j)!=(m+n)
            }
        }
    }
}