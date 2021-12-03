#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>

char* soundex(char *name, char* code);

int main(int argc, char **argv)
{
    char code[5]={0};
    if( argc==2 ){
        printf("The name's soundex code is %s\n", soundex(argv[1], code));
    }else{
        printf("Please enter a name.\n");
    }

    return 0;
}

char* soundex(char *name, char* code){
    code[0] = name[0];
    int j=0;

    while(name[j] != '\0'){
        name[j] = toupper(name[j]);
        j++;
    }
    
    int i=1;
    j=1;
    while(name[j] != '\0'){
        if(name[j]=='B' || name[j]=='F' || name[j]=='P' || name[j]=='V'){
            code[i]='1'; i++;
            if (name[j+1] == 'H' || name[j+1]=='W'){
                if(name[j+2]=='B' || name[j+2]=='F' || name[j+2]=='P' || name[j+2]=='V'){j=j+2;}
            }
        }else if(name[j]=='C' || name[j]=='G' || name[j]=='J' || name[j]=='K' || \
                 name[j]=='Q' || name[j]=='S' || name[j]=='X' || name[j]=='Z' ){
            code[i]='2'; i++;
            if (name[j+1] == 'H' || name[j+1]=='W'){
                if(name[j+2]=='C' || name[j+2]=='G' || name[j+2]=='J' || name[j+2]=='K' || \
                   name[j+2]=='Q' || name[j+2]=='S' || name[j+2]=='X' || name[j+2]=='Z' ){j=j+2;}
            }
        }else if(name[j]=='D' || name[j]=='T'){
            code[i]='3'; i++;
            if (name[j+1] == 'H' || name[j+1]=='W'){
                if(name[j+2]=='D' || name[j+2]=='T'){j=j+2;}
            }
        }else if(name[j]=='L'){
            code[i]='4'; i++;
            if(name[j+1] == 'H' || name[j+1]=='W'){
                if(name[j+2]=='L'){j=j+2;}
            }
        }else if(name[j]=='M' || name[j]=='N'){
            code[i]='5'; i++;
            if(name[j+1] == 'H' || name[j+1]=='W'){
                if(name[j+2]=='M' || name[j+2]=='N'){j=j+2;}
            }
        }else if(name[j]=='R'){
            code[i]='6'; i++;
            if(name[j+1] == 'H' || name[j+1]=='W'){
                if(name[j+2]=='R'){j=j+2;}
            }
        }
        j++;

        if (name[j]==name[j-1]){
            j++;
        }

    }

    while(i<4){
        code[i]='0';
        i++;
    }

    code [4]='\0';

    return code;

}