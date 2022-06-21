#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct RcdType{
    int key;
} RcdType;

typedef struct HeapType{
    RcdType r[MAX];
    int length;
} HeapType;

void GetHeap(HeapType *H);
void HeapAdjust(RcdType R[], int s, int m);
void HeapSort(HeapType *H);
void PrintHeap(HeapType *H);

int main(){
    HeapType *H=(HeapType *)malloc(sizeof(HeapType));
    H->length=0;
    GetHeap(H);
    HeapSort(H);
    PrintHeap(H);
    return 0;
}

void GetHeap(HeapType *H){
    char c='\0';
    int i=1;
    while(c!='\n'){
        scanf("%d", &H->r[i++]);
        H->length++;
        c=getchar();
    }
}

void HeapAdjust(RcdType R[], int s, int m){
    RcdType rc=R[s];
    int j;
    for(j=3*s-1; j<=m; j=j*3-1){
        if(j==m-1 && R[j].key<R[j+1].key) ++j;
        else if(j<m-1){
            if(R[j+1].key > R[j].key && R[j+1].key > R[j+2].key) j=j+1;
            else if(R[j+2].key > R[j].key && R[j+2].key > R[j+1].key) j=j+2;
        }
        if(rc.key >= R[j].key) break;
        R[s]=R[j];
        s=j;
    }
    R[s]=rc;
}

void HeapSort(HeapType *H){
    int i;
    for(i=(H->length+1)/3; i>0; --i)
        HeapAdjust(H->r, i, H->length);
    for(i=H->length; i>1; --i){
        RcdType mid=H->r[1];
        H->r[1]=H->r[i];
        H->r[i]=mid;
        HeapAdjust(H->r, 1, i-1);
    }
}

void PrintHeap(HeapType *H){
    int i;
    for(i=1; i<=H->length; i++){
        printf("%d", H->r[i].key);
        if(i!=H->length) printf(" ");
    }
}