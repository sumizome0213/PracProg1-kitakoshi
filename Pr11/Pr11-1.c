#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAX_SIZE 13
#define TRUE     1
#define FALSE    0
#define IMAX     10000 /* 想定し得る最大コストよりも大きい値を設定 */

 /* データ（隣接行列） */
int adjacent[MAX_SIZE][MAX_SIZE] = {
    {   0,  30,IMAX,  40,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  0: 東京
    {  30,   0,  90,  60, 140,  80,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  1: 埼玉
    {IMAX,  90,   0,IMAX,IMAX, 110, 330,240,IMAX,IMAX,IMAX,IMAX,IMAX},      //  2: 群馬
    {  40,  60,IMAX,   0, 130,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  3: 千葉
    {IMAX, 140,IMAX, 130,   0, 100, 260,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  4: 茨城
    {IMAX,  80, 110,IMAX, 100,   0, 170,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  5: 栃木
    {IMAX,IMAX, 330,IMAX, 260, 170,   0, 550,  80,  90,IMAX,IMAX,IMAX},     //  6: 福島
    {IMAX,IMAX, 240,IMAX,IMAX,IMAX, 550,   0, 630,IMAX,IMAX,IMAX,IMAX},     //  7: 新潟
    {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  80, 630,   0,  60, 190,IMAX,IMAX},     //  8: 山形
    {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  90,IMAX,  60,   0, 290, 180,IMAX},     //  9: 宮城
    {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 190, 290,   0, 110, 300},     // 10: 秋田
    {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 180, 110,   0, 190},     // 11: 岩手
    {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 300, 190,   0}      // 12: 青森
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


int d[MAX_SIZE][MAX_SIZE];           /* 頂点間の最小コスト */
int pre_vertex[MAX_SIZE][MAX_SIZE];  /* 最短経路 */

/* dとpre_vertexを初期化 */
void init(void)
{
    int i, j;
    for( i=0; i < MAX_SIZE; i++ ){
        for( j =0; j < MAX_SIZE; j++ ){
            pre_vertex[i][j] = i;
            d[i][j]=adjacent[i][j];
        }
    }
}

/* すべての頂点間の最短経路を探索（フロイド法） */
void search(void)
{
    /* 実装せよ */
    int i, j, k;

    for (i = 0; i < MAX_SIZE; i++){      // 経由する頂点
        for (j = 0; j < MAX_SIZE; j++){    // 開始頂点
            for (k = 0; k < MAX_SIZE; k++){  // 終端
                if (d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    pre_vertex[i][j] = pre_vertex[k][j];
                }
            }
        }
    }
}

/* 経路を表示（逆順） */
void print_path(int p, int q)
{
    int x = q;
    printf("-|%s|-",graph_data[x]);
    do{
        x = pre_vertex[p][x];
        printf("-|%s|-",graph_data[x]);
    }while(x != p);
}

int check(char name[10]){
    int i;
    for (i = 0; i < MAX_SIZE; i++) {
        if(strcmp(graph_data[i], name) == 0) return i;
    }

    return -1;
}

int main(void)
{
    int h,begin,end,flag;
    char start[10],destination[10];

    printf("出発都市を入力して下さい． : ");
    scanf("%s", &start);
    while((begin=check(start)) == -1){
        printf("都市名が存在しません．もう一度出発都市を入力して下さい． : ");
        scanf("%s", &start);
    }
    printf("到着都市を入力して下さい． : ");
    scanf("%s", &destination);
    while((end=check(destination)) == -1){
        printf("都市名が存在しません．もう一度到着都市を入力して下さい．: ");
        scanf("%s", &destination);
    }

    /* 初期化 */
    init();

    /* 探索 */
    search();

    /* 表示 */
    print_path(end, begin);   // 実行の一例
    printf("コストは%dです。\n", d[end][begin]);
    return 0;
}
