#include<stdio.h>
#include<math.h>

int main(void){
    printf("Enter two times :");
    int h1,h2;
    int m1,m2;

    scanf("%d:%d %d:%d",&h1,&m1,&h2,&m2);

    int min1,min2;
    min1 = h1 * 60 + m1;
    min2 = h2 * 60 + m2 + 24*60;

    int min;
    min = min2 - min1;

    int h,m;
    h = min / 60;
    m = min % 60;

    printf("Difference is : %d:%d\n",h,m);


    return 0;
}