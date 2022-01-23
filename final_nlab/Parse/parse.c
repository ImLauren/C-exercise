#include "parse.h"


bool strsame(char *s, const char *pr)
{
    if(strcmp(s,pr)==0){
        return true;
    }

    return false;
}


void Prog(Program *p)
{
    if(!strsame(p->codes[p->cw],"BEGIN")){   //the first word is BEGIN or not
        ERROR("No BEGIN statement?");
    }
    p->cw = p->cw+1;

    if(!strsame(p->codes[p->cw],"{")){   //the second word is { or not
        ERROR("No \"{\" statement?");
    }
    p->cw = p->cw+1;

    Instrclist(p);
}

void Instrclist(Program *p) 
{
    if(strsame(p->codes[p->cw],"}")){
        return;
    }

    Instrc(p);
    p->cw = p->cw+1;
    Instrclist(p);
}

void Instrc(Program *p) 
{
    if(strsame(p->codes[p->cw],"PRINT")){
        p->cw = p->cw+1;
        Print(p);
    }else if(strsame(p->codes[p->cw],"SET")){
        p->cw = p->cw+1;
        Set(p);
    }else if((strsame(p->codes[p->cw],"ONES")) || (strsame(p->codes[p->cw],"READ"))){
        Create(p);
    }else if(strsame(p->codes[p->cw],"LOOP")){
        p->cw = p->cw+1;
        Loop(p);
    }else{
        ERROR("Expecting a PRINT, SET, CREATE, LOOP or '}' statement?");
    }

}

void Print(Program *p)
{
    if (Varname(p)){
        return;
    }else if (p->codes[p->cw][0] == '\"'){
        Print_String(p);
    }else{
        ERROR("Expecting a variable or string?");
    }

}

bool Varname(Program *p)
{
    if (p->codes[p->cw][0] != '$'){
        return false;
    }
    char c = p->codes[p->cw][1];
    if(!(c>='A' && c<='Z')){
        return false;
    }

    return true;
}


void Print_String(Program *p)
{
    int len = strlen(p->codes[p->cw]);
    if (p->codes[p->cw][len-1] != '\"'){
        ERROR("Expecting a '\"' statement?");
    }

}

void Set(Program *p)
{
    if (Varname(p)){
        p->cw = p->cw+1;
    }else{
        ERROR("Expecting a variable");
    }

    if(strsame(p->codes[p->cw],":=")){
        p->cw = p->cw+1;
    }else{
        ERROR("Expecting a ':=' statement?");
    }

    Polishlist(p);
}

void Polishlist(Program *p) 
{
    if(strsame(p->codes[p->cw],";"))
    {
        return;
    }


    Polish(p);
    p->cw = p->cw+1;
    Polishlist(p);
}

void Polish(Program *p)
{
    if (Pushdown(p)){
        return;
    }else if(Unaryop(p)){
        return;
    }else if(Binaryop(p)){
        return;
    }else{
        ERROR("Expecting a Polish or ';' statement?");
    }
}

bool Pushdown(Program *p)
{
    if (Varname(p)){
        return true;
    } else if(Interger(p)){
        return true;
    }else{
        return false;
    }
}

bool Unaryop(Program *p)
{
    if(strsame(p->codes[p->cw],"U-NOT")){
        return true;
    }else if(strsame(p->codes[p->cw],"U-EIGHTCOUNT")){
        return true;
    }else{
        return false;
    }
}

bool Binaryop(Program *p)
{
    if(strsame(p->codes[p->cw],"B-AND")){
        return true;
    }else if(strsame(p->codes[p->cw],"B-OR")){
        return true;
    }else if(strsame(p->codes[p->cw],"B-GREATER")){
        return true;
    }else if(strsame(p->codes[p->cw],"B-LESS")){
        return true;
    }else if(strsame(p->codes[p->cw],"B-ADD")){
        return true;
    }else if(strsame(p->codes[p->cw],"B-TIMES")){
        return true;
    }else if(strsame(p->codes[p->cw],"B-EQUALS")){
        return true;
    }else{
        return false;
    }
}

bool Interger(Program *p)
{
    int i=0;
    char c = p->codes[p->cw][0];

    while(c != '\0'){
        if( c<48 || c>57){
            return false;
        }
        i++;
        c = p->codes[p->cw][i];
    }

    return true;
}

void Create(Program *p)
{
    if(strsame(p->codes[p->cw],"ONES")){
        p->cw = p->cw+1;
        Array_Ones(p);
    }else if(strsame(p->codes[p->cw],"READ")){
        p->cw = p->cw+1;
        Array_Read(p);
    }else{
        ERROR("Expecting a ONES or READ statement?");
    }
}

void Array_Ones(Program *p)
{
    if(Interger(p)){
        p->cw = p->cw+1;
    }else{
        ERROR("Expecting an interger of row?");
    }

    if(Interger(p)){
        p->cw = p->cw+1;
    }else{
        ERROR("Expecting an interger of column?");
    }

    if(!Varname(p)){
        ERROR("Expecting a Variable?");
    }

}

void Array_Read(Program *p)
{
    if(p->codes[p->cw][0] == '\"'){
        int len = 0;
        len = strlen(p->codes[p->cw]);
        if(p->codes[p->cw][len-1] != '\"'){
            ERROR("Expecting a '\"' statement?");
        }
        p->cw = p->cw+1;
    }else{
        ERROR("Expecting a \'\"\' statement?");
    }

    if (!Varname(p)){
        ERROR("Expecting a Variable?");
    }
}

void Loop(Program *p)
{
    if(Varname(p)){
        p->cw = p->cw+1;
    }else{
        ERROR("Expecting a Variable?");
    }

    if(Interger(p)){
        p->cw = p->cw+1;
    }else{
        ERROR("Expecting an Interger?");
    }

    if(strsame(p->codes[p->cw],"{")){
        p->cw = p->cw+1;
    }else{
        ERROR("Expecting a \'{\' statement?");
    }

    Instrclist(p);
}


