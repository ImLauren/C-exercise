#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#define ERROR(PHRASE) { fprintf(stderr, \
        "Fatal Error: %s occured in %s, line %d\n", \
        PHRASE, __FILE__, __LINE__); exit(EXIT_FAILURE); }

#define MAXNUMTOKENS 100    //max number of code
#define MAXTOKENSIZE 50     //max number of token 
#define MAXVAR 27           //max varriable: 26 uppercase (upper-case) variables + a temporary variable


struct prog{
    char codes[MAXNUMTOKENS][MAXTOKENSIZE];
    int cw;       // Current Code
    int varnum;   //store left value of SET function 
    struct varval* Heads;   ///ponit array to store matrix or number
    struct stackvar* stack;  //srack
};
typedef struct prog Program;

//Establish a structure to store matrices: 26 uppercase (upper-case) variables + a temporary variable
struct varval{
    int row;
    int col;
    int** arr;
};
typedef struct varval varval;

//Establish a stack structure to store the operation matrix
struct stackvar{
    int var[MAXVAR];  //A-Z:-1~-26; temporary variable:-27; number is positive interger
    int top;
};
typedef struct stackvar stackvar;


bool strsame(char *s, const char *pr);  //compare string is same or not
void Prog(Program *p); 
void Instrclist(Program *p);
void Instrc(Program *p);

void Print(Program *p);
bool Varname(Program *p);    //whether string conforms to the form of vername
void Print_Varname(Program *p); 
void Print_String(Program *p); 

void Set(Program *p);
void Polishlist(Program *p);
void Polish(Program *p);
bool Pushdown(Program *p); 
bool Interger(Program *p); //whether number is A non-negative integer
bool Unaryop(Program *p);   
void U_Eightcount(Program *p);  
bool Binaryop(Program *p);
void B_And(Program *p,int **tmparr, int **tmparr2, int num1, int num2, int r, int co);
void B_Or(Program *p,int **tmparr, int **tmparr2, int num1, int num2, int r, int co);
void B_Greater(Program *p,int **tmparr, int **tmparr2, int num1, int num2, int r, int co);
void B_Less(Program *p,int **tmparr, int **tmparr2, int num1, int num2, int r, int co);
void B_Add(Program *p,int **tmparr, int **tmparr2, int num1, int num2, int r, int co);
void B_Times(Program *p,int **tmparr, int **tmparr2, int num1, int num2, int r, int co);
void B_Equals(Program *p,int **tmparr, int **tmparr2, int num1, int num2, int r, int co);

void Create(Program *p);
void Array_Ones(Program *p);   
void Array_Read(Program *p);   

void Loop(Program *p);

bool IsFull(stackvar *stack); //whether stack is full
bool IsEmpty(stackvar *stack); //whether stack is empty
bool Push(stackvar *stack, int x);   //push a number to the stack
int Pop(stackvar *stack);  //pop a number
int** Init_Arr(int row, int col); //2*2 array malloc space
void Delete_Arr(int **arr, int row);  //free 2*2 array

bool test_file(char filename[MAXTOKENSIZE]);

