#include<stdio.h>
#include<stdlib.h>

int scode(int a);

int main(void){
    int str=0;
    while(str != '\0'){
        str = getchar();
        str = scode(str);
        putchar(str);
    }

    printf("\n");

    return 0;
}

int scode(int a){
    int re;
    
    if(a>='A' && a<='Z'){
        re = 'Z'-a +'A';
    }else if(a>='a' && a<='z'){
        re = 'z'-a+'a';
    }else{
        re =a;
    }

    return re;
}