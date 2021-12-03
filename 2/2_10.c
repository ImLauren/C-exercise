#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>

void list(int num);

int main(void){
    int num;
    printf("How  many  songs  required ?");
    scanf("%d",&num);
    list(num);
    return 0;

}

void list(int num){
    int a[num];
    int used[num]; //创建一个数组，表示用过的数字
    int i=0;
    used[0]=0;

    for(i=0;i<num;i++){
        a[i] = rand()%num+1;
        while(used[a[i]]==1){   //如果数字用过，则重新赋值a[i]的值，直到用到没用过的数字
            a[i] = rand()%num+1;
        }
        used[a[i]]=1;
    }
    
    for(i=0;i<num;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}