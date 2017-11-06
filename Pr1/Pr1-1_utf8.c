#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* dev-c++コンパイラでは，上記の"<"や">"と"stdio.h"との間にスペースを入れると
   コンパイル時に不具合が発生することがあるので，スペースは入れないように */

#define LINEAR 0  /* 1:線形探索，0:二分探索 */
#define NORMAL 1  /* 1:通常版，  0:番兵版   */
#define LOOP   0  /* 1:ループ版，0:再帰版   */

#define N  30000  /* 探索するレコード数 (注意：この値"だけ"を変えても、実際の検索レコード数は増えない） */

/* 線形探索 */
int l_search(int data[], int target)
{
    int i, count = 0;
#if NORMAL   /* 通常版 */
    for ( i = 0; i < N; i++ )
        if ( target == data[i] ) {
            return i;
        }
    return -1;
#else        /* 番兵版 */
    /* 実装せよ */
    /* dataの一番最後に番兵を追加する */
    /* ループに比較条件は不要（データ中に検索キーがあっても無くても最後に番兵は見つかるから） */
    /* みつかったらループを抜ける */
    /* 番兵しかみつからなかったら-1を返す */
    /* データがみつかったらbreakしたときの添え字の値を返す */
    data[N] = target;

    while (1) {
        count++;
        if ( target == data[count]) break;
    }

    if ( count == N ) return -1;
    return count;
#endif
}

/* クイックソート */
void quick(int data[], int left, int right)
{
    /* 前期で作成したquick関数を再利用する(再利用にあたって修正が必要なら、修正後に再利用する) */
    /* クイックソートがまだ完成していない場合は既にできているもので最も速いソートを用いてよい */
    if (left < right) {
        int i = left, j = right, pivot;
        if (data[i] < data[i + (j - 1) / 2]) {
            if (data[i + (j - 1) / 2] < data[j]) pivot = data[i + (j - 1) / 2]; else if (data[j] < data[i]) pivot = data[i]; else pivot = data[j];
        } else {
            if (data[j] < data[i + (j - 1) / 2]) pivot = data[i + (j - 1) / 2]; else if (data[i] < data[j]) pivot = data[i]; else pivot = data[j];
        }
        while (1) { /* data[] を pivot 以上と以下の集まりに分割する */
            int temp;
            while (data[i] < pivot) i++; /* data[i] >= pivot となる位置を検索 */
            while (pivot < data[j]) j--; /* data[j] <= pivot となる位置を検索 */
            if (i >= j) break;
            temp = data[i];
            data[i] = data[j];
            data[j] = temp; /* data[i], data[j] を交換 */
            i++; j--;
        }
        quick(data, left, i - 1);  /* 分割した左を再帰的にソート */
        quick(data, j + 1, right); /* 分割した右を再帰的にソート */
    }
}

/* 二分探索 */
int b_search(int data[], int low, int high, int target)
{
#if LOOP
    /* ループバージョン */
    /* 実装せよ */
    /* low <= high の間はループ（low > highなら見つからなかった） */
    /* mid に low と high の中間値をセット */
    /* data[mid] より target が小さければ high を mid-1 に */
    /* data[mid] より target が大きければ low を mid+1 に */
    /* data[mid] == target だったらループを抜ける */
    /* 見つかったなら mid を返す */
    /* 見つからなかったなら -1 を返す */
    while(1){
        if(low > high){
            return -1;
        }else{
            int mid = low + (high - low) / 2;
            if(data[mid] > target){
                //binary_search(data, target, low, mid - 1);
                high = mid - 1;
            }else if(data[mid] < target){
                //binary_search(data, target, mid + 1, high);
                low = mid + 1;
            }else if(data[mid] == target){
                return mid;
            }else{
                return -1;
            }
        }
    }
#else
    /* 再帰バージョン */
    /* 実装せよ */
    /* low > high なら見つからなかったということで -1 を返す */
    /* mid に low と high の中間値をセット */
    /* data[mid] より target が小さければ前半部分で再帰 */
    /* data[mid] より target が大きければ後半部分で再帰 */
    /* data[mid] == target だったら見つかったということで mid を返す */
    if(low > high){
        return -1;
    }else{
        int mid = low + (high - low) / 2;
        if(data[mid] > target){
            return b_search(data, low, mid - 1, target);
        }else if(data[mid] < target){
            return b_search(data, mid + 1, high, target);
        }else{
            return mid;
        }
    }
#endif
}

/* メイン */
int main(void)
{
    int a[N], i, target, work[N], index;
    for( i = 0; i < N; i++ ) work[i] = rand() % N;
    clock_t start,end;
    start = clock();
#if LINEAR
#else
    quick(work,0,N-1);
#endif
    for( target = N/2-500; target < N/2+500; target++ ) {  // 検索レコード数を変えるには、この辺りを修正する必要がある
#if LINEAR
        index = l_search(work,target);
#else
        index = b_search(work,0,N-1,target);
#endif
        printf("TARGET=%d: ", target);
        if ( index != -1 )
            printf("○\n");
        else
            printf("×\n");
    }
    end = clock();
    printf("%.5f秒かかりました\n",(double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}
