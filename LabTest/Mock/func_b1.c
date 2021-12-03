#include "common.h"

int numdiff(const int l[], const int n)
{

    if(n==0){
        return 0;
    }

    if(l==NULL){
        return 0;
    }

    int *num;
    num = (int *)malloc(n*sizeof(int));
    int repeat = 0;
    int k=0;

    for(int i=0;i<n;i++){
        num[i] = -1;
    }

    for(int i=0;i<n;i++){
        repeat = 0;
        for(int j=0;j<n;j++){
            if (l[i] == num[j]){
                repeat = 1;
            }
        }
        if(repeat == 0){
            num[k]=l[i];
            k++;
        }
    }


    free(num);
    return k;
}          
