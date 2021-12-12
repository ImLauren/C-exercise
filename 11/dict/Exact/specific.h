#include "../dict.h"

#define BIGS 1000


//struct of Separate Chaining
typedef char Word[BIGS];  //BIGSTR=1000   max length of key char
struct Node {
    Word Word;  // word
    struct Node* Next;  // next node
};
typedef struct Node Node;

struct dict{
    int Table_Size;    //size of hash table
    Node* Heads;         //the heads of hash table
};


//Hash function
int Hash(dict* x, const char* s);

//test fuction  (not in main function) 
void test(void);
