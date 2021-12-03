#include<stdio.h>
#include<assert.h>
#include<math.h>
#define N 100000
#define e 2.71828182845904523536

double Number(doulbe num);

int main(void){
    doulbe num = e;
    Number(num);
    return 0;
}

double Number(doulbe num){
    double i,j;
    double n=0;
    double re=0;
    double k;
    for (i=1;i<N;i++){
        for(j=(i*2);j<(i*3) && j<N;j++){
            n = j/i;
            k = n-num;
            if (fabs(k)<0.000000001){
                re = n;
                printf("the approximation of e is %.1f/%.1f=%.15f\n",j,i,re);
            }
        }

    }
    return re;
}