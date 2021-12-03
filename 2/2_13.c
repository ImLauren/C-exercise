#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<ctype.h>

void change(char ch[]);
//void test(void);

int main(void){
    printf("Please enter a word: ");
    char ch[100];

    scanf("%s",ch);
    
    change(ch);

    printf("%s",ch);
    printf("\n");

    //test();
    return 0;
}

void change(char ch[]){
    int i=0;
    while(ch[i] !='\0'){
        if(ch[i] =='a'|| ch[i]=='e' || ch[i]=='i' || ch[i]=='o' || ch[i]=='u'){
            ch[i]= toupper(ch[i]);
        }else{
            ch[i] = tolower(ch[i]); 
        }
        i++;
    }
}
