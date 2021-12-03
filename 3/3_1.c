#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>


int palin(char str[]);
void test(void);

int main(void){

    palin("A man, a plan, a canal: Panama!");

    test();
    return 0;
}

int palin(char str[]){
    int ch[100];
    int i=0;
    int j=0;
    int re=1;

    //printf("%s\n",str);
    //将str变成只有小写字母的字符串
    while(str[i] != '\0'){
        if(str[i] >='A' && str[i] <= 'Z'){
            ch[j] = 32+str[i];
            j++;
        }
        if(str[i] >='a' && str[i] <= 'z'){
            ch[j] = str[i];
            j++;
        }
        i++;
    }

    //printf("%s\n",str);
    
    /*for(int t=0;t<j;t++){
        putchar(ch[t]);
    }
    printf("\n")*/;

    //判是否对称
    for(int k=0; k<(j-1)/2;k++){
        if(ch[k] != ch[j-1-k]){
            re = 0;
        }
    }

    //printf("re=%d\n",re);

    return re;
}

void test(void){
    assert(palin("kayak")==1);
    assert(palin("A man, a plan, a canal: Panama!")==1);
    assert(palin("Madam, in Eden I’m Adam,")==1);
    assert(palin("Level, madam, level!")==1);
}