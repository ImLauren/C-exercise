#include<stdio.h>
#include<stdlib.h>

int main(void){
    int vowel[5]={'a','e','i','o','u'};
    int count=0;

    for(int i='b';i<='z';i++){
        if(i !='e' && i!='i' && i !='o' && i!='u'){
            for(int j=0;j<5;j++){
                for(int k='b';k<='z';k++){
                    if(i !='e' && i!='i' && i !='o' && i!='u'){
                        count++;
                        printf("%d.%c%c%c ",count,i,vowel[j],k);
                    }
                }
            }
        }
    }

    return 0;
}