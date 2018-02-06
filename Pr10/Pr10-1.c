#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAX_SIZE 13
#define TRUE     1
#define FALSE    0
#define IMAX     INT_MAX

/* データ（隣接行列） */
int adjacent[MAX_SIZE][MAX_SIZE] = {
    {   0,  30,IMAX,  40,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // A: 東京
    {  30,   0,  90,  60, 140,  80,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // B: 埼玉
    {IMAX,  90,   0,IMAX,IMAX, 110, 330, 240,IMAX,IMAX,IMAX,IMAX,IMAX},     // C: 群馬
    {  40,  60,IMAX,   0, 130,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // D: 千葉
    {IMAX, 140,IMAX, 130,   0, 100, 260,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // E: 茨城
    {IMAX,  80, 110,IMAX, 100,   0, 170,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // F: 栃木
    {IMAX,IMAX, 330,IMAX, 260, 170,   0, 550,  80,  90,IMAX,IMAX,IMAX},     // G: 福島
    {IMAX,IMAX, 240,IMAX,IMAX,IMAX, 550,   0, 630,IMAX,IMAX,IMAX,IMAX},     // H: 新潟
    {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  80, 630,   0,  60, 190,IMAX,IMAX},     // I: 山形
    {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  90,IMAX,  60,   0, 290, 180,IMAX},     // J: 宮城
    {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 190, 290,   0, 110, 300},     // K: 秋田
    {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 180, 110,   0, 190},     // L: 岩手
    {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 300, 190,   0}      // M: 青森
};

char *graph_data[] = {  // 上記隣接行列の0〜12番目の各要素に対応
    "Tokyo",
    "Saitama",
    "Gunma",
    "Chiba",
    "Ibaraki",
    "Tochigi",
    "Fukushima",
    "Niigata",
    "Yamagata",
    "Miyagi",
    "Akita",
    "Iwate",
    "Aomori"
};


int visited[MAX_SIZE];  /* 調べた頂点を記憶 */
int cost[MAX_SIZE];             /* コスト */
int prev[MAX_SIZE];             /* 直前の頂点 */

void print_path(void)
{
    int i;
    for( i = 0; i < MAX_SIZE; i++ ){
        printf("頂点 %s 直前の頂点 %s コスト %d\n", graph_data[i], graph_data[prev[i]], cost[i] );
    }
}

void search(int start)
{
    int i;
    int min;
    int next;

    cost[start] = 0;
    do {
        min = INT_MAX;
        next = -1;
        visited[start] = TRUE;

        /* 頂点の選択処理 */
        /*各頂点の中から
        まだ訪れていない頂点iについて
            直前に選んだ頂点 start と、今調べている頂点が接続されているかチェック
                出発点から直前の頂点 start までの最小コスト(cost[start])とadjacent に格納されているコストを足す
                この値とcost[i]を比較し、小さければ
                    cost[i]を新しい値に更新する
                    prev[i]もstartに更新する
            cost[i] が min より小さければ
                min と next を更新する*/

        for (i = 0; i < MAX_SIZE; i++) {
            if(visited[i] == FALSE){
                if (adjacent[i][start] != IMAX) {
                    if (cost[i] > cost[start] + adjacent[i][start]) {
                        cost[i] = cost[start] + adjacent[i][start];
                        prev[i] = start;
                    }
                }
                if (cost[i] < min) {
                    min = cost[i];
                    next = i;
                }
            }
        }

        start = next;
    } while( start != -1 );
}

void disp(int start, int end){
    if (end == start) {
        printf("[%s]", graph_data[end]);
        return;
    }else{
        disp(start, prev[end]);
    }
    printf("->[%s]", graph_data[end]);
    return;
}

int main(void)
{
    int i, j, departure, arrival;
    int path[MAX_SIZE]; // 以下のプログラムでは初期化以降、path[]を使用していないが、
            // 最短経路保存用として使用できる（もちろん、使用しなくても良い）
    /* 初期化 */
    for( i = 0; i < MAX_SIZE; i++ ){
        visited[i] = FALSE;
        cost[i] = IMAX;
        /* 最短経路保存用の配列初期化 */
        path[i] = -1;
    }

    /* 都県情報の表示と、出発、到着地点の入力 */
    for (i = 0; i < MAX_SIZE; i++) {
        printf("%d: %s\n", i, graph_data[i]);
    }

    printf("出発地点を入力して下さい:");
    scanf("%d", &departure);
    printf("到着地点を入力して下さい:");
    scanf("%d", &arrival);

    /* 探索 */
    search( departure );

    /* 表示 */
    print_path();

    /* 最短経路の表示 */
    disp(departure, arrival);
    printf(" : cost=%d\n", cost[arrival]);

    return 0;
}
