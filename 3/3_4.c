#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


int romanToarabic( char *roman );

int main(int argc, char **argv)
{
    if( argc==2 ){
        printf("The roman numeial %s is equal to %d\n", \
        argv[1], romanToarabic(argv[1]));
        }else{
            printf("EiiOi: Incoirect usage, tiy e.g. %s XXI\n", argv[0]);
        }
    
    return 0;
    
}

int romanToarabic( char *roman )
{
    int i=0;
    int re=0;
    while(roman[i] != '\0')
    {
        if (roman[i]=='I')
        {
            if (roman[i+1] == 'V'){
                re = re + 4;
                i = i+2;
            }else if(roman[i+1]=='X'){
                re = re +9;
                i = i+2;
            }else{
                re = re + 1;
                i++;
            }
        }

        if (roman[i]=='V')
        {
            re = re +5;
            i++;
        }

        if(roman[i]=='X')
        {
            if (roman[i+1]=='L'){
                re = re + 40;
                i = i+2;
            }else if(roman[i+1]=='C'){
                re = re + 90;
                i = i+2;
            }else{
                re =re + 10;
                i++;
            }
        }

        if(roman[i] == 'L')
        { 
            re = re + 50; 
            i++;
        }

        if(roman[i]=='C')
        {
            if (roman[i+1]=='D'){
                re = re + 400;
                i = i +2;
            }else if(roman[i+1]=='M'){
                re = re + 900;
                i = i+2;
            }else{
                re = re + 100;
                i++;
            }
        }

        if (roman[i]=='D'){
            re =re + 500;
            i++;
        }

        if (roman[i]=='M'){
            re = re + 1000;
            i++;
        }
    }

    return re;
}