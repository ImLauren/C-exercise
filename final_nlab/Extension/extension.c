#include "extension.h"


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
    }else if(strsame(p->codes[p->cw],"ONES") || strsame(p->codes[p->cw],"READ")){ 
        Create(p);
    }else if(strsame(p->codes[p->cw],"LOOP")){
        p->cw = p->cw+1;
        Loop(p);
    }else if(strsame(p->codes[p->cw],"SAVE")){
        p->cw = p->cw+1;
        Save(p);
    }else{
        ERROR("Expecting a PRINT, SET, CREATE, LOOP, SAVE or '}' statement?");
    }

}

void Print(Program *p)
{
    if (Varname(p)){
        Print_Varname(p);
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

void Print_Varname(Program *p)
{
    char c;
    c = p->codes[p->cw][1];
    int n = 0;
    n = c - 'A';    //Determine the number of variables and find them in the P variable array

    if(p->Heads[n].row !=-1 && p->Heads[n].col !=-1) 
    {
        for(int i=0; i<p->Heads[n].row; i++){
            for(int j=0; j<p->Heads[n].col; j++){
                printf("%d ", p->Heads[n].arr[i][j]);
            }
            printf("\n");
        }
    }else
    {
        ERROR("No value!");
    }
    
}

void Print_String(Program *p)
{
    int len = strlen(p->codes[p->cw]);
    if (p->codes[p->cw][len-1] != '\"'){
        ERROR("Expecting a \" statement?");
    }

    char str[MAXTOKENSIZE]; 
    strcpy(str,p->codes[p->cw]);
    int i=1;
    while(str[i] != '\"'){
        str[i-1] = str[i];
        i++;
    }
    str[i] = '\0';
    str[i-1] = '\0';

    printf("%s\n",str);
}

void Set(Program *p)
{
    if (Varname(p)){
        char c = p->codes[p->cw][1];
        int i = c - 'A';
        p->varnum = i;
        p->cw = p->cw+1;
    }else{
        ERROR("Expecting a variable?");
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
    if(strsame(p->codes[p->cw],";"))  //Assign an left value
    {
        if(p->stack->top > -1){
            int n = Pop(p->stack);
            if( n==-30 ){
                ERROR("Expecting a varialbe?"); 
            }
            if(n<0){   //n is alphabetic variable
                n = abs(n)-1;
            }else{    //n is a number
                if(p->Heads[p->varnum].row == -1){
                    p->Heads[p->varnum].arr = Init_Arr(1,1);
                }
                p->Heads[p->varnum].row = 1;
                p->Heads[p->varnum].col = 1;
                p->Heads[p->varnum].arr[0][0] = n;
                return;
            }
            int r = p->Heads[n].row;
            int co = p->Heads[n].col;
            if(p->Heads[p->varnum].row == -1){
                p->Heads[p->varnum].arr = Init_Arr(r,co);
            }
            p->Heads[p->varnum].row = r;
            p->Heads[p->varnum].col = co;
            for(int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    p->Heads[p->varnum].arr[i][j] =  p->Heads[n].arr[i][j];
                }
            }
        }
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
    bool re;
    int i=0;

    i = p->varnum;  //left value

    if (Varname(p))
    {
        re = true;
        if (strsame(p->codes[p->cw+1],";"))  //variables+; : direct assignment
        {
            char c = p->codes[p->cw][1];
            int i2 = c - 'A';
            //Determine that the matrix has a value
            if(p->Heads[i2].row != -1 && p->Heads[i2].col != -1) 
            {
                if(p->Heads[i].row != -1 &&  p->Heads[i].col != -1){
                    Delete_Arr(p->Heads[i].arr, p->Heads[i].row);
                }
                p->Heads[i].row = p->Heads[i2].row;
                p->Heads[i].col = p->Heads[i2].col;
                int r =  p->Heads[i2].row;
                int co = p->Heads[i2].col;
                // matrix  malloc
                p->Heads[i].arr = Init_Arr(r,co);
                //store value
                for (int k=0; k<r; k++){
                    for (int j=0; j<co; j++){
                        p->Heads[i].arr[k][j] = p->Heads[i2].arr[k][j];
                    }
                }
            }else{
                ERROR("Variavle is no value!");
            }
        }else    //no;  record value after :=
        {
            char c = p->codes[p->cw][1];
            int n = -1-(c-'A');   //Prevent from being the same as number, record negative values
            bool re2 = Push(p->stack,n);
            if(re2 == false){
                ERROR("The Stack is Full!");
            }
            return re;
        }

    } else if(Interger(p))
    {
        re = true;
        if (strsame(p->codes[p->cw+1],";"))  //variables+; : direct assignment
        {
            int n = atoi(p->codes[p->cw]);  //1*1 array
            p->Heads[i].row = 1;
            p->Heads[i].col = 1;
            p->Heads[i].arr = Init_Arr(1,1);
            p->Heads[i].arr[0][0] = n;
        }else
        {
            int n = atoi(p->codes[p->cw]);  //push
            bool re2 = Push(p->stack,n);
            if(re2 == false){
                ERROR("The Stack is Full!");
            }
            return re;
        }
        
    }else{
        re = false;
    }

    return re;
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

bool Unaryop(Program *p) 
{
    bool re;
    if(strsame(p->codes[p->cw],"U-NOT"))
    {
        re = true;
        int n = Pop(p->stack);
        if( n==-30 ){
            ERROR("Expecting a varialbe?"); 
        }
        //whether n is negetive value
        if (n<0){
            n = abs(n)-1 ;
        }else{  //n is number - push 1*1 array and return
            if (n>0){
                n = 0;
            }else if(n ==0 ){
                n=1;
            }
            bool re2 = Push(p->stack,n);
            if (re2 == false){
                ERROR("The Stack is Full!");
            }
            return re;
        }
        
        int r = p->Heads[n].row;   //row
        int co = p->Heads[n].col;  //col
        int **tmparr;    //temporary matrix variable
        tmparr = Init_Arr(r,co);
        
        for (int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                if (p->Heads[n].arr[i][j] ==0 ){
                    tmparr[i][j] =1;
                }else if(p->Heads[n].arr[i][j] >0){
                   tmparr[i][j] =0;
                }
            }
        }

        if (p->Heads[MAXVAR-1].row != -1){
            Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
        }
        p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
        p->Heads[MAXVAR-1].row = r;
        p->Heads[MAXVAR-1].col = co;
        for(int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                p->Heads[MAXVAR-1].arr[i][j] = tmparr[i][j];  //the last value of heads is temporary matrix variable
            }
        }
        bool re2 = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
        if (re2 == false){
            ERROR("The Stack is Full!");
        }
        
        //free tmparr
        Delete_Arr(tmparr,r);
    }else if(strsame(p->codes[p->cw],"U-EIGHTCOUNT"))
    {
        U_Eightcount(p);
        re = true;
    }else{
        re = false;
    }

    return re;
}

void U_Eightcount(Program *p)
{
    int n = Pop(p->stack);
    if( n==-30 ){
        ERROR("Expecting a varialbe?");
    }

    //whether n is negetive value
    if (n<0){
        n = abs(n)-1 ;
    }else{   //number
        n=0;
        bool re = Push(p->stack,n);
        if(re == false){
            ERROR("The Stack is Full!");
        }
        return;
    }

    int r = p->Heads[n].row;   //row
    int co = p->Heads[n].col;  //col
    int **tmparr;    //temporary matrix variable
    tmparr = Init_Arr(r,co); 
    for (int i=0; i<r; i++){
        for(int j=0; j<co; j++){
            if(p->Heads[n].arr[i][j] ==0 ){ 
                tmparr[i][j] = 0;
            }else if(p->Heads[n].arr[i][j] >0){
                tmparr[i][j] = 1;   
            }
        }
    }

    int **tmparr2;    //copy tmparr
    tmparr2 = Init_Arr(r,co); 
    for (int i=0; i<r; i++){
        for(int j=0; j<co; j++){
            tmparr2[i][j] = tmparr[i][j];
        }
    }

    for (int i=0; i<r; i++){
        for(int j=0; j<co; j++){
            int sum = 0;  //true value number of one cell 
            if (i==0 && j==0){    //top left corner
                sum = tmparr2[i][j+1] + tmparr2[i+1][j+1] + tmparr2[i+1][j];
            }else if(i==0 && j==co-1){  //Upper right corner
                sum = tmparr2[i][j-1] + tmparr2[i+1][j-1] + tmparr2[i+1][j];
            }else if(i==0 && j>0 && j<co-1){  //First row (except corner)
                sum = tmparr2[i][j-1] + tmparr2[i+1][j-1] + tmparr2[i+1][j] + tmparr2[i+1][j+1] + tmparr2[i][j+1];
            }else if(i==r-1 && j==0){  //lower left quarter
                sum = tmparr2[i-1][j] + tmparr2[i-1][j+1] + tmparr2[i][j+1];
            }else if(i==r-1 && j==co-1){  //Lower right corner
                sum = tmparr2[i-1][j] + tmparr2[i-1][j-1] + tmparr2[i][j-1];
            }else if(i==r-1 && j>0 && j<co-1){  //Last line (except corner)
                sum = tmparr2[i][j-1] + tmparr2[i-1][j-1] + tmparr2[i-1][j] + tmparr2[i-1][j+1] + tmparr2[i][j+1];
            }else if(j==0 && i>0 && i<r-1){ //First column (except corner)
                sum = tmparr2[i-1][j] + tmparr2[i-1][j+1] + tmparr2[i][j+1] + tmparr2[i+1][j+1] + tmparr2[i+1][j];
            }else if(j==co-1 && i>0 && i<r-1){  //Last column (except corner)
                sum = tmparr2[i-1][j] + tmparr2[i-1][j-1] + tmparr2[i][j-1] + tmparr2[i+1][j-1] + tmparr2[i+1][j];
            }else{
                sum  = tmparr2[i-1][j-1] + tmparr2[i-1][j] + tmparr2[i-1][j+1] + tmparr2[i][j-1] + tmparr2[i][j+1] 
                    + tmparr2[i+1][j-1] + tmparr2[i+1][j] + tmparr2[i+1][j+1];
            }

            tmparr[i][j] = sum;
        }
    }
    Delete_Arr(tmparr2,r);

    if (p->Heads[MAXVAR-1].row != -1){
        Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
    }
    p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
    p->Heads[MAXVAR-1].row = r;
    p->Heads[MAXVAR-1].col = co;
    for(int i=0; i<r; i++){
        for (int j=0; j<co; j++){
            p->Heads[MAXVAR-1].arr[i][j] = tmparr[i][j];  //the last value of heads is temporary matrix variable 
        }
    }
    bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
    if (re == false){
        ERROR("The Stack is Full!");
    }

    Delete_Arr(tmparr,r);

}

bool Binaryop(Program *p)
{
    bool re;
    //pop 2 matrices
    int n1 = Pop(p->stack);
    int n2 = Pop(p->stack);
    if( n1==-30 || n2==-30){
        ERROR("Expecting a varialbe or ';' statement?");
    }
    int **tmparr;
    int **tmparr2;
    int num1 = -1;
    int num2 = -1;
    int r = 0;
    int co = 0;
    if (n1<0 && n2<0)   //Both are alphabetic variables
    {
        n1 = abs(n1)-1;
        n2 = abs(n2)-1;
        int r1 = p->Heads[n1].row;
        int co1 = p->Heads[n1].col;
        int r2 = p->Heads[n2].row;
        int co2 = p->Heads[n2].col;
        if (r1==1 && co1==1 && r2==1 && co2==1)  //Both matrices are 1*1 (2 numbers)
        {
            num1 = p->Heads[n1].arr[0][0];
            num2 = p->Heads[n2].arr[0][0];
            r = 1; 
            co = 1;
        }else if((r1==1 && co1==1) || (r2==1 && co2==1))  //One of the two is a 1*1 matrix (1 number)
        {
            if (r1 ==1 && co1 == 1)
            {
                num1 = p->Heads[n1].arr[0][0];
                tmparr2 = Init_Arr(r2,co2);
                for(int i=0; i<r2; i++){
                    for(int j=0; j<co2; j++){
                        tmparr2[i][j] = p->Heads[n2].arr[i][j];
                    }
                }
                r = r2;
                co = co2;
            }else if(r2 ==1 && co2 == 1)
            {
                num2 = p->Heads[n2].arr[0][0];
                tmparr = Init_Arr(r1,co1);
                for(int i=0; i<r1; i++){
                    for(int j=0; j<co1; j++){
                        tmparr[i][j] = p->Heads[n1].arr[i][j];
                    }
                }
                r = r1;
                co = co1;
            }
        }else         //Both are multiple * multiple matrices
        {
            if( r1!=r2 || co1 != co2)  //If the matrices are different, an error is reported
            {
                ERROR("Two array must be the same size!");
            }else{
                tmparr = Init_Arr(r1,co1);
                tmparr2 = Init_Arr(r1, co1);
                for(int i=0; i<r1; i++){
                    for(int j=0; j<co1; j++){
                        tmparr[i][j] = p->Heads[n1].arr[i][j];
                        tmparr2[i][j] = p->Heads[n2].arr[i][j];
                    }
                }
                r = r1;
                co = co1;
            }
        }
    }else if(n1>0 && n2>0)   //2 numbers
    {
        num1 = n1;
        num2 = n2;
        r = 1;
        co = 1;
    }else if(n1>0 || n2>0)   //one number and one letter variable
    {
        int n = 0;
        if(n1>0){
            num1 = n1;
            n = abs(n2)- 1; 
        }else if(n2 > 0){
            num2 = n2; 
            n = abs(n1) - 1;
        }
        if(p->Heads[n].row==1 && p->Heads[n].col==1)    //the other letter is the 1 * 1 matrix (number)
        {
            if(num1 == -1){
                num1 = p->Heads[n].arr[0][0];
            }else if(num2 == -1){
                num2 = p->Heads[n].arr[0][0];
            }
            r = 1;
            co = 1;
        }else        //the other letter is multi * multi matrix
        {
            r = p->Heads[n].row;
            co = p->Heads[n].col;
            if (num1 == -1){   //num1 has no value to ensure the order of 1 and 2
                tmparr = Init_Arr(r, co);
                for(int i=0; i<r; i++){
                    for(int j=0; j<co; j++){
                        tmparr[i][j] = p->Heads[n].arr[i][j];
                    }
                }
            }else if(num2 == -1){
                tmparr2 = Init_Arr(r, co);
                for(int i=0; i<r; i++){
                    for(int j=0; j<co; j++){
                        tmparr2[i][j] = p->Heads[n].arr[i][j];
                    }
                }     
            }
        }
    }


    if(strsame(p->codes[p->cw],"B-AND")){
        B_And(p,tmparr, tmparr2, num1, num2, r, co);
        re = true;
    }else if(strsame(p->codes[p->cw],"B-OR")){
        B_Or(p,tmparr, tmparr2, num1, num2, r, co);
        re = true;
    }else if(strsame(p->codes[p->cw],"B-GREATER")){
        B_Greater(p,tmparr, tmparr2, num1, num2, r, co);
        re = true;
    }else if(strsame(p->codes[p->cw],"B-LESS")){
        B_Less(p,tmparr, tmparr2, num1, num2, r, co);
        re = true;
    }else if(strsame(p->codes[p->cw],"B-ADD")){
        B_Add(p,tmparr, tmparr2, num1, num2, r, co);
        re = true;
    }else if(strsame(p->codes[p->cw],"B-TIMES")){
        B_Times(p,tmparr, tmparr2, num1, num2, r, co);
        re = true;
    }else if(strsame(p->codes[p->cw],"B-EQUALS")){
        B_Equals(p,tmparr, tmparr2, num1, num2, r, co);
        re = true;
    }else if(strsame(p->codes[p->cw],"B-SUB")){
        B_Sub(p,tmparr, tmparr2, num1, num2, r, co);
        re = true;
    }else if(strsame(p->codes[p->cw],"B-MUL")){
        B_Mul(p,tmparr, tmparr2, num1, num2, r, co);
        re = true;        
    }else{
        re = false;
    }

    return re;
}

void B_And(Program *p,int **tmparr, int **tmparr2, int num1, int num2, int r, int co)
{
    if (num1 != -1 && num2 != -1)   //2 numbers
    {
        int n=0;
        if(num1>0 && num2>0){
            n=1;
        }else if(num1==0 || num2==0){
            n=0;
        }
        bool re = Push(p->stack, n);
        if (re == false){
            ERROR("The Stack is Full!");
        }
    }else if(num1 != -1 && num2 == -1)   //1 number
    {
        if (num1 != -1)    //num1 and tmparr2 have value
        {  
            for (int i=0; i<r; i++){
                for (int j=0; j<co;j++){
                    if (num1>0 && tmparr2[i][j]>0){
                        tmparr2[i][j] = 1;
                    }else{
                        tmparr2[i][j] = 0;
                    }
                }
            }
            //put the result into heads array and release the tmparr array
            if (p->Heads[MAXVAR-1].row != -1){
                Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
            }
            p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
            p->Heads[MAXVAR-1].row = r;
            p->Heads[MAXVAR-1].col = co;
            for(int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    p->Heads[MAXVAR-1].arr[i][j] = tmparr2[i][j]; 
                }
            }
            bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
            if (re == false){ERROR("The Stack is Full!");}
            Delete_Arr(tmparr2,r);
        }else if(num2 != -1)   //tmparr and num2 have value
        {
            for (int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    if (num2>0 && tmparr[i][j]>0){
                        tmparr[i][j] = 1;
                    }else{
                        tmparr[i][j] = 0;
                    }
                }
            }
            //put the result into heads array and release the tmparr array
            if (p->Heads[MAXVAR-1].row != -1){
                Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
            }
            p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
            p->Heads[MAXVAR-1].row = r;
            p->Heads[MAXVAR-1].col = co;
            for(int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    p->Heads[MAXVAR-1].arr[i][j] = tmparr[i][j]; 
                }
            }
            bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
            if (re == false){ERROR("The Stack is Full!");}
            Delete_Arr(tmparr,r);
        }
    }else if(num1 ==-1 && num2 == -1)   //2 multi * multi matrix
    {
        for (int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                if (tmparr[i][j]>0 && tmparr2[i][j]>0){
                    tmparr[i][j] = 1;
                }else{
                    tmparr[i][j] = 0;
                }
            }
        }
        //put the result into heads array and release the tmparr array
        if (p->Heads[MAXVAR-1].row != -1){
            Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
        }
        p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
        p->Heads[MAXVAR-1].row = r;
        p->Heads[MAXVAR-1].col = co;
        for(int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                p->Heads[MAXVAR-1].arr[i][j] = tmparr[i][j];  
            }
        }
        bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
        if (re == false){ERROR("The Stack is Full!");}
        Delete_Arr(tmparr,r);
        Delete_Arr(tmparr2,r);   
    }
}

void B_Or(Program *p,int **tmparr, int **tmparr2, int num1, int num2, int r, int co)
{
    if (num1 != -1 && num2 != -1)   //2 nubmers
    {
        int n=0;
        if(num1==0 && num2==0){
            n=0;
        }else{
            n=1;
        }
        bool re = Push(p->stack, n);
        if (re == false){
            ERROR("The Stack is Full!");
        }
    }else if(num1 != -1 || num2 != -1)   //1 number
    {
        if (num1 != -1){  //num1 and tmparr2 have value
            for (int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    if (num1==0 && tmparr2[i][j]==0){
                        tmparr2[i][j] = 0;
                    }else{
                        tmparr2[i][j] = 1;
                    }
                }
            }
            //put the result into heads array and release the tmparr array
            if (p->Heads[MAXVAR-1].row != -1){
                Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
            }
            p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
            p->Heads[MAXVAR-1].row = r;
            p->Heads[MAXVAR-1].col = co;
            for(int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    p->Heads[MAXVAR-1].arr[i][j] = tmparr2[i][j]; 
                }
            }
            bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
            if (re == false){ERROR("The Stack is Full!");}
            Delete_Arr(tmparr2,r);
        }else if(num2 != -1)   //tmparr and num2 have value
        {
            for (int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    if (num2==0 && tmparr[i][j]==0){
                        tmparr[i][j] = 0;
                    }else{
                        tmparr[i][j] = 1;
                    }
                }
            }
            //put the result into heads array and release the tmparr array
            if (p->Heads[MAXVAR-1].row != -1){
                Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
            }
            p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
            p->Heads[MAXVAR-1].row = r;
            p->Heads[MAXVAR-1].col = co;
            for(int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    p->Heads[MAXVAR-1].arr[i][j] = tmparr[i][j]; 
                }
            }
            bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
            if (re == false){ERROR("The Stack is Full!");}
            Delete_Arr(tmparr,r);
        }
    }else if(num1 ==-1 && num2 == -1)   //2 multi * multi matrix
    {
        for (int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                if (tmparr[i][j]==0 && tmparr2[i][j]==0){
                    tmparr[i][j] = 0;
                }else{
                    tmparr[i][j] = 1;
                }
            }
        }
        //put the result into heads array and release the tmparr arra
        if (p->Heads[MAXVAR-1].row != -1){
            Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
        }
        p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
        p->Heads[MAXVAR-1].row = r;
        p->Heads[MAXVAR-1].col = co;
        for(int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                p->Heads[MAXVAR-1].arr[i][j] = tmparr[i][j];  
            }
        }
        bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
        if (re == false){ERROR("The Stack is Full!");}
        Delete_Arr(tmparr,r);
        Delete_Arr(tmparr2,r);   
    }
}

void B_Greater(Program *p,int **tmparr, int **tmparr2, int num1, int num2, int r, int co)
{
    if (num1 != -1 && num2 != -1)   //2 numbers
    {
        int n=0;
        //stack, last in, first out, so 1 is the next value and 2 is the previous value
        if(num1 < num2){  
            n=1;
        }else{
            n=0;
        }
        bool re = Push(p->stack, n);
        if (re == false){
            ERROR("The Stack is Full!");
        }
    }else if(num1 != -1 || num2 != -1)   //1 number
    {
        if(num1 != -1)    //num1 and tmparr2 have value
        {
            for (int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    if (num1 < tmparr2[i][j]){
                        tmparr2[i][j] = 1;
                    }else{
                        tmparr2[i][j] = 0;
                    }
                }
            }
            //put the result into heads array and release the tmparr array
            if (p->Heads[MAXVAR-1].row != -1){
                Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
            }
            p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
            p->Heads[MAXVAR-1].row = r;
            p->Heads[MAXVAR-1].col = co;
            for(int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    p->Heads[MAXVAR-1].arr[i][j] = tmparr2[i][j]; 
                }
            }
            bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
            if (re == false){ERROR("The Stack is Full!");}
            Delete_Arr(tmparr2,r);
        }else if(num2 != -1)  // tmparr and num2 have value
        {
            for (int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    if (tmparr[i][j] < num2){
                        tmparr[i][j] = 1;
                    }else{
                        tmparr[i][j] = 0;
                    }
                }
            }
            //put the result into heads array and release the tmparr array
            if (p->Heads[MAXVAR-1].row != -1){
                Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
            }
            p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
            p->Heads[MAXVAR-1].row = r;
            p->Heads[MAXVAR-1].col = co;
            for(int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    p->Heads[MAXVAR-1].arr[i][j] = tmparr[i][j]; 
                }
            }
            bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
            if (re == false){ERROR("The Stack is Full!");}
            Delete_Arr(tmparr,r);
        }

    }else if(num1 ==-1 && num2 == -1)   //2 multi * multi matrix
    {
        for (int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                if (tmparr[i][j] < tmparr2[i][j]){
                    tmparr[i][j] = 1;
                }else{
                    tmparr[i][j] = 0;
                }
            }
        }
        //put the result into heads array and release the tmparr array
        if (p->Heads[MAXVAR-1].row != -1){
            Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
        }
        p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
        p->Heads[MAXVAR-1].row = r;
        p->Heads[MAXVAR-1].col = co;
        for(int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                p->Heads[MAXVAR-1].arr[i][j] = tmparr[i][j]; 
            }
        }
        bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
        if (re == false){ERROR("The Stack is Full!");}
        Delete_Arr(tmparr,r);
        Delete_Arr(tmparr2,r);   
    }
}

void B_Less(Program *p,int **tmparr, int **tmparr2, int num1, int num2, int r, int co)
{
    if (num1 != -1 && num2 != -1)   //2 numbers
    {
        int n=0;
        //stack, last in, first out, so 1 is the next value and 2 is the previous value
        if(num1 > num2){ 
            n=1;
        }else{
            n=0;
        }
        bool re = Push(p->stack, n);
        if (re == false){
            ERROR("The Stack is Full!");
        }
    }else if(num1 != -1 || num2 != -1)   //1 number
    {
        if(num1 != -1)    //num1 and tmparr2 have value
        {
            for (int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    if (num1 > tmparr2[i][j]){
                        tmparr2[i][j] = 1;
                    }else{
                        tmparr2[i][j] = 0;
                    }
                }
            }
            //put the result into heads array and release the tmparr array
            if (p->Heads[MAXVAR-1].row != -1){
                Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
            }
            p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
            p->Heads[MAXVAR-1].row = r;
            p->Heads[MAXVAR-1].col = co;
            for(int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    p->Heads[MAXVAR-1].arr[i][j] = tmparr2[i][j]; 
                }
            }
            bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
            if (re == false){ERROR("The Stack is Full!");}
            Delete_Arr(tmparr2,r);
        }else if(num2 != -1)  // tmparr and num2 have value
        {
            for (int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    if (tmparr[i][j] >num2){
                        tmparr[i][j] = 1;
                    }else{
                        tmparr[i][j] = 0;
                    }
                }
            }
            //put the result into heads array and release the tmparr array
            if (p->Heads[MAXVAR-1].row != -1){
                Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
            }
            p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
            p->Heads[MAXVAR-1].row = r;
            p->Heads[MAXVAR-1].col = co;
            for(int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    p->Heads[MAXVAR-1].arr[i][j] = tmparr[i][j]; 
                }
            }
            bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
            if (re == false){ERROR("The Stack is Full!");}
            Delete_Arr(tmparr,r);
        }

    }else if(num1 ==-1 && num2 == -1)   //2 multi * multi matrix
    {
        for (int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                if (tmparr[i][j] > tmparr2[i][j]){
                    tmparr[i][j] = 1;
                }else{
                    tmparr[i][j] = 0;
                }
            }
        }
        //put the result into heads array and release the tmparr array
        if (p->Heads[MAXVAR-1].row != -1){
            Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
        }
        p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
        p->Heads[MAXVAR-1].row = r;
        p->Heads[MAXVAR-1].col = co;
        for(int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                p->Heads[MAXVAR-1].arr[i][j] = tmparr[i][j]; 
            }
        }
        bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
        if (re == false){ERROR("The Stack is Full!");}
        Delete_Arr(tmparr,r);
        Delete_Arr(tmparr2,r);   
    }
}

void B_Add(Program *p,int **tmparr, int **tmparr2, int num1, int num2, int r, int co)
{
    if (num1 != -1 && num2 != -1)   //2 numbers
    {
        int n=0;
        n = num1 + num2;
        bool re = Push(p->stack, n);
        if (re == false){
            ERROR("The Stack is Full!");
        }
    }else if(num1 != -1 || num2 != -1)   //1 number
    {
        if (num1 != -1){  //num1 and tmparr2 have value
            for (int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    tmparr2[i][j] = tmparr2[i][j] + num1;
                }
            }
            //put the result into heads array and release the tmparr array
            if (p->Heads[MAXVAR-1].row != -1){
                Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
            }
            p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
            p->Heads[MAXVAR-1].row = r;
            p->Heads[MAXVAR-1].col = co;
            for(int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    p->Heads[MAXVAR-1].arr[i][j] = tmparr2[i][j];  
                }
            }
            bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
            if (re == false){ERROR("The Stack is Full!");}
            Delete_Arr(tmparr2,r);
        }else if(num2 != -1)   //tmparr and num2 have value
        {
            for (int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    tmparr[i][j] = tmparr[i][j] + num2;
                }
            }
            ///put the result into heads array and release the tmparr array
            if (p->Heads[MAXVAR-1].row != -1){
                Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
            }
            p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
            p->Heads[MAXVAR-1].row = r;
            p->Heads[MAXVAR-1].col = co;
            for(int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    p->Heads[MAXVAR-1].arr[i][j] = tmparr[i][j];  
                }
            }
            bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
            if (re == false){ERROR("The Stack is Full!");}
            Delete_Arr(tmparr,r);
        }
    }else if(num1 ==-1 && num2 == -1)   //2 multi * multi matrix
    {
        for (int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                tmparr[i][j] = tmparr[i][j] + tmparr2[i][j];
            }
        }
        //put the result into heads array and release the tmparr array
        if (p->Heads[MAXVAR-1].row != -1){
            Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
        }
        p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
        p->Heads[MAXVAR-1].row = r;
        p->Heads[MAXVAR-1].col = co;
        for(int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                p->Heads[MAXVAR-1].arr[i][j] = tmparr[i][j];  
            }
        }
        bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
        if (re == false){ERROR("The Stack is Full!");}
        Delete_Arr(tmparr,r);
        Delete_Arr(tmparr2,r);   
    }
}

void B_Times(Program *p,int **tmparr, int **tmparr2, int num1, int num2, int r, int co)
{
    if (num1 != -1 && num2 != -1)   //2 numbers
    {
        int n=0;
        n = num1 * num2;
        bool re = Push(p->stack, n);
        if (re == false){
            ERROR("The Stack is Full!");
        }
    }else if(num1 != -1 || num2 != -1)   //1 number
    {
        if (num1 != -1){  //num1 and tmparr2 have value
            for (int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    tmparr2[i][j] = tmparr2[i][j] * num1;
                }
            }
            //put the result into heads array and release the tmparr array
            if (p->Heads[MAXVAR-1].row != -1){
                Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
            }
            p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
            p->Heads[MAXVAR-1].row = r;
            p->Heads[MAXVAR-1].col = co;
            for(int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    p->Heads[MAXVAR-1].arr[i][j] = tmparr2[i][j]; 
                }
            }
            bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
            if (re == false){ERROR("The Stack is Full!");}
            Delete_Arr(tmparr2,r);
        }else if(num2 != -1)   //tmparr and num2 have value
        {
            for (int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    tmparr[i][j] = tmparr[i][j] * num2;
                }
            }
            //put the result into heads array and release the tmparr array
            if (p->Heads[MAXVAR-1].row != -1){
                Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
            }
            p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
            p->Heads[MAXVAR-1].row = r;
            p->Heads[MAXVAR-1].col = co;
            for(int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    p->Heads[MAXVAR-1].arr[i][j] = tmparr[i][j]; 
                }
            }
            bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
            if (re == false){ERROR("The Stack is Full!");}
            Delete_Arr(tmparr,r);
        }
    }else if(num1 ==-1 && num2 == -1)   //2 multi * multi matrix
    {
        for (int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                tmparr[i][j] = tmparr[i][j] * tmparr2[i][j];
            }
        }
        //put the result into heads array and release the tmparr array
        if (p->Heads[MAXVAR-1].row != -1){
            Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
        }
        p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
        p->Heads[MAXVAR-1].row = r;
        p->Heads[MAXVAR-1].col = co;
        for(int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                p->Heads[MAXVAR-1].arr[i][j] = tmparr[i][j];  
            }
        }
        bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
        if (re == false){ERROR("The Stack is Full!");}
        Delete_Arr(tmparr,r);
        Delete_Arr(tmparr2,r);   
    }
}

void B_Equals(Program *p,int **tmparr, int **tmparr2, int num1, int num2, int r, int co)
{
    if (num1 != -1 && num2 != -1)   //2 numbers
    {
        if(num2 == num1){
            num1 = 1;
        }else{
            num1 = 0;
        }
        bool re = Push(p->stack, num1);
        if (re == false){
            ERROR("The Stack is Full!");
        }
    }else if(num1 != -1 || num2 != -1)   //1 number
    {
        if (num1 != -1){  //num1 and tmparr2 have value
            for (int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    if(tmparr2[i][j] == num1){
                        tmparr2[i][j] = 1;
                    }else{
                        tmparr2[i][j] = 0;
                    }
                }
            }
            //put the result into heads array and release the tmparr array
            if (p->Heads[MAXVAR-1].row != -1){
                Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
            }
            p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
            p->Heads[MAXVAR-1].row = r;
            p->Heads[MAXVAR-1].col = co;
            for(int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    p->Heads[MAXVAR-1].arr[i][j] = tmparr2[i][j];  
                }
            }
            bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
            if (re == false){ERROR("The Stack is Full!");}
            Delete_Arr(tmparr2,r);
        }else if(num2 != -1)   //tmparr and num2 have value 
        {
            for (int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    if(num2 == tmparr[i][j]){
                        num2 = 1;
                    }else{
                        num2 = 0;
                    }
                }
            }
            //put the result into heads array and release the tmparr array
            if (p->Heads[MAXVAR-1].row != -1){
                Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
            }
            p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
            p->Heads[MAXVAR-1].row = r;
            p->Heads[MAXVAR-1].col = co;
            for(int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    p->Heads[MAXVAR-1].arr[i][j] = tmparr[i][j];  
                }
            }
            bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
            if (re == false){ERROR("The Stack is Full!");}
            Delete_Arr(tmparr,r);
        }
    }else if(num1 ==-1 && num2 == -1)   //2 multi * multi matrix
    {
        for (int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                if(tmparr2[i][j] == tmparr[i][j]){
                    tmparr2[i][j] = 1;
                }else{
                    tmparr2[i][j] = 0;
                }
            }
        }
        //put the result into heads array and release the tmparr array
        if (p->Heads[MAXVAR-1].row != -1){
            Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
        }
        p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
        p->Heads[MAXVAR-1].row = r;
        p->Heads[MAXVAR-1].col = co;
        for(int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                p->Heads[MAXVAR-1].arr[i][j] = tmparr[i][j];  
            }
        }
        bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
        if (re == false){ERROR("The Stack is Full!");}
        Delete_Arr(tmparr,r);
        Delete_Arr(tmparr2,r);   
    }
}

void B_Sub(Program *p,int **tmparr, int **tmparr2, int num1, int num2, int r, int co)
{
    if (num1 != -1 && num2 != -1)   //2 numbers
    {
        int n=0;
        n = num2 - num1;
        if (n<0){
            ERROR("Can't do negative numbers operation!");
        }
        bool re = Push(p->stack, n);
        if (re == false){
            ERROR("The Stack is Full!");
        }
    }else if(num1 != -1 || num2 != -1)   //1 number
    {
        if (num1 != -1){  //num1 and tmparr2 have value
            for (int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    tmparr2[i][j] = tmparr2[i][j] - num1;
                }
            }
            //put the result into heads array and release the tmparr array
            if (p->Heads[MAXVAR-1].row != -1){
                Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
            }
            p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
            p->Heads[MAXVAR-1].row = r;
            p->Heads[MAXVAR-1].col = co;
            for(int i=0; i<r; i++){
                for (int j=0; j<co; j++){
                    p->Heads[MAXVAR-1].arr[i][j] = tmparr2[i][j];  
                }
            }
            bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
            if (re == false){ERROR("The Stack is Full!");}
            Delete_Arr(tmparr2,r);
        }else if(num2 != -1)   //tmparr and num2 have value
        {
            ERROR("A number is not allowed sub matrix!");
        }
    }else if(num1 ==-1 && num2 == -1)   //2 multi * multi matrix
    {
        for (int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                tmparr[i][j] = tmparr[i][j] - tmparr2[i][j];
            }
        }
        //put the result into heads array and release the tmparr array
        if (p->Heads[MAXVAR-1].row != -1){
            Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
        }
        p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
        p->Heads[MAXVAR-1].row = r;
        p->Heads[MAXVAR-1].col = co;
        for(int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                p->Heads[MAXVAR-1].arr[i][j] = tmparr[i][j];  
            }
        }
        bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
        if (re == false){ERROR("The Stack is Full!");}
        Delete_Arr(tmparr,r);
        Delete_Arr(tmparr2,r);   
    }
}

void B_Mul(Program *p,int **tmparr, int **tmparr2, int num1, int num2, int r, int co) 
{
    if (num1 != -1 && num2 != -1)   //2 numbers
    {
        ERROR("Only two mul*mul matrix can do 'B-MUL'!");
    }else if(num1 != -1 || num2 != -1)   //1 number
    {
        ERROR("Only two mul*mul matrix can do 'B-MUL'!");
    }else if(num1 ==-1 && num2 == -1)   //2 multi * multi matrix
    {
        if(r != co){
            ERROR("Only when the rows of the first matrix and the columns of the second matrix are the same can do 'B-MUL'!");
        }

        int **tmparr3 = Init_Arr(r,co);

        for (int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                int sum = 0;
                for (int k=0; k<co; k++){
                    sum = sum + tmparr2[i][k] * tmparr[k][j];
                }
                tmparr3[i][j] = sum;
            }
        }
        //put the result into heads array and release the tmparr array
        if (p->Heads[MAXVAR-1].row != -1){
            Delete_Arr(p->Heads[MAXVAR-1].arr,p->Heads[MAXVAR-1].row);
        }
        p->Heads[MAXVAR-1].arr = Init_Arr(r,co);
        p->Heads[MAXVAR-1].row = r;
        p->Heads[MAXVAR-1].col = co;
        for(int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                p->Heads[MAXVAR-1].arr[i][j] = tmparr3[i][j];  
            }
        }
        bool re = Push(p->stack,-MAXVAR);  //-1-(MAXVAR-1) 
        if (re == false){ERROR("The Stack is Full!");}
        Delete_Arr(tmparr,r);
        Delete_Arr(tmparr2,r);
        Delete_Arr(tmparr3,r);
    }
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
    int r=0;   //row
    int co=0;  //cols
    char c;    //var name
    if(Interger(p)){
        r = atoi(p->codes[p->cw]);
        p->cw = p->cw+1;
    }else{
        ERROR("Expecting an interger of row?");
    }

    if(Interger(p)){
        co = atoi(p->codes[p->cw]);
        p->cw = p->cw+1;
    }else{
        ERROR("Expecting an interger of column?");
    }

    if(Varname(p)){
        c = p->codes[p->cw][1];
    }else{
        ERROR("Expecting a Variable?");
    }

    //Put the matrix into the heads array
    int n = 0;
    n = c - 'A';
    p->Heads[n].row = r;
    p->Heads[n].col = co;
    p->Heads[n].arr = Init_Arr(r,co);

    for (int i=0; i<r; i++){
        for (int j=0; j<co; j++){
            p->Heads[n].arr[i][j] = 1;
        }
    }

}

void Array_Read(Program *p)
{
    int len=0;
    //Check whether the filename is a string
    if(p->codes[p->cw][0] == '\"'){
        len = strlen(p->codes[p->cw]);
        if(p->codes[p->cw][len-1] != '\"'){
            ERROR("Expecting a '\"' statement?");
        }
    }else{
        ERROR("Expecting a \'\"\' statement?");
    }

    //filename Remove double quotes
    char filename[MAXTOKENSIZE];
    int j=0;
    for(int i=1; i<len-1;i++){
        filename[j] = p->codes[p->cw][i];
        j++;
    }
    filename[j] = '\0';

    FILE *f;
    if((f = fopen(filename,"r")) == NULL){
        ERROR("No file?");
    }

    p->cw = p->cw+1;
    if (Varname(p))  //Read the file and put the matrix into the corresponding variable
    {
        f = fopen(filename,"r");    //Open the file that needs to read the matrix

        char c = p->codes[p->cw][1];
        int r=0, co=0;
        fscanf(f, "%d %d\n", &r, &co);
        int n=c-'A';
        p->Heads[n].row = r;
        p->Heads[n].col = co;
        p->Heads[n].arr = Init_Arr(r,co);   //malloc
        int num=0;
        for (int i=0; i<r; i++){
            for (int j=0; j<co; j++){
                fscanf(f, "%d", &num); 
                p->Heads[n].arr[i][j] = num;
            }
        }

        fclose(f);
    }else{
        ERROR("Expecting a Variable?")
    }
}

void Loop(Program *p)
{
    char c;
    int n=0;
    int loopnum =0 ;
    //Set the variable to a matrix of 1 * 1 and set its value to 1
    if(Varname(p))   
    {
        c = p->codes[p->cw][1];
        n = c-'A';
        //If it has been used before, release it first
        if (p->Heads[n].row != -1 && p->Heads[n].row != -1){
            Delete_Arr(p->Heads[n].arr, p->Heads[n].row);
        }
        p->Heads[n].row = 1;
        p->Heads[n].col = 1;
        p->Heads[n].arr = Init_Arr(1,1); 
        p->Heads[n].arr[0][0] = 1;
        p->cw = p->cw+1;
    }else{
        ERROR("Expecting a Variable?");
    }

    if(Interger(p)){
        loopnum = atoi(p->codes[p->cw]);
        p->cw = p->cw+1;
    }else{
        ERROR("Expecting an Interger?");
    }

    if(strsame(p->codes[p->cw],"{")){
        p->cw = p->cw+1;
    }else{
        ERROR("Expecting a \'{\' statement?");
    }

    int lp = p->cw;  //Record the position where the initial loop begins
    for (p->Heads[n].arr[0][0] = 1; p->Heads[n].arr[0][0] <= loopnum; p->Heads[n].arr[0][0]++){
        p->cw = lp;
        Instrclist(p);
    }

}

void Save(Program *p)
{
    int len=0;
    //Check whether the filename is a string
    if(p->codes[p->cw][0] == '\"'){
        len = strlen(p->codes[p->cw]);
        if(p->codes[p->cw][len-1] != '\"'){
            ERROR("Expecting a '\"' statement?");
        }
    }else{
        ERROR("Expecting a filename?");
    }

    //filename Remove double quotes
    char filename[MAXTOKENSIZE];
    int j=0;
    for(int i=1; i<len-1;i++){
        filename[j] = p->codes[p->cw][i];
        j++;
    }
    filename[j] = '\0';

    p->cw = p->cw+1; 
    FILE *f;
    f=fopen(filename,"w");

    if (Varname(p)){
        char c = p->codes[p->cw][1];
        int n = c-'A';
        int r = p->Heads[n].row;
        int co = p->Heads[n].col;
        if (r == -1 && co == -1){
            ERROR("Variable no value!");
        }
        fprintf(f,"%d %d\n", r, co);
        for (int i=0; i<r; i++){
            for (int k=0; k<co; k++){
                fprintf(f,"%d ", p->Heads[n].arr[i][k]);
            }
            fprintf(f, "\n");
        }
    }else if(Interger(p)){
        int n = atoi(p->codes[p->cw]);
        fprintf(f,"%d", n);
    }else if(String(p)){
        char content[MAXTOKENSIZE];
        int l = strlen(p->codes[p->cw]);
        int n=0;
        for(int m=1; m<l-1;m++){
            content[n] = p->codes[p->cw][m];
            n++;
        }
        content[n] = '\0';
        fprintf(f,"%s", content);
    }else{
        ERROR("Expecting a TYPE?");
    }
    fclose(f);
}

bool String(Program *p)
{
    int len=0;
    //Check whether the filename is a string
    if(p->codes[p->cw][0] == '\"'){
        len = strlen(p->codes[p->cw]);
        if(p->codes[p->cw][len-1] != '\"'){
            return false;
        }
    }else{
        return false;
    }
    return true;
}


bool IsFull(stackvar *stack)
{
    return (stack->top == MAXVAR-1);
}

bool IsEmpty(stackvar *stack)
{
    return (stack->top == -1);
}

bool Push(stackvar *stack, int x)
{
    if ( IsFull(stack) ) {
        return false;
    }
    else {
        stack->top++;
        stack->var[stack->top] = x;
        return true;
    }
}

int Pop(stackvar *stack)
{
    if ( IsEmpty(stack) ){
        return -30;   //-30 special value, error flag
    }
    else{
        return ( stack->var[(stack->top)--] );
    }
}

int** Init_Arr(int row, int col)
{
    int **arr;
    arr = (int **)malloc(row*sizeof(int*));
    for(int i=0; i<row; i++){
        arr[i] = (int *)malloc(col*sizeof(int));
    }
    return arr;
}

void Delete_Arr(int **arr, int row)
{
    for(int i=0; i<row; i++){
        free(arr[i]);
    }
    free(arr);
}

