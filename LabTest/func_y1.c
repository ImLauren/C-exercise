#include "common.h"

int arrrun(const int a[5][5])
{
    int count=1;
    int max = 1;
    for(int j=0;j<5;j++){
        count = 1;
        for(int i=0;i<4;i++){
            if(a[i][j] == a[i+1][j]){
                count++;
            }
            if( count > max){
                max = count;
            }
            if(i!=0 && a[i][j]!=a[i-1][i] && a[i][j]!=a[i+1][j]){
                count  = 1;
            }
        }

    }

    return max;
}
