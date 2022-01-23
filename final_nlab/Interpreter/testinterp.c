#include "interp.h"


int main(void)
{
    /*test all codes （needs nlb files in 'file' folder)
    the following will print all the result values */
    assert(test_file("./file/trivial.nlb"));
    printf("\n");
    assert(test_file("./file/setprinta.nlb"));
    printf("\n");
    assert(test_file("./file/setprintb.nlb"));
    printf("\n");
    assert(test_file("./file/setprintc.nlb"));
    printf("\n");
    assert(test_file("./file/onesprint.nlb"));
    printf("\n");
    assert(test_file("./file/loopa.nlb"));
    printf("\n");
    assert(test_file("./file/loopb.nlb"));
    printf("\n");
    assert(test_file("./file/nestedloop.nlb"));
    printf("\n");
    assert(test_file("./file/lifeb3s23.nlb"));
    printf("\n");
    assert(test_file("./file/test1.nlb"));
    printf("\n");
    assert(test_file("./file/test2.nlb"));
    
    return 0;
}


bool test_file(char filename[MAXTOKENSIZE])
{
    FILE *fp;
    if((fp = fopen(filename,"r")) == NULL){
        ERROR("No file?");
    }
    fp = fopen(filename,"r");
    Program* p = calloc(1, sizeof(Program));

    int i = 0;
    char notes[MAXNUMTOKENS];  
    char str[MAXTOKENSIZE];
    while(fscanf(fp,"%s",str)==1 && i<MAXNUMTOKENS){
        if(!strcmp(str,"#")) 
        {
            fscanf(fp, "%[^\n]s", notes);  
        }
        if(strcmp(str,"#")) 
        {
            strcpy(p->codes[i], str);
            i++;
        }
    }
    assert(i<MAXNUMTOKENS);
    p->cw = 0;

    p->Heads = (varval*)malloc(MAXVAR*sizeof(varval));
    for(int i=0; i<MAXVAR; i++) {
        p->Heads[i].row = -1;
        p->Heads[i].col = -1;
    }

    p->stack = (stackvar*)malloc(1*sizeof(stackvar));
    p->stack->top = -1;

    Prog(p);

    fclose(fp);
    for(int i=0; i<MAXVAR; i++)
    {
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

    return true;
}

