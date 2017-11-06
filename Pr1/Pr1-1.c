#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* dev-c++�R���p�C���ł́C��L��"<"��">"��"stdio.h"�Ƃ̊ԂɃX�y�[�X�������
   �R���p�C�����ɕs����������邱�Ƃ�����̂ŁC�X�y�[�X�͓���Ȃ��悤�� */

#define LINEAR 0  /* 1:���`�T���C0:�񕪒T�� */
#define NORMAL 1  /* 1:�ʏ�ŁC  0:�ԕ���   */
#define LOOP   0  /* 1:���[�v�ŁC0:�ċA��   */

#define N  30000  /* �T�����郌�R�[�h�� (���ӁF���̒l"����"��ς��Ă��A���ۂ̌������R�[�h���͑����Ȃ��j */

/* ���`�T�� */
int l_search(int data[], int target)
{
    int i, count = 0;
#if NORMAL   /* �ʏ�� */
    for ( i = 0; i < N; i++ )
        if ( target == data[i] ) {
            return i;
        }
    return -1;
#else        /* �ԕ��� */
    /* �������� */
    /* data�̈�ԍŌ�ɔԕ���ǉ����� */
    /* ���[�v�ɔ�r�����͕s�v�i�f�[�^���Ɍ����L�[�������Ă������Ă��Ō�ɔԕ��͌����邩��j */
    /* �݂������烋�[�v�𔲂��� */
    /* �ԕ������݂���Ȃ�������-1��Ԃ� */
    /* �f�[�^���݂�������break�����Ƃ��̓Y�����̒l��Ԃ� */
    data[N] = target;

    while (1) {
        count++;
        if ( target == data[count]) break;
    }

    if ( count == N ) return -1;
    return count;
#endif
}

/* �N�C�b�N�\�[�g */
void quick(int data[], int left, int right)
{
    /* �O���ō쐬����quick�֐����ė��p����(�ė��p�ɂ������ďC�����K�v�Ȃ�A�C����ɍė��p����) */
    /* �N�C�b�N�\�[�g���܂��������Ă��Ȃ��ꍇ�͊��ɂł��Ă�����̂ōł������\�[�g��p���Ă悢 */
    if (left < right) {
        int i = left, j = right, pivot;
        if (data[i] < data[i + (j - 1) / 2]) {
            if (data[i + (j - 1) / 2] < data[j]) pivot = data[i + (j - 1) / 2]; else if (data[j] < data[i]) pivot = data[i]; else pivot = data[j];
        } else {
            if (data[j] < data[i + (j - 1) / 2]) pivot = data[i + (j - 1) / 2]; else if (data[i] < data[j]) pivot = data[i]; else pivot = data[j];
        }
        while (1) { /* data[] �� pivot �ȏ�ƈȉ��̏W�܂�ɕ������� */
            int temp;
            while (data[i] < pivot) i++; /* data[i] >= pivot �ƂȂ�ʒu������ */
            while (pivot < data[j]) j--; /* data[j] <= pivot �ƂȂ�ʒu������ */
            if (i >= j) break;
            temp = data[i];
            data[i] = data[j];
            data[j] = temp; /* data[i], data[j] ������ */
            i++; j--;
        }
        quick(data, left, i - 1);  /* �������������ċA�I�Ƀ\�[�g */
        quick(data, j + 1, right); /* ���������E���ċA�I�Ƀ\�[�g */
    }
}

/* �񕪒T�� */
int b_search(int data[], int low, int high, int target)
{
#if LOOP
    /* ���[�v�o�[�W���� */
    /* �������� */
    /* low <= high �̊Ԃ̓��[�v�ilow > high�Ȃ猩����Ȃ������j */
    /* mid �� low �� high �̒��Ԓl���Z�b�g */
    /* data[mid] ��� target ����������� high �� mid-1 �� */
    /* data[mid] ��� target ���傫����� low �� mid+1 �� */
    /* data[mid] == target �������烋�[�v�𔲂��� */
    /* ���������Ȃ� mid ��Ԃ� */
    /* ������Ȃ������Ȃ� -1 ��Ԃ� */
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
    /* �ċA�o�[�W���� */
    /* �������� */
    /* low > high �Ȃ猩����Ȃ������Ƃ������Ƃ� -1 ��Ԃ� */
    /* mid �� low �� high �̒��Ԓl���Z�b�g */
    /* data[mid] ��� target ����������ΑO�������ōċA */
    /* data[mid] ��� target ���傫����Ό㔼�����ōċA */
    /* data[mid] == target �������猩�������Ƃ������Ƃ� mid ��Ԃ� */
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

/* ���C�� */
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
    for( target = N/2-500; target < N/2+500; target++ ) {  // �������R�[�h����ς���ɂ́A���̕ӂ���C������K�v������
#if LINEAR
        index = l_search(work,target);
#else
        index = b_search(work,0,N-1,target);
#endif
        printf("TARGET=%d: ", target);
        if ( index != -1 )
            printf("��\n");
        else
            printf("�~\n");
    }
    end = clock();
    printf("%.5f�b������܂���\n",(double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}
