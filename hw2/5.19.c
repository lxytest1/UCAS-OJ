#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int main(){
    int m,n;
    scanf("%d %d",&m, &n);
    int matrix[m][n];
    int lmin[m];
    int cmax[n];
    int i,j,k;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            scanf("%d",&matrix[i][j]);
            getchar();
            if(i==0) cmax[j]=matrix[i][j];
            else if(matrix[i][j]>cmax[j]) cmax[j]=matrix[i][j];
            if(j==0) lmin[i]=matrix[i][j];
            else if(matrix[i][j]<lmin[i]) lmin[i]=matrix[i][j];
        }
    }

    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            if(matrix[i][j] != lmin[i] || matrix[i][j] != cmax[j]) continue;
            printf("%d ",matrix[i][j]);
        }
    }
}