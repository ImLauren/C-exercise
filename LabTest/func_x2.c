#include "common.h"

bool strsorted(const char* s1)
{
    int num = 'a'-'A';
    int l = strlen(s1);
    char *s = (char *)malloc((l+1)*sizeof(char));

    int j=0;
    for (int i=0; i<l;i++){
        if(s1[i]>='A' && s1[i]<='z'){
            if(s1[i]<='Z' || s1[i]>='a'){
                s[j] = s1[i];
                j++;
            }
        }
    }
    s[j] = '\0';
    int l2 = strlen(s);

    for(int i=0;i<l2+1;i++){
        if(s[i]>='A' && s[i]<='Z'){
            s[i] = s[i]+num;
        }
    }

    for(int i=0;i<l2-1;i++){
        if(s[i]>s[i+1]){
            return false;
        }
    }

    free(s);
    return true;

}
