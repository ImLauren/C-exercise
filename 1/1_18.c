#include<stdio.h>
#include<stdlib.h>


int main(void){
    int num;
    int number1 = rand() % 100+1;

    do{
        printf("Please gusses a numer:");
        scanf("%d",&num);
        if (num != number1){
            if(num > number1){
                printf("your number is large.\n");
            }else{
                printf("your number is small.\n");
            }
            
        }
    }while(num != number1);
    printf("You are right!\n");

    return 0;
}