#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int r,c;
}PosType;
typedef struct{
    PosType seat;       // current position
    PosType former;     // former position
    int di;             // direction to next seat
}ElemType;

typedef struct Node{
    ElemType data;
    struct Node *next;
}QNode;
typedef struct {
    QNode *front;
    QNode *rear;
}LinkedQueue;

int InitQueue(LinkedQueue *lq){
    lq->front = lq->rear = (QNode *)malloc(sizeof(QNode));
    if(!lq->front) return 0;
    lq->front->next = NULL;
    return 1;
}

int GetLen(LinkedQueue *lq){
    int i;
    QNode *p;
    p = lq->front->next;
    i = 0;
    while(!p){
        i++;
        p = p->next;
    }
    return i;
}

int IsQueueEmpty(LinkedQueue *lq){
    if(lq->front == lq->rear) return 1;
    else return 0;
}

int GetFront(LinkedQueue *lq, ElemType *e){
    if(lq->front == lq->rear) return 0;
    *e = lq->front->next->data;
    return 1;
}

int Enqueue(LinkedQueue *lq, ElemType e){
    QNode *p = (QNode *)malloc(sizeof(QNode));
    if(!p) return 0;
    p->data = e;
    p->next = NULL;
    lq->rear->next = p;
    lq->rear = p;
    return 1;
}

int Dequeue(LinkedQueue *lq, ElemType *e){
    QNode *p;
    if(lq->front == lq->rear) return 0;
    p = lq->front->next;
    *e = p->data;
    lq->front->next = p->next;
    if(lq->rear == p) lq->rear=lq->front;
    free(p);
    return 1;
}

void PrintQueue(LinkedQueue *lq){
    QNode *p;
    p = lq->front->next;
    while(p!=NULL){
        printf("%d %d",p->data.seat.r,p->data.seat.c);
        p=p->next;
    }
    printf("\n");
}

// ------------------------------------------------
int m,n;
char maze[100][100];

void PrintMaze(int m, int n){
    int i,j;
    for(i=0;i<m;i++) {
        for(j=0;j<n;j++)
        printf("%c",maze[i][j]);
        printf("\n");
    }
    printf("\n");
}

//在迷宫的当前位置记录路径(+)
void PathMark(PosType CurPos) {
    maze[CurPos.r][CurPos.c]='+';
}

//在迷宫的当前位置留下走过标记(*)
void FootPrint(PosType CurPos) {
    maze[CurPos.r][CurPos.c]='*';
}

// 判定迷宫的当前位置是否可通过(即未曾走到过的通道块)
int Pass(PosType CurPos) {
    if (maze[CurPos.r][CurPos.c]=='0')
        return 1; // 如果当前位置是空格，则可以通过
    else return 0;//可能是墙，可能已经走过：包括当前的路径和被标记为走不通的通道块
}

//返回当前位置的Dir方向所指示的位置
PosType NextPos(PosType CurPos, int Dir) {
PosType ReturnPos;
	switch (Dir) {
        case 1: ReturnPos.r=CurPos.r; ReturnPos.c=CurPos.c+1; break;
        case 2: ReturnPos.r=CurPos.r+1;ReturnPos.c=CurPos.c; break;
        case 3: ReturnPos.r=CurPos.r; ReturnPos.c=CurPos.c-1; break;
        case 4: ReturnPos.r=CurPos.r-1;ReturnPos.c=CurPos.c; break;
    }
    return ReturnPos;
}

ElemType trajectories[1000]; int traP=0;
void PrintTrajectory(ElemType endp, int time){// time 标记是不是第二次调用
    int i; PosType tmp; int len=0; PosType path[1000];
    ElemType seeTrajectories[1000];
    // PathMark(endp.seat);
    path[len++]=endp.seat;
    tmp=endp.former;
    for(i=traP-1;i>=0;i--){
        if(trajectories[i].seat.r==tmp.r && trajectories[i].seat.c==tmp.c){
            // PathMark(trajectories[i].seat);
            path[len++]=trajectories[i].seat;
            tmp = trajectories[i].former;
            seeTrajectories[i]=trajectories[i];
        }
    }
    // printf("\n");
    // PrintMaze(m, n);
    len--;
    if(time == 2) len--;
    while(len>=0){
        printf("%d %d\n",(path[len].r+1), (path[len].c+1));
        len--;
    }
    return;
}

int main() {
    LinkedQueue workingQ;
    ElemType tmpBlock,qHead;
    PosType start1,end1,npos;

    scanf("%d %d",&m,&n);
    getchar();
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            maze[i][j]=getchar();
            if(maze[i][j]=='R'){
                maze[i][j]='0';
                start1.r=i;
                start1.c=j;
            }else if(maze[i][j]=='Y'){
                maze[i][j]='0';
                end1.r=i;
                end1.c=j;
            }
        }
        getchar();
    }

    // PrintMaze(m,n);
    //start1.r=1;start1.c=1; end1.r=8;end1.c=1;
    tmpBlock.seat=start1; tmpBlock.former=start1;tmpBlock.di=1;
    InitQueue(&workingQ); Enqueue(&workingQ,tmpBlock);
    while(!IsQueueEmpty(&workingQ)){
        Dequeue(&workingQ, &qHead);
        if(qHead.seat.c == end1.c && qHead.seat.r == end1.r){
            PrintTrajectory(qHead, 1);
            break;
        } else trajectories[traP++]=qHead;

        for(int dj=1;dj<=4;dj++){
            npos=NextPos(qHead.seat, dj);
            if(Pass(npos)) {
                tmpBlock.seat=npos;
                tmpBlock.former=qHead.seat;
                tmpBlock.di=dj;
                Enqueue(&workingQ,tmpBlock);
                FootPrint(npos);
                // printf("\n");
                // PrintMaze(m,n);
                // printf("\n");
            }
        }
    }

    start1=end1;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            if(maze[i][j]=='*' || maze[i][j]=='+'){
                maze[i][j]='0';
            }else if(maze[i][j]=='C'){
                maze[i][j]='0';
                end1.r=i;
                end1.c=j;
            }
        }
    }

    tmpBlock.seat=start1; tmpBlock.former=start1;tmpBlock.di=1;
    InitQueue(&workingQ); Enqueue(&workingQ,tmpBlock);
    while(!IsQueueEmpty(&workingQ)){
        Dequeue(&workingQ, &qHead);
        if(qHead.seat.c == end1.c && qHead.seat.r == end1.r){
            PrintTrajectory(qHead, 2);
            break;
        } else trajectories[traP++]=qHead;

        for(int dj=1;dj<=4;dj++){
            npos=NextPos(qHead.seat, dj);
            if(Pass(npos)) {
                tmpBlock.seat=npos;
                tmpBlock.former=qHead.seat;
                tmpBlock.di=dj;
                Enqueue(&workingQ,tmpBlock);
                FootPrint(npos);
                // printf("\n");
                // PrintMaze(m,n);
                // printf("\n");
            }
        }
    }
    return 0;
}
