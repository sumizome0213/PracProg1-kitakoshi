/* 2���T���؂ɂ��T�� */

#include <stdio.h>

#define KEY_SIZE        8

struct tree{
    struct tree *left;
    int no;
    struct tree *right;
};

/* ���l�̓��͗p�֐� */
int get_num(void) {
    int  i;
    int  d = 0;
    int  c = 0;
    rewind(stdin);
    for( i = 0; i < 5 && c != '\n' ; i++ ){ /* 5�P�^�܂� */
        c = getchar();
        if ( c == '\n' ) break;
        d = d * 10 + c - '0';
    }
    rewind(stdin);
    return d;
}

/* �m�[�h�̒ǉ� */
struct tree *add_node(int num) {
    struct tree *p;
    p = (struct tree *)malloc(sizeof(struct tree));
    p->left = NULL;
    p->no = num;
    p->right = NULL;
    return p;
}

/* �c���[�̍쐬 */
struct tree *make_tree(struct tree *node, int num) {
    if( node == NULL ){
        node = add_node(num);
        return node;
    }
    if ( num > node->no )
        node->left = make_tree(node->left,num);
    if ( num < node->no )
        node->right = make_tree(node->right,num);
    return node;
}

/* �c���[�̕\�� */
void print_tree(struct tree *node) {
    int i;
    static int depth = 0;
    if( node->left != NULL ){
        depth ++;
        print_tree(node->left);
        depth --;
    }
    for( i = 0; i < depth; i++ )
        printf("\t");
    printf("[%2d]\n",node->no);
    if( node->right != NULL){
        depth ++;
        print_tree(node->right);
        depth --;
    }
}

/* �c���[�̒T���֐� search ������ */
int serch(struct tree *node){
    printf("key-> ");
    int num = get_num();

    printf("\n");

    while(1){

        printf("[%d]->",node->no);

        if(node->no == num) {
            printf("Found.\n");
            return 0;
        }else if (node->no < num) {
            node = node->left;
        }else if (node->no > num) {
            node = node->right;
        }

        if (node == NULL) break;
    }

    printf("Not Found.\n");
    return -1;
}

int main(void) {
struct tree *root;
int i, num;
char c[128] = "";

for( i = 0; i < KEY_SIZE; i++ ){
    printf("%d> ",i+1);
    num = get_num();
    if( i == 0 ){
        root = make_tree(NULL,num);
    }
    else{
        make_tree(root,num);
    }
}
print_tree(root);

/* �L�[���͂ɂ����s����~�����܂ŁA�T���L�[��
* ���͂ƒT���A���ʂ̕\�����J��Ԃ�
*/

printf("\n");

while(1){
    serch(root);

    printf("Do you wanna continue(yes/no)?");
    scanf("%s",c);
    if(!strcmp(c, "no")) break;
}

return 0;
}
