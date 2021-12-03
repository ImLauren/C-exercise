#include<stdio.h>

int main(void){
    int money = 0;
    int d = 0;
    do{
        printf("How much money would you like ?");
        scanf("%d",&money);
        d = money/20;
        if (money % 20 != 0){
            printf("I can give you %d or %d , try again .\n",20*d,20*(d+1));
        }
    }while( money%20 != 0);
    printf("OK , dispensing ...\n");

    return 0;
}