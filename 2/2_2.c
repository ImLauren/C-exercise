#include<stdio.h>
#define N 10000000

long hailstone(long n);

int main(void){
    long i;
    long max=0;
    long cn;
    long num=0;
    for (i = 1;i<N;i++){
        cn = hailstone(i);
        if (cn > max){
            max = cn;
            num = i;
        }
    }

    //printf("\nthe number is %ld\nthe sequence is %ld\n",num,max);
    printf("%ld\n",num);

    return 0;
}


//creat a hailstone function and memory the number of sequence
long hailstone(long n){
    long a = n;
    long count = 1;
    while( a != 1){
        if (a % 2 ==0){
            a = a/2;
        }else{
            a = 3 * a + 1;
        }
        count ++;
    }
    return count;
}