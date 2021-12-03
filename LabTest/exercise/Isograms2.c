#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int isogram(char *s);
void FindLongest(FILE *fp);

int main(int argc, char **argv)
{
    FILE* fp;
    if(argc==2){
        if((fp = fopen(argv[1],"r"))==NULL){
            exit(EXIT_FAILURE);
        }
    }else{
        printf("Please enter a file name.\n");
        exit(EXIT_FAILURE);
    }

    fp = fopen(argv[1],"r");
    FindLongest(fp);

    fclose(fp);
    return 0;
}

int isogram(char *s)
{
    int letter[26]={0};
    int l=strlen(s);

    for(int i=0; i<l;i++){
        for(int j='a';j<'a'+26;j++){
            if(s[i] == j){
                letter[j-'a']++;
            }
        }
    }

    for(int i=0;i<26;i++){
        if(letter[i]>1){
            return 0;
        }
    }

    return 1;
}

void FindLongest(FILE *fp)
{
    char s[100]={'\0'};
    char word[100]={'\0'};
    char ch='\0';
    int l=0;
    int re=0;
    int max=0;
    int i=0;
    while((ch = getc(fp)) != EOF){
        if(ch!='\n' && ch!=' '){
            s[i] = ch;
            i++;
        }else{
            s[i] = '\0';
            re=isogram(s);
            if(re == 1){
                l = strlen(s);
                if(max<l){
                    max = l;
                    strcpy(word,s);
                }
            }
            for(int j=0;j<=i;j++){
                s[j]='\0';
            }
            i=0;
        }
    }

    printf("The longest word is %s\n", word);
    printf("The length is %d\n", max-1);

}

