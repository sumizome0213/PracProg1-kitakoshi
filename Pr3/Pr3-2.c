#include <stdio.h>
#include <string.h>
#define BF 1
#define KMP 1
#define BM 1
#define TEXT_LENGTH 64
#define PATN_LENGTH 256
int next[PATN_LENGTH];
/* �e�L�X�g�ƃp�^�[���̕s��v�����������Ƃ��ɂǂꂾ�����炷���������\ */
int skip[PATN_LENGTH];

#define uchar unsigned char
#define max(a,b) ((a)>(b)?a:b) /* ��̐�a,b�̂����傫������Ԃ��}�N�� */

/* ������text���當����pattern����������(�͂܂����@) */
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

/* ���炵�\���쐬���� */
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

/* ������text���當����pattern����������(KMP�@) */
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


/* BM�@�p�̂��炵�\���쐬���� */
void init_skip(uchar pattern[])
{
    int i;
    int patn_len;
    patn_len = strlen(pattern);

    for( i = 0; i < 256; i++ )
        skip[i] = patn_len;
    for( i = 0; i < patn_len; i++ ){
        skip[pattern[i]] = patn_len - i - 1;
    }
    for( i = 0; i < patn_len; i++ ){
        printf("%c: skip[%2d] =  %d\n", pattern[i], pattern[i], skip[pattern[i]]);
    }

}


/* ������text���當����pattern����������(BM�@) */
int bm_search(uchar text[], uchar pattern[])
{
    int i; /* ���ڂ��Ă���e�L�X�g�̈ʒu */
    int j; /* ���ڂ��Ă���p�^�[���̈ʒu */
    int text_len, patn_len;

    text_len = strlen(text);    /* �e�L�X�g�̒������Z�b�g */
    patn_len = strlen(pattern); /* �p�^�[���̒������Z�b�g */

    i = patn_len -1; //i�Ƀe�L�X�g�̍ŏ��̒��ڈʒu���Z�b�g

    while( i < text_len ) {
        j = patn_len -1;//j�Ƀp�^�[���̍ŏ��̒��ڈʒu���Z�b�g
        for(int num = 0; num < i; num++) printf(">");
        printf("%c", pattern[j]);
        while(text[i] == pattern[j]/*�e�L�X�g�ƃp�^�[�����P������r*/ ) {
            if(j <= 0){//���ׂĂ̕�������v������
                printf(" ...success\n");
                return i;//�p�^�[�������������ʒu��Ԃ�
            }
            printf("\n");
            i--;//�e�L�X�g�̈ʒu���P�����߂�
            j--;//�p�^�[���̈ʒu���P�����߂�
            for(int num = 0; num < i; num++) printf(" ");
            printf("%c", pattern[j]);
        }
        printf(" ...failure\n");
        //printf("%c\n", text[i]);
        if(skip[text[i]] < patn_len-j){
            i += patn_len-j;
        }else{
            i += skip[text[i]];//�e�L�X�g�̒��ړ_(i)���C�s��v�ɂȂ��������ɉ��������ʂ������炷
        }
        //getchar();
    }

    return -1;//-1��Ԃ�
}


int doit(uchar text[TEXT_LENGTH+1], uchar pattern[PATN_LENGTH+1])
{
    //uchar text[TEXT_LENGTH+1];
    //uchar pattern[PATN_LENGTH+1];
    int position;
    //strcpy(text,"aabbabcabc");
    //strcpy(pattern,"abcab");

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


#if BM
    printf("--- B M ---\n");
    init_skip(pattern);
    printf("%s\n",text);
    position = bm_search(text, pattern);
    printf("position=%d\n",position);
#endif

return 0;
}

int main(void){
    uchar text[TEXT_LENGTH+1];
    uchar pattern[PATN_LENGTH+1];
    strcpy(text,"aabbabcabc");
    strcpy(pattern,"abcab");
    doit(text,pattern);
    strcpy(text,"pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko");
    strcpy(pattern,"pyokopyokomu");
    doit(text,pattern);
    return 0;
}
