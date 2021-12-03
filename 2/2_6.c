#include<stdio.h>
#include<assert.h>

int Numbers(int a);
void test(void);

int main(void){
    test();
    /*printf("line 1 is '%d' ",Numbers(1));
    printf("line 2 is '%d' ",Numbers(2));
    printf("line 3 is '%d' ",Numbers(3));
    printf("line 4 is '%d' ",Numbers(4));*/
    return 0;
}

int Numbers(int a){
    int re=0;
    if (a == 1){
        return 1;
    }
    re = a + Numbers(a-1);

    return re;
}

void test(void){
    assert(Numbers(1)==1) ;
    assert(Numbers(2)== 3) ;
    assert(Numbers(3) == 6);
    assert(Numbers(4)== 10) ;
    assert(Numbers(5)== 15) ;
    assert(Numbers(6)== 21) ; 
}
