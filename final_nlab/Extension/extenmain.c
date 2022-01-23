#include "extension.h"


int main(int argc, char **argv)
{
    if(argc != 2){
        ERROR("No file?");
    }

    FILE *fp;

    if((fp = fopen(argv[1],"r")) == NULL){
        ERROR("No file?") ;
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
            fscanf(fp, "%[^\n]s", notes);  //Read # subsequent characters until newline
        }
        if(strcmp(str,"#"))   //Do not store # in p code
        {
            strcpy(p->codes[i], str);
            i++;
        }
    }
    assert(i<MAXNUMTOKENS);
    p->cw = 0;

    //array of heads malloc
    p->Heads = (varval*)malloc(MAXVAR*sizeof(varval));
    //initialize heads
    for(int i=0; i<MAXVAR; i++) {
        p->Heads[i].row = -1;
        p->Heads[i].col = -1;
    }

    //p-stack malloc
    p->stack = (stackvar*)malloc(1*sizeof(stackvar));
    p->stack->top = -1;

    Prog(p);

    fclose(fp);

    for(int i=0; i<MAXVAR; i++)
    {
        //If the matrix is not empty, release the matrix space in heads
        if(p->Heads[i].row != -1 && p->Heads[i].col != -1)  
        {
            for(int k=0; k<p->Heads[i].row;k++)
            {
                free(p->Heads[i].arr[k]);
            }
            free(p->Heads[i].arr);
        }
    }
    free(p->Heads); 
    
    free(p->stack);
    free(p);

    return 0;
}

