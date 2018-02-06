#include <stdio.h>
#define BUF_SIZE 32

int checksp(int c)
{
    if(c == ' ' || c == '\n' || c == '\t'){
        return 1;
    }else{
        return 0;
    }
}

void compress(char *s)
{
    char *p;
    p = s;
    /* 行頭の空白を消去 */
    while( checksp(*p) ){
        p++;
    }

    int temp;
    while(*p != '.'){
        temp = 0;
        while( checksp(*p)){
            temp++;
            p++;
        }
        if (temp != 0) p--;
        if (*p == ',' || *p == '.' || *p == '!' || *p == '?') s--;
        *s = *p;
        s++;
        p++;
    }
    if (*p == ',' || *p == '.' || *p == '!' || *p == '?') s--;
    *s = '.';
    s++;
    *s = '\0';
}


int main(void)
{
    char s[] = "     Nice to \n meet \t you    ,  Jack !\n     I'm      Mike \n\t\t .    ";

    printf("Before = \"%s\"\n",s);
    //printf("hi");
    compress(s);

    printf("After  = \"%s\"\n",s);

    return 0;
}
