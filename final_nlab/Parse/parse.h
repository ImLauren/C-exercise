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


struct prog{
    char codes[MAXNUMTOKENS][MAXTOKENSIZE];
    int cw;  // Current Code
};
typedef struct prog Program;


bool strsame(char *s, const char *pr);  //compare string is same or not
void Prog(Program *p);  
void Instrclist(Program *p);
void Instrc(Program *p);

void Print(Program *p);
bool Varname(Program *p);    //whether string conforms to the form of vername
void Print_String(Program *p);  

void Set(Program *p);
void Polishlist(Program *p);
void Polish(Program *p);
bool Interger(Program *p);  //whether number is A non-negative integer
bool Pushdown(Program *p);
bool Unaryop(Program *p);
bool Binaryop(Program *p);

void Create(Program *p);
void Array_Ones(Program *p);   
void Array_Read(Program *p);   

void Loop(Program *p);

void test_single_function(void);
bool test_file(char filename[MAXTOKENSIZE]);

