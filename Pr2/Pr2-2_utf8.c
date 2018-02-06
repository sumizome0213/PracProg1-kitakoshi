#include <stdio.h>
#include <string.h>
#define BF 1
#define KMP 1
#define TEXT_LENGTH 64
#define PATN_LENGTH 16
int next[PATN_LENGTH];

/* 文字列textから文字列patternを検索する(力まかせ法) */
int brute_force_search(char text[], char pattern[])
{
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int text_len = strlen(text);
    int patn_len = strlen(pattern);
    while ( i < text_len && j < patn_len ) {
        if(text[i] == pattern[j]){
            printf("%c", pattern[j]);
            j++;
            if (j==patn_len) {
                printf(" ...success\n");
                return i - patn_len + 1;
            }
            i++;
        }else{
            l++;
            i = l;
            j=0;
            printf("%c", pattern[j]);
            printf(" ...failure\n");
            for(k = 0; k < i; k++) printf(" ");
        }
   }
   return -1;
}

/* ずらし表を作成する */
void init_next(char pattern[])
{
    int j, k, m;
    int patn_len = strlen(pattern);

    for ( j = 0; j < patn_len; j++ ) {
        if ( j < 1 ) {
            next[j] = 1;
        }else {
            for ( k = 1; k < j; k++ ) {
                for ( m = k; m < j && pattern[m] == pattern[m-k]; m++ ) ;
                if ( m == j ) break;
            }
            next[j] = k;
        }
        printf("%c: next[%2d] =  %d\n", pattern[j], j, next[j]);
    }
}

/* 文字列textから文字列patternを検索する(KMP法) */
int kmp_search(char text[], char pattern[])
{
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int text_len = strlen(text);
    int patn_len = strlen(pattern);
    while ( i < text_len && j < patn_len ) {
        if(text[i] == pattern[j]){
            printf("%c", pattern[j]);
            j++;
            if (j==patn_len) {
                printf(" ...success\n");
                return i - patn_len + 1;
            }
            i++;
        }else{
            l += next[j];
            i = l;
            j=0;
            printf("%c", pattern[j]);
            printf(" ...failure\n");
            for(k = 0; k < i; k++) printf(" ");
        }
   }
   return -1;
}

int doit(char text[TEXT_LENGTH+1])
{
    //char text[TEXT_LENGTH+1];
    char pattern[PATN_LENGTH+1];
    int position;
    //strcpy(text,"xxxtartartayx");
    strcpy(pattern,"tartay");

#if BF
    printf("--- B F ---\n");
    printf("%s\n",text);
    position = brute_force_search(text, pattern);
    printf("position=%d\n",position);
#endif

#if KMP
    printf("--- KMP ---\n");
    init_next(pattern);
    printf("%s\n",text);
    position = kmp_search(text, pattern);
    printf("position=%d\n",position);
#endif
    return 0;
}

int main(void){
    char text[TEXT_LENGTH+1];
    strcpy(text,"xxxtartartayx");
    doit(text);
    strcpy(text,"pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko");
    doit(text);
    return 0;
}
