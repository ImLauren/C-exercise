#include "common.h"

char* strnodupes(const char* s)
{
    char *news;
    int l = strlen(s);
    news = (char *)malloc((l+1)*sizeof(char));
    news[0] = '1';
    int repeat=0;
    int k=0;
    for(int i=0;i<l;i++){
        repeat=0;

        for(int j=0;j<k+1;j++){
            if(s[i] == news[j]){
                repeat = 1;
            }
        }

        if(repeat ==0 ){
            news[k] = s[i];
            k++;
        }

    }
    news[k]='\0';

    return news;
}
