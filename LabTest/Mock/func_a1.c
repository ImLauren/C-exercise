#include "common.h"

bool struses(const char* s1, const char* s2)
{
    int l1 = strlen(s1);
    int l2 = strlen(s2);

    if(l1==0 && l2>0){
        return true;
    }

    if(l1>0 && l2==0){
        return false;
    }

    int a[l1];
    for(int i=0;i<l1;i++){
        a[i]=0;
    }
    int j=0;

    for(int i=0;i<l1;i++){
        j=0;
        while(a[i] == 0 && j<l2){
            if(s1[i] == s2[j]){
                a[i]=1;
            }else{
                a[i]=0;
            }
            j++;
        }
    }

    for(int i=0; i<l1;i++){
        if (a[i] == 0 ){
            return false;
        }
    }

    return true;
}
