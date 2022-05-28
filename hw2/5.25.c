/*
时间复杂度分析：pv1, pv2, pv3是指向V1, V2, V3数组的指针，
需要将矩阵内所有元素过一遍，对于每一个元素，要决定矩阵B3对
应位置是0还是1，还要决定V3是否新增非零元素，因此算法的
时间复杂度为O(m*n)
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    int m,n;
    scanf("%d %d",&m, &n);
    getchar();
    int i,j;
    int A1[m][n], A2[m][n], B1[m][n], B2[m][n], B3[m][n];
    int V1[m*n], V2[m*n], V3[m*n];
    //函数实现？二维数组传参？
    //get V1
    char c;
    int sgn=1;
    i=0;
    while((c=getchar())!='\n'){
        V1[i]=0;
        do{
            if(c=='-'){
                sgn=-1;
                continue;
            }
            V1[i]+=(c-'0');
            V1[i]*=10;
        }while((c=getchar())!=' ' && c!='\n');
        V1[i]/=10;
        V1[i]*=sgn;
        sgn=1;
        i++;
        if(c=='\n') break;
    }

    //get B1
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            scanf("%d",&B1[i][j]);
            getchar();
        }
    }

    //get V2
    sgn=1;
    i=0;
    while((c=getchar())!='\n'){
        V2[i]=0;
        do{
            if(c=='-'){
                sgn=-1;
                continue;
            }
            V2[i]+=(c-'0');
            V2[i]*=10;
        }while((c=getchar())!=' ' && c!='\n');
        V2[i]/=10;
        V2[i]*=sgn;
        sgn=1;
        i++;
        if(c=='\n') break;
    }

    //get B2
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            scanf("%d",&B2[i][j]);
            getchar();
        }
    }

    int pv1=0, pv2=0, pv3=0;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            if(B1[i][j]==1 && B2[i][j]==1){
                V3[pv3++]=V1[pv1++]+V2[pv2++];
                if(!V3[pv3-1]){
                    pv3--;
                    B3[i][j]=0;
                }else B3[i][j]=1;
            }else if(B1[i][j]==1 && B2[i][j]==0){
                B3[i][j]=1;
                V3[pv3++]=V1[pv1++];
            }else if(B1[i][j]==0 && B2[i][j]==1){
                B3[i][j]=1;
                V3[pv3++]=V2[pv2++];
            }else if(B1[i][j]==0 && B2[i][j]==0){
                B3[i][j]=0;
            }
        }
    }

    //print
    for(i=0;i<pv3-1;i++){
        printf("%d ",V3[i]);
    }
    if(pv3) printf("%d",V3[pv3-1]);
    printf("\n");
    for(i=0;i<m;i++){
        for(j=0;j<n-1;j++){
            printf("%d ",B3[i][j]);
        }
        printf("%d\n",B3[i][n-1]);
    }
}