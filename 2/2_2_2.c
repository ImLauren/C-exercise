#include<stdio.h>
#define N 10000000

long hailstone(long n);

int main(void){

    long i;
    long max=0;
    long number=0;
    long cn=0; 
    for (i=1;i<N;i++){
        cn = hailstone(i);
        if (cn > max){
            max = cn;
            number = i;
        }
    }


    //printf("\nthe initial number is %ld\nthe max number is %ld\n",number,max);
    printf("%ld\n",number);

    return 0;
}


long hailstone(long n){
    long a = n;
    long max = n;
    while( a != 1){
        if (a % 2 ==0){
            a = a/2;
        }else{
            a = 3 * a + 1;
        }
        if (a>max){
            max = a;
        }
    }
    return max;
}