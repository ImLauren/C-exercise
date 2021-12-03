#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define p 3.14159265359

int main(void){
    double pi=0;
    double count = 1;
    double t=1;
    double a = 1;
    
    while(fabs(pi - p)>1e-9){
        t = 4/(2*count -1);
        pi += a * t;
        a = -a;
        
        count++;
    }

    printf("pi = %.9lf, count = %d\n",pi,(int)count-1);

    return 0;
}