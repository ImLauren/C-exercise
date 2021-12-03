#include "common.h"

int closestmean(const int l[], const int n)
{
    int avg=0;
    int sum=0;
    for(int i=0;i<n;i++){
        sum = sum + l[i];
    }
    avg = sum/n;

    int dis[n];

    for(int i=0; i<n;i++){
        dis[i] = abs(l[i]-avg);
    }

    int min=dis[0];
    int num=0;
    for(int i=0; i<n; i++){
        if(dis[i]<min){
            min = dis[i];
            num = i;
        }
    }

    return l[num];    
}          
