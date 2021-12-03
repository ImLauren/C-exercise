#include<stdio.h>
#include<math.h>
#include<assert.h>

int test(double x);

void main(void){
    double x;
    
    scanf("%lf",&x);

    assert(test(x)==1);

}

int test(double x){
    int re;

    re = pow(sin(x),2) + pow(cos(x),2);
    printf("%d\n",re);
    return re;

}