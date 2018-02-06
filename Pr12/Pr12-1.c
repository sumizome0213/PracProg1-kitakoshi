/* �i�b�v�U�b�N���i���I�v��@�ɂ���@�j */

#include<stdio.h>
#include<stdlib.h>

/* �z��size�Avalue�͂��ꂼ��ו��̑傫���Ɖ��l��\�킵�Ă���
 * �����Y�������m���Ή����Ă���(��F�ו�0�̑傫����size[0]�A���l��value[0]�j�B
 */

/* �ו��̑傫�� */
int size[] = {2, 3, 5, 7, 9, 15};

/* �ו��̉��l */
int value[] = {2, 4, 7, 11, 14, 24};

/* �ו��̎�ނ̐� */
#define AS (sizeof(size)/sizeof(size[0]))

/* �i�b�v�U�b�N�̑傫���̏�� */
#define MAX_M   200

void DynamicProgramming(int N, int Nsize[], int Nvalue[]){
    int i,j;

    /* �����_�Ńi�b�v�U�b�N�ɋl�ߍ��񂾉ו��̉��l�̍��v */
    int total[MAX_M];

    /* �Ō�ɑI�񂾉ו� */
    int choice[MAX_M];

    /* �ו�i����ꂽ���̉��l�̍��v */
    int repack_total = 0;

    /* �z����N���A���Ă��� */
    for(i=0;i<=N;i++){
        total[i] = 0;
        choice[i] = -1;
    }

    /* �ו� i = 0AS �܂ł��l���ɓ���� */
    for(i=0;i<AS;i++){
        /* �傫��j(=Nsize[i])�̃i�b�v�U�b�N�ɑ΂��āA�ו����l�ߍ���ł݂� */
            /* �����ו�i����ꂽ�Ƃ���ƁA���l�̍��v�͂�����ɂȂ邩���v�Z���āA�ϐ�repack_total�Ɋi�[ */
            /* �ו�i����ꂽ����(����Ȃ����)���l���傫���Ȃ�̂Ȃ�A�ו�i������ */
        for (j = 0; j <= N; j++) {
            if(0 <= j-size[i]){
                if (total[j] < total[j-size[i]] + value[i]) {
                    total[j] = total[j-size[i]] + value[i];
                    choice[j] = i;
                }
            }
        }

        /* �z��total�Achoice�̒��g��\������ */
        printf("i = %d\n",i);
        printf("choice = ");
        for(j=0;j<=N;j++)
            printf("%2d ",choice[j]);
        printf("\n");
    }

    /* �ǂ̉ו����i�b�v�U�b�N�ɓ��ꂽ����\������ */
    while (size[0]<N) {
        printf("�ו� %d (���l%d)���l�ߍ���\n", choice[N], value[choice[N]]);
        repack_total += value[choice[N]];
        N -= size[choice[N]];
    }
    printf("���l�̍��v = %d\n", repack_total);

}

int main(int argc, char *argv[]){
    /* �i�b�v�U�b�N�̑傫�� */
    int m = 114514;

    /* �����̐�������Ă��Ȃ����A�i�b�v�U�b�N�̑傫��������𒴂��Ă��Ȃ���
     * ����i�K�؂Ȉ����̐��A�������͒l���ݒ肳��Ă��Ȃ��ꍇ�A�ēx���͂����߂�j
    */
    if(argv[1]!=NULL) m = atoi(argv[1]);

    while(m < 0 || 200 < m){
       printf("�R�}���h���C������������������܂���B�ēx���͂��ĉ������B : ");
       scanf("%d", &m);
   }

    /* �R�}���h��������i�b�v�U�b�N�̑傫���𓾂� */
    printf("Size of knapsack is %d\n",m);

    DynamicProgramming(m,size,value);

    return 0;
}
