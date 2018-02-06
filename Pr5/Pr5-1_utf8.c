//c11 modeで実行して下さい
/* Pointerを用いたリスト構造の実現 */
#include <stdio.h>
#include <string.h>

#define MAX_STATION 10                  /* 最大の駅の数 */
#define ERROR    NULL

typedef struct Station {
        char name[20+1];                /* 駅名は最大全角10文字まで */
        int  time;                      /* 前の駅からの所要時間 */
        struct Station *next_addr;      /* 次のデータのアドレス */
} STATION;

int station_num = 0;                    /* ファイルから読み込んだ駅の数 */
STATION station[MAX_STATION];           /* 数値の入力用配列 */
STATION head;

int get_num(void) {
        int  i;
        int  d = 0;
        int  c = 0;
        rewind(stdin);
        for( i = 0; i < 5 && c != '\n' ; i++ ) { /* 5ケタまで */
                c = getchar();
                if ( c == '\n' ) break;
                d = d * 10 + c - '0';
        }
        rewind(stdin);
        return d;
}

/* データファイルの読み込み */
int read_data(void)
{
        FILE *fp;
        int i;
        /* キャラクタデータ読み込み */
        fp = fopen("station_data.txt", "r");
        if ( fp == NULL ){
                fprintf(stderr,"CANNOT OPEN station_data.txt\n");
                return -1;
        }
        for( i = 0; i < MAX_STATION; i++, station_num++ ) {
                if ( fscanf(fp,"%s\t%d",station[i].name,&station[i].time) != 2 ) break;
                /* まずは読み込んだ順にリストをつなぐ */
                station[i].next_addr = &station[i+1];
        }
        fclose(fp);
        /* リストの先頭はhead.next_addrにセット */
        head.next_addr = &station[0];
        /* リストの最後はNULLを入れておく */
        station[station_num-1].next_addr = NULL;
        return 0;
}

/* 路線データを表示 */
void station_disp(void)
{
        STATION *current_addr;
        current_addr = head.next_addr;

        while(1){
                if(current_addr == NULL)
                    break;
                printf("|ADDR:%20d|\n",current_addr);
                printf("|NAME:%20s|\n",current_addr->name);
                printf("|TIME:%20d|\n",current_addr->time);
                printf("|NEXT:%20d|\n",current_addr->next_addr);
                printf("\n");

                /* current_addrを更新 */
                current_addr = current_addr->next_addr;

        }
}

/* 入力された駅がリストに存在しているかどうかのチェック */
STATION *check(char target[])
{
        /* リストをたどって指定された駅が含まれているかどうか確認 */
        STATION *current_addr;
        current_addr = head.next_addr;
        while(1){
                if( strcmp(current_addr->name, target) == 0)
                        return current_addr;
                if(current_addr->next_addr == NULL)
                        break;
                /* current_addrを更新 */
                current_addr = current_addr->next_addr;
        }
        return ERROR;
}

/* データの追加 */
void add(void)
{
        STATION *current_addr;
        char targetChar[16];    // 追加する駅の直前の駅名を格納
        int a_point; /* 配列としての追加位置 */
        int i;    /* 物理的には最後に追加する */
        a_point = station_num++;
        printf("NAME =");
        fgets(station[a_point].name,16,stdin);
        for( i=0; station[a_point].name[i] != '\n' && i != 15; i++ );
        station[a_point].name[i] = '\0';
        /* ←↑改行コードを削除するための処理 */
        printf("TIME =");
        station[a_point].time = get_num();
        station_disp();
        do{
                printf("どの駅の後に追加しますか?\nNAME =");
                fgets(targetChar,16,stdin);
                for( i=0; targetChar[i] != '\n' && i != 15; i++ );
                targetChar[i] = '\0';
                /* ↑改行コードを削除するための処理 */
        } while( (current_addr = check(targetChar)) == ERROR );
        /* データの追加（リストをつなぐ） */
        station[a_point].next_addr = current_addr->next_addr;
        current_addr->next_addr = &station[a_point];
        station_disp();
}

/* データの削除 */
void del(void)
{
        int i;
        STATION *forDel; // 削除したい要素を格納するポインタ
        STATION *current_addr;
        char targetChar[16];

        station_disp();
        do{
                printf("どの駅を削除しますか?\nNAME =");
                fgets(targetChar,16,stdin);
                for( i=0; targetChar[i] != '\n' && i != 15; i++ );
                targetChar[i] = '\0';
                /* ↑改行コードを削除するための処理 */
        } while( (forDel = check(targetChar)) == ERROR );
        current_addr = head.next_addr;
        /* 残り１つだったらそれ以上消さない */
        while(1){
                if(strcmp(current_addr->name,targetChar) == 0 && current_addr == head.next_addr){
                        /* 先頭を削除したい場合 */
                        head.next_addr = current_addr->next_addr;
                        break;
                }
                if(current_addr->next_addr == NULL){
                        break;
                }
                /* 先頭以外を削除したい場合 */
                if(current_addr->next_addr == forDel){
                        current_addr->next_addr = forDel->next_addr;
                        break;
                }
                /* current_addrを更新 */
                current_addr = current_addr->next_addr;
        }
        station_disp();
}

/* 所要時間の計算 */
void calc(void)
{
        int sum=0, i;

        STATION *current_addr;
        char targetFrom[16],targetTo[16];

        printf("どこからどこまでの所要時間を計算しますか？\n");
        do{
                printf("FROM(Station Name)=");
                fgets(targetFrom,16,stdin);
                for( i=0; targetFrom[i] != '\n' && i != 15; i++ );
                targetFrom[i] = '\0';
                /* ↑改行コードを削除するための処理 */
        } while( (current_addr =  check(targetFrom)) == ERROR );
        do{
                printf("TO(Station Name)=");
                fgets(targetTo,16,stdin);
                for( i=0; targetTo[i] != '\n' && i != 15; i++ );
                targetTo[i] = '\0';
                /* ↑改行コードを削除するための処理 */
        } while( check(targetTo) == ERROR );
        printf("%sから",targetFrom);
        printf("%sまでですね\n",targetTo);
        /* 所要時間を計算する */
        while(1){
                if(strcmp(current_addr->name,targetTo) == 0){
                        break;
                }
                if(current_addr->next_addr == NULL){
                        sum = -1;
                        break;
                }
                /* current_addrを更新 */
                current_addr = current_addr->next_addr;
                sum += current_addr->time;
        }
        printf("所要時間は%dです\n",sum);
}

/* メニュー */
int menu(void)
{
        int c;
        while( 1 ){
                printf("1.表\示\n");   // 表と示の間の"\"はおまじない（外すとどうなるか、試してみてもよい
                printf("2.追加\n");
                printf("3.削除\n");
                printf("4.所要時間\n");
                printf("5.終了\n");
                c = get_num();
                if( c >= 1 && c <= 5 )
                        break;
                else
                        printf("1〜5までの数字を入力してください\n");
        }
        switch( c ){
                case 1:
                        station_disp();
                        break;
                case 2:
                        add();
                        break;
                case 3:
                        del();
                        break;
                case 4:
                        calc();
                        break;
                case 5:
                        return 1;
        }
        return 0;
}

int main(void)
{
        int end = 0;
        end = read_data();
        while( !end ){
                end = menu();
        }
        return 0;
}
