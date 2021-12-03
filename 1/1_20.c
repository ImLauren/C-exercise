#include<stdio.h>
#include<stdlib.h>

int guess(int g);

int main(void){
 
    int a;
    int g;

    printf("Please guess a number between 0 to 35 (odd is 36 and even is 37):");
    scanf("%d",&g);

    printf("Please enter money:");
    scanf("%d",&a);

    printf("You get %d money",guess(g)*a);


    return 0;
}

int guess(int g){
    int num;
    int win;
    num = rand()%35 + 0;

    if (g == num){
        win =35;
    }else if(num % 2 ==1 && g == 36){
        win =2;
    }else if(num % 2 ==0 && g == 37){
        win = 2;
    }else{
        win = 0;
    }

    return win;
}