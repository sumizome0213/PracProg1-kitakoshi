/* グラフ構造の幅優先探索 */

#include<stdio.h>

#define TRUE            1
#define FALSE           0
#define MAX_SIZE        11

int adjacent[MAX_SIZE][MAX_SIZE]; /* 隣接行列 */
int visited[MAX_SIZE];
int open_list[MAX_SIZE]; /* キュー */
int qnum = 0;

char *graph_data[] = {
    "CI",      /* A : C I */
    "DGH",     /* B : D G H */
    "ADG",     /* C : A D G */
    "BCHIJ",   /* D : B C H I J */
    "FHJ",     /* E : F H J */
    "EGK",     /* F : E G K */
    "BCF",     /* G : B C F */
    "BDEJ",    /* H : B D E J */
    "AD",      /* I : A D */
    "DEHK",    /* J : D E H K */
    "FJ"       /* K : F J */
};


/* グラフの初期化 */
void init_graph(void) {
    printf("隣接行列:\n");
    int i, j, k;
    for (i = 0; i < MAX_SIZE; i++) {
        for (j = 0; j < MAX_SIZE; j++) {
            adjacent[i][j] = 0;
        }
    }

    for( i = 0; i < MAX_SIZE; i++ ){
        for( j = 0; (k = graph_data[i][j]) != '\0'; j++ ){
            adjacent[i][k-'A'] = 1;
        }
    }

    for (i = 0; i < MAX_SIZE; i++) {
        for (j = 0; j < MAX_SIZE; j++) {
            printf("%d",adjacent[i][j] );
        }
        printf("\n");
    }
}

/* キューの初期化 */
void init_queue(int *q)
{
    int i;
    for( i = 0; i < MAX_SIZE; i++ ){
        q[i] = -1;
    }
}

/* キューの表示 */
void print_queue(int *q)
{
    int i;
    printf("open_list = {");
    for( i = 0; i < MAX_SIZE; i++ )
        if( q[i] != -1 )
            printf("%c",q[i]+'A');
    printf("}\n");
}

/* キューの中にデータdが存在しているかどうかをチェック */
int check_queue(int *q,int d)
{
    int i;
    for( i = 0; i < MAX_SIZE;i++ )
        if( q[i] == d ) return TRUE;
    return FALSE;
}

/* キューにデータを入れる */
void enqueue(int *q, int d)
{
    q[qnum] = d;
    qnum++;
}

/* キューからデータを取り出す */
int dequeue(int *q)
{
    int tmp = q[0], i;
    qnum--;
    for(i=1; i < MAX_SIZE; i++) q[i-1] = q[i];
    return tmp;
}

/* 経路の探索（幅優先探索） */
void search(int now, int end)
{
    init_queue(open_list);
    enqueue(open_list, now);
    visited[now] = 1;

    printf("searching ... %c\n", now + 'A');
    print_queue(open_list);

    while ((now = dequeue(open_list)) != -1) {
        visited[now] = 1;
        if (now == end) {
            printf("Found.\n");
            return;
        }else{
            int i = 0;
            for(i = 0; i < MAX_SIZE; i++){
                if(adjacent[now][i] == 1 && visited[i] == 0 && check_queue(open_list, i) == 0) {
                    enqueue(open_list, i);
                    printf("searching ... %c\n", i + 'A');
                    print_queue(open_list);
                }
            }
        }
    }
}

/* メイン関数 */
int main(void)
{
    init_graph();

    search(0, 10 );    /* A から K の経路 */
    return 0;
}
