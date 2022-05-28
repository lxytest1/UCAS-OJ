#include <stdio.h>
#include <stdlib.h>

typedef struct OLNode{
    int i,j;
    int e;
    struct OLNode *right, *down;
} OLNode, *Olink;

typedef struct{
    Olink *rhead, *chead;
    int mu, nu, tu;
} CrossList;

CrossList addcl(CrossList cl1, CrossList cl2);
void printlist(CrossList cl);

//二维数组传参复杂且容易使人迷惑，就直接在main函数里完成代码了
int main(){
    int m,n;
    scanf("%d %d",&m,&n);
    getchar();
    CrossList cl1;
    cl1.mu=m;
    cl1.nu=n;
    cl1.rhead=malloc((m+1)*sizeof(Olink));
    cl1.chead=malloc((n+1)*sizeof(Olink));
    CrossList cl2;
    cl2.mu=m;
    cl2.nu=n;
    cl2.rhead=malloc((m+1)*sizeof(Olink));
    cl2.chead=malloc((n+1)*sizeof(Olink));
    int i,j;
    int B1[m][n], B2[m][n], B3[m][n];
    int V1[m*n], V2[m*n], V3[m*n];

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
    cl1.tu=i;

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
    cl2.tu=i;

    //get B2
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            scanf("%d",&B2[i][j]);
            getchar();
        }
    }

    //Create list cl1, cl2
    int pv1=0, pv2=0;
    for(i=0;i<m;i++){
        cl1.rhead[i] = NULL;
        cl2.rhead[i] = NULL;
    }
    for(j=0;j<n;j++){
        cl1.chead[j] = NULL;
        cl2.chead[j] = NULL;
    }
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            if(B1[i][j]){
                OLNode *p=malloc(sizeof(OLNode));
                p->i=i; p->j=j;
                p->e=V1[pv1++];

                // Olink q=cl1.rhead[i];
                // while(q->right) q=q->right;
                // p->right=q->right;
                // q->right=p;

                // q=cl1.chead[j];
                // while(q->down) q=q->down;
                // p->down=q->down;
                // q->down=p;
                if (NULL == cl1.rhead[i] || cl1.rhead[i]->j > j){
                    p->right = cl1.rhead[i];
                    cl1.rhead[i] = p;
                } else{
                    Olink q=cl1.rhead[i];
                    for (q = cl1.rhead[i]; (q->right) && q->right->j < j; q = q->right);
                    p->right = q->right;
                    q->right = p;
                }
                if (NULL == cl1.chead[j] || cl1.chead[j]->i > i){
                    p->down = cl1.chead[j];
                    cl1.chead[j] = p;
                }else{
                    Olink q=cl1.rhead[i];
                    for (q = cl1.chead[j]; (q->down) && q->down->i < i; q = q->down);
                    p->down = q->down;
                    q->down = p;
                }
            }
            if(B2[i][j]){
                OLNode *p=malloc(sizeof(OLNode));
                p->i=i; p->j=j;
                p->e=V2[pv2++];

                // Olink q=cl2.rhead[i];
                // while(q->right) q=q->right;
                // p->right=q->right;
                // q->right=p;

                // q=cl2.chead[j];
                // while(q->down) q=q->down;
                // p->down=q->down;
                // q->down=p;
                if (NULL == cl2.rhead[i] || cl2.rhead[i]->j > j){
                    p->right = cl2.rhead[i];
                    cl2.rhead[i] = p;
                } else{
                    Olink q=cl2.rhead[i];
                    for (q = cl2.rhead[i]; (q->right) && q->right->j < j; q = q->right);
                    p->right = q->right;
                    q->right = p;
                }
                if (NULL == cl2.chead[j] || cl2.chead[j]->i > i){
                    p->down = cl2.chead[j];
                    cl2.chead[j] = p;
                }else{
                    Olink q=cl2.rhead[i];
                    for (q = cl2.chead[j]; (q->down) && q->down->i < i; q = q->down);
                    p->down = q->down;
                    q->down = p;
                }
            }
        }
    }
    cl1=addcl(cl1, cl2);
    printlist(cl1);
}

CrossList addcl(CrossList cl1, CrossList cl2){
    int i;
    for(i=0;i<cl1.mu;i++){
        OLNode *p1=cl1.rhead[i];
        OLNode *p2=cl2.rhead[i];
        while(p2!=NULL){
            if(p1==NULL || p1->j>p2->j){
                OLNode *q=malloc(sizeof(OLNode));
                *q=*p2;
                Olink r=cl1.rhead[i];
                if(r==p1){
                    cl1.rhead[i]=q;
                    cl1.rhead[i]->right=p1;
                }else{
                    while(r->right!=p1) r=r->right;
                    q->right=r->right;
                    r->right=q;
                    // cl1.rhead[i]=r;
                }
                Olink c=cl1.chead[p2->j];
                if(c==NULL){
                    cl1.chead[p2->j]=q;
                    q->down=NULL;
                }else if(c->down==NULL){
                    if(c->i<i){
                        cl1.chead[p2->j]->down=q;
                        q->down=NULL;
                    }else{
                        q->down=c;
                        cl1.chead[p2->j]=q;
                    }
                    // while(c->i<i) c=c->down;
                    // q->down=c->down;
                    // c->down=q;
                }else{
                    while(c->down!=NULL) {
                        if(c->down->i>i) break;
                        c=c->down;
                    }
                    q->down=c->down;
                    c->down=q;
                }
                cl1.tu++;
                p2=p2->right;
            }else if(p1->j<p2->j){
                p1=p1->right;
            }else if(p1->j==p2->j && (p1->e+p2->e)!=0){
                p1->e=p1->e+p2->e;
                p2=p2->right;
                p1=p1->right;
            }else if(p1->j==p2->j && (p1->e+p2->e)==0){
                Olink r=cl1.rhead[i];
                if(r==p1) {
                    cl1.rhead[i]=p1->right;
                }else{
                    while(r->right!=p1) r=r->right;
                    r->right=p1->right;
                }
                Olink c=cl1.chead[p2->j];
                if(c==p1) {
                    cl1.chead[p2->j]=p1->down;
                }else{
                    while(c->down!=p1) c=c->down;
                    c->down=p1->down;
                }
                p1=p1->right;
                cl1.tu--;
                p2=p2->right;
            }
            // p2=p2->right;
        }
    }
    return cl1;
}

void printlist(CrossList cl){
    int m=cl.mu;
    int n=cl.nu;
    int t=cl.tu;
    CrossList cl2=cl;
    Olink r=malloc(sizeof(Olink));
    int B[m][n];
    int V[t];
    int i,j,k=0;
    for(i=0;i<m;i++){
        r=cl2.rhead[i];
        for(j=0;j<n;j++){
            // if(r->j==j){
            //     B[i][j]=1;
            //     V[k++]=r->e;
            //     if(!r->right) r=r->right;
            // }else B[i][j]=0;
            if(!r || r->j!=j){
                B[i][j]=0;
            }else if(r->j==j){
                B[i][j]=1;
                V[k++]=r->e;
                r=r->right;
            }
        }
    }
    // for(k=0;k<t;k++){
    //     printf("%d ",V[k]);
    // }
    // printf("\n");
    // for(i=0;i<m;i++){
    //     for(j=0;j<n;j++){
    //         printf("%d ",B[i][j]);
    //     }
    // }

    for(i=0;i<t-1;i++){
        printf("%d ",V[i]);
    }
    if(t) printf("%d",V[t-1]);
    printf("\n");
    for(i=0;i<m;i++){
        for(j=0;j<n-1;j++){
            printf("%d ",B[i][j]);
        }
        printf("%d\n",B[i][n-1]);
    }
}