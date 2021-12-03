#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*构造一个单位正方形和一个单位圆的1/4，往整个区域内随机投入点，
根据点到原点的距离判断点是落在1/4的圆内还是在圆外，从而根据落在两个不同区域的点的数目，求出两个区域的比值。
如此一来，就可以求出1/4单位圆的面积，从而求出圆周率π。*/

int main(void){
    double x,y,pi;
    int cout = 0;
    int cin = 0;

    srand(time(NULL)); //设置随机种子数，随系统时间变化

    for (int i = 0; i < 10000; i++){
        x = (double)rand()/RAND_MAX;
        y = (double)rand()/RAND_MAX;
        if (x*x + y*y > 1){
            cout ++;
        }else{
            cin ++;
        }
    }

    pi = 4 * cin / (cout + cin);

    printf("pi = %lf\n", pi);

    return 0;
}