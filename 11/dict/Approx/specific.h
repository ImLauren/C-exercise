#include "../dict.h"


struct dict{
    unsigned long Table_Size;    //size of Bloom Filter
    unsigned long *list;     //BF list
    unsigned long *hash_function;  //store key value
};

//hash function
unsigned long* _hashes(dict* x, const char* s);    //bool value array
unsigned long _hash(dict* x, const char* s);       //hash function

//test function (not in main function)
void test(void);
