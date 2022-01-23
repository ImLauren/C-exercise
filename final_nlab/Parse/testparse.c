#include "parse.h"



int main(void)
{
    //test single function
    test_single_function();

    //test all codes （needs nlb files in 'file' folder)
    assert(test_file("./file/trivial.nlb"));
    assert(test_file("./file/setprinta.nlb"));
    assert(test_file("./file/setprintb.nlb"));
    assert(test_file("./file/setprintc.nlb"));
    assert(test_file("./file/onesprint.nlb"));
    assert(test_file("./file/loopa.nlb"));
    assert(test_file("./file/loopb.nlb"));
    assert(test_file("./file/nestedloop.nlb"));
    assert(test_file("./file/lifeb3s23.nlb"));
    assert(test_file("./file/test1.nlb"));
    assert(test_file("./file/test2.nlb"));


    return 0;

}


void test_single_function()
{
    //1.test strsame function
    assert(strsame("A","A"));
    assert(strsame("B-ADD","B-ADD")); 
    assert(!strsame("B-or","B-OR"));  
    assert(!strsame("b","C"));
    assert(!strsame("AND","ADD"));

    char s[MAXTOKENSIZE]; 
    strcpy(s,"{");
    assert(strsame(s,"{"));
    strcpy(s,"U-NOT");
    assert(strsame(s,"U-NOT"));
    strcpy(s,"begin");
    assert(!strsame(s,"BEGIN")); 
    strcpy(s,"c");
    assert(!strsame(s,"D"));
    strcpy(s,"LOP");
    assert(!strsame(s,"LOOP"));


    Program* p = calloc(1, sizeof(Program));   
    //2.test Varname function
    p->cw = 0;
    strcpy(p->codes[p->cw],"$A");
    assert(Varname(p));
    p->cw = 1;
    strcpy(p->codes[p->cw],"A");
    assert(!Varname(p));
    p->cw = 2;
    strcpy(p->codes[p->cw],"$5");
    assert(!Varname(p));

    //3.test Interger function
    p->cw = 3;
    strcpy(p->codes[p->cw],"5");
    assert(Interger(p));
    p->cw = 4;
    strcpy(p->codes[p->cw],"28");
    assert(Interger(p));
    p->cw = 5;
    strcpy(p->codes[p->cw],"596");
    assert(Interger(p));
    p->cw = 6;
    strcpy(p->codes[p->cw],"a");
    assert(!Interger(p));
    p->cw = 7;
    strcpy(p->codes[p->cw],"7t");
    assert(!Interger(p));

    //4.test Putdown function
    p->cw = 0;
    assert(Pushdown(p));
    p->cw = 2;
    assert(!Pushdown(p));
    p->cw = 3;
    assert(Pushdown(p));
    p->cw = 7;
    assert(!Pushdown(p));

    //5.test Unaryop function
    p->cw = 8;
    strcpy(p->codes[p->cw],"U-NOT");
    assert(Unaryop(p));
    p->cw = 9;
    strcpy(p->codes[p->cw],"U-EIGHTCOUNT");
    assert(Unaryop(p));
    p->cw = 10;
    strcpy(p->codes[p->cw],"U-OR");
    assert(!Unaryop(p));

    //6.test Binaryop function
    p->cw = 11;
    strcpy(p->codes[p->cw],"B-AND");
    assert(Binaryop(p));
    p->cw = 12;
    strcpy(p->codes[p->cw],"B-TIMES");
    assert(Binaryop(p));
    p->cw = 13;
    strcpy(p->codes[p->cw],"A-ADD");
    assert(!Binaryop(p));


    free(p);
}

//Run the program and return true after normal operation
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

    return true;
}

