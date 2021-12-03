#include<stdio.h>
#include<assert.h>
#include<time.h>
#include<stdlib.h>
#define N 5

void game(int a[], int b[]);


int main(void){
    printf("Please choose\n 1. begin with the randomed first line\n 2. the central of first line: \n");
    int c;
    int a[N]={0};
    int b[N]={0};
    scanf("%d",&c);
    
    //第一行随机开始
    int i;
    int num;
    if (c == 1){
        srand(time(NULL));
        for (i=0;i<N;i++){
            num = rand()%2;
            a[i] = num;
        }
    }

    //第一行选定一个数为1
    if (c==2){
        num = rand()%N;
        a[num] = 1;
    }
    
    game(a,b);
    return 0;
}

void game(int a[], int b[]){
    //显示出第一行
    int i;
    for (i=0;i<N;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
    
    //计算下一行
    for(i=0;i<5;i++){
        if(a[i-1]==1 && a[i]==1 && a[i+1]==1){
            b[i]=0;
        }else if(a[i-1]==1 && a[i]==1 && a[i+1]==0){
            b[i]=1;
        }else if(a[i-1]==1 && a[i]==0 && a[i+1]==1){
            b[i]=1;
        }else if(a[i-1]==1 && a[i]==0 && a[i+1]==0){
            b[i]=0;
        }else if(a[i-1]==0 && a[i]==1 && a[i+1]==1){
            b[i]=1;
        }else if(a[i-1]==0 && a[i]==1 && a[i+1]==0){
            b[i]=1;
        }else if(a[i-1]==0 && a[i]==0 && a[i+1]==1){
            b[i]=1;
        }else if(a[i-1]==0 && a[i]==0 && a[i+1]==0){
            b[i]=0;
        }
    }
    
    for (i=0;i<N;i++){
        printf("%d ",b[i]);
    }
    printf("\n");


}