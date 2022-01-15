#include "specific.h"
#define Hash_Number 33    //hash function number
#define Init_Number 5381  //hash initial number


/* The maximum number of words we will want to input. 
   Exact : Hashtable will be twice this size     
*/
dict* dict_init(unsigned int maxwords){
    unsigned int Exact_Number = maxwords * 2;    //exact number of hash table

    dict* dic;
    dic = (dict*)malloc(sizeof(dict));
    dic->Table_Size = Exact_Number;  

    //array of heads
    dic->Heads = (Node*)malloc(dic->Table_Size*sizeof(Node));
    //initialize heads
    for(int i=0; i<dic->Table_Size; i++ ) {
        dic->Heads[i].Word[0] = '\0';
        dic->Heads[i].Next = NULL;
    }

    return dic;
}

/* Add string to dictionary
   Exact : A deep-copy is stored in the hashtable only if the wordint
           has not already been added to the table.
*/
bool dict_add(dict* x,  const char* s)
{
    if (x == NULL){
        return false;
    }

    bool find;
    Node* New_Node;   //new node
    int key;
    find = dict_spelling(x,s);

    if( !find )
    {
        New_Node = (Node*)malloc(sizeof(Node));

        //Do not calculate punctuation
        char str[BIGS];
        char c;
        int i=0;
        while( (c = *s++)){
            if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
                str[i] = c;
                i++;
            }
        }
        str[i] = '\0';

        key = Hash(x,str);
        strcpy(New_Node->Word,str);
        New_Node->Next = x->Heads[key].Next;  //insert New_Node as the first node if list[key]
        x->Heads[key].Next = New_Node; 
    }
    return true;
    
}

/* Returns true if the word is already in the dictionary,
   false otherwise. 
*/
bool dict_spelling(dict* x, const char* s)
{
    if (x == NULL){
        return false;
    }

    Node* P;
    int key;
    
    key = Hash(x,s);   //Hash key value - initial list position
    P = x->Heads[key].Next; 

    //Do not calculate punctuation
    char str[10000];
    char c;
    int i=0;
    while( (c = *s++)){
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
            str[i] = c;
            i++;
        }
    }
    str[i] = '\0';

    // not in the end of list OR not find s 
    while( P!=NULL && strcmp(P->Word, str) ){
        P = P->Next;
    }
    //now P- position of word OR NULL 

    if( P == NULL){
        return false;
    }else{
        return true;
    }
}



/* Frees all space used */
void dict_free(dict* x)
{
    Node* P;
    Node* Tmp;
    
    //free nodes of link 
    for(int i=0; i<x->Table_Size; i++ ) {
        P = x->Heads[i].Next;
        while( P ) {
            Tmp = P->Next;
            free( P );
            P = Tmp;
        }
    }
    free( x->Heads ); //free head node
    free( x );        //free hash table
}


//hash function, return key value
int Hash(dict* x, const char* s)
{
    if (x == NULL){
        exit(EXIT_FAILURE);
    }

    unsigned long hash = Init_Number;
    unsigned int c;
    int sz = x->Table_Size;

    //Do not calculate punctuation
    while((c = (*s ++))){
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
            hash = Hash_Number * hash ^ c;
        }
    }

    int re = (int) hash % sz;
    re = abs(re);
    return re;
}


//test function (not in main function)
void test(void)
{

    assert(!Hash(NULL,"a"));
    assert(!Hash(NULL,"word"));

    dict* d = dict_init(50);

    assert(Hash(d,"a")==4);
    assert(Hash(d,"a,")==4);
    assert(Hash(d,"word")==63);
    assert(Hash(d,"word.")==63);
    assert(Hash(d,"boort")==33);
    assert(Hash(d,"\"boort")==33);
    
    assert(dict_add(d, "word"));
    assert(dict_add(d, "boort"));
    
    assert(dict_spelling(d, "\"word\""));
    assert(dict_spelling(d, "boort,"));

    dict_free(d);
}

