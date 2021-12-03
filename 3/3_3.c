#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>
#include <string.h>

//typedef enum bool {false, true} bool;
void strmerge(const char* s1, const char* s2, char*s3);
#define LARGESTRING 1000

int main(void){

    char s[LARGESTRING];
    strmerge("Hello World!", "World! & Everyone.", s);
    assert(strcmp(s, "Hello World! & Everyone.")==0);
    
    strmerge("The cat sat", "sat on the mat.", s);
    assert(strcmp(s, "The cat sat on the mat.")==0);

    strmerge("The cat sat on the mat", "The cat sat on the mat.", s);
    assert(strcmp(s, "The cat sat on the mat.")==0);

    strmerge("One ", "Two", s);
    assert(strcmp(s, "One Two")==0);

    strmerge("", "The cat sat on the mat.", s);
    assert(strcmp(s, "The cat sat on the mat.")==0);

    strmerge("The cat sat on the mat.", "", s);
    assert(strcmp(s, "The cat sat on the mat.")==0);

    strmerge("123412341234", "1234", s);
    assert(strcmp(s, "123412341234")==0);

    return 0;
}

void strmerge(const char* s1, const char* s2, char*s3){

    memset(s3, 0, sizeof(*s3));

    int l2=strlen(s2);
    int l1=strlen(s1);
    int flag=0;
    int k =0;

    //s1、s2部分重叠
    for(int j=0;j<l2;j++){
        for(int i=0;i<l1;i++){
            if(s2[j]==s1[i] && s2[j+1]==s1[i+1] && s2[j+2]==s1[i+2]){
                strncpy(s3,s1,i);
                flag=1;
                k=i;
                break;
            }
            
        }
        if(flag==1){
            break;
        }
    }


    //s1、s2不同
    if(flag==0){
        strcpy(s3,s1);
        k = l1;
    }

    for(int x=0;x<l2;x++){
        s3[k]=s2[x];
        k++;
    }
    s3[k]='\0';

    //s2与s1重叠
    int l3 = strlen(s3);
    if(l3 < l1){
        strcpy(s3,s1);
    }

    printf("s3 = %s\n",s3);

}