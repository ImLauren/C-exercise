#include<stdio.h>
#include<stdlib.h>
#include<math.h>


int isprime(int n);

int main(void){
    int letter[26];
    
    for (int i=0;i<26;i++){
        letter[i]=i+'a';
    }
    int number = 0;
    int count = 0;
    char name[3];

    for(int i=0;i<26;i++){
        //是元音字母，则进入第一个循环
        if(letter[i]=='a' || letter[i]=='e' || letter[i]=='i' || letter[i]=='o' || letter[i]=='u'){
            name[0]=letter[i];
            name[2]=letter[i];
            for (int j=0;j<26;j++){
                if(i != j && letter[j]!='a' && letter[j]!='e' && letter[j]!='i' && letter[j]!='o' && letter[j]!='u'){
                    name[1]=letter[j];
                    number = 2*(i+1)+j+1;
                    if(isprime(number)==1){
                        count++;
                        printf("%d.%c%c%c ",count,name[0],name[1],name[2]);
                    }
                }
            }
        }else{
            name[0]=letter[i];
            name[2]=letter[i];
            for(int j=0;j<26;j++){
                if (letter[j]=='a' || letter[j]=='e' || letter[j]=='i' || letter[j]=='o' || letter[j]=='u'){
                    name[1]=letter[j];
                    number = 2*(i+1)+j+1;
                    if(isprime(number)==1){
                        count++;
                        printf("%d.%c%c%c ",count,name[0],name[1],name[2]);
                    }
                }
            }
        }
    }

    return 0;
}

int isprime(int n){
    int re=1;
    for(int i=2;i<n;i++){
        if(n % i ==0 ){
            re =0;
        }
    }
    return re;
}