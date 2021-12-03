#include<stdio.h>
#include<assert.h>
#include<math.h>
#define N 1000

int Isprime(int a);
int Isthree(int a);
void test(void);

int main(void){
    int i;
    int j=0;
    int a[1000];

    for (i=2;i<N;i++){
        if (Isprime(i)== 1){
            a[j] = i;
            j++;
        }
    }

    //i=0;
    //while(a[i]!=0){
    //    printf("%d ",a[i]);
    //    i++;
    //}

    //printf("\n");

    for(i=0;i<j;i++){
        if(Isthree(a[i])==1){
            printf("%d ",a[i]);
        }
    }

   test();
   printf("\n");
   return 0;
}

int Isprime(int a){
    int i;
    int re=1;
    for (i=2;i<=sqrt(a);i++){
        if (a%i == 0){
            re = 0;
            break;
        }
    }
    return re;
}

int Isthree(int a){
    int n =a;
    while(n>9){
        n = n % 10;
    }
    if (n == 3){
        return 1;
    }else{
        return 0;
    }
}

void test(void){
    assert(Isprime(5)==1);
    assert(Isprime(22)==0);
    assert(Isprime(23)==1);
    assert(Isprime(88)==0);
    assert(Isthree(3)==1);
    assert(Isthree(23)==1);
    assert(Isthree(54)==0);
}