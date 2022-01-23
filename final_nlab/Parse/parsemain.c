#include "parse.h"


int main(int argc, char **argv)
{
    if(argc != 2){
        ERROR("No file?");
    }
    
    FILE *fp;

    if((fp = fopen(argv[1],"r")) == NULL){
        ERROR("No file?");
    }

    fp = fopen(argv[1],"r");
    Program* p = calloc(1, sizeof(Program)); 

    int i = 0;
    //Put the code into the structure and calculate whether the code length exceeds max
    char notes[MAXNUMTOKENS];  //Save comment string temporarily
    char str[MAXTOKENSIZE];
    while(fscanf(fp,"%s",str)==1 && i<MAXNUMTOKENS){
        if(!strcmp(str,"#"))  //If is # , jump to the next line
        {
            fscanf(fp, "%[^\n]s", notes);   //Read # subsequent characters until newline
        }
        if(strcmp(str,"#"))  //Do not store # in p code
        {
            strcpy(p->codes[i], str);
            i++;
        }
    }
    assert(i<MAXNUMTOKENS);

    p->cw = 0;

    Prog(p);
    fclose(fp);
    free(p);

    printf("Parsed OK\n");



    return 0;
}

