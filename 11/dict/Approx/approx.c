#include "specific.h"

#define KHASHES 11  //number of hash function
#define Hash_Number 33    //hash function number
#define Init_Number 5381  //hash initial number


/* The maximum number of words we will want to input.
   Approx : Hashtable will be (e.g.) 20 times this size
*/
dict* dict_init(unsigned int maxwords)
{
    unsigned int Approx_Number = maxwords * 20;    //approx number of Bloom Filter

    dict* dic;
    dic = (dict*)malloc(sizeof(dict));
    dic->Table_Size = (unsigned long) Approx_Number;

    //array of BF
    dic->list = (unsigned long*)malloc(dic->Table_Size * sizeof(unsigned long));
    //array of key value
    dic->hash_function = (unsigned long*)malloc(KHASHES * sizeof(unsigned long));

    //initialize
    for (unsigned long i=0; i<dic->Table_Size;i++){
        dic->list[i] = 0;
    }

    for(unsigned long i=0; i<KHASHES; i++){
        dic->hash_function[i] = 0;
    }

    return dic;

}

/* Add string to dictionary
   Approx : Multiple hashes (e.g. 11) are computed and corresponding
            Boolean flags set in the Bloom hashtable. 
*/
bool dict_add(dict* x,  const char* s)
{
    if (x == NULL){
        return false;
    }

    bool Find_Word;
    Find_Word = dict_spelling(x,s);

    if (Find_Word == false){
        for (int i=0; i<KHASHES; i++){
            x->list[x->hash_function[i]] = 1;
        }
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

    unsigned long* hashes;
    hashes = _hashes(x, s);

    bool Find_Word = true;   //assume that word is in the list
    for (unsigned long i=0; i<KHASHES && Find_Word==true; i++){
        if(x->list[hashes[i]] == 0){
            Find_Word = false;
        }
    }

    if(Find_Word == false){
        for (int i=0; i<KHASHES; i++){
            x->hash_function[i] = hashes[i];
        }  
    }

    free(hashes);

    return Find_Word;
}

/* Frees all space used */
void dict_free(dict* x)
{
    free(x->list);
    free(x->hash_function);
    free(x);
}


unsigned long* _hashes(dict* x, const char* s)
{
    if (x == NULL){
        exit(EXIT_FAILURE);
    }

    // You’ll need to free this later
    unsigned long* hashes = ncalloc(KHASHES, sizeof(unsigned long));

    // Use Bernstein from Lecture Notes (or other suitable hash)
    unsigned long bh = _hash(x, s);
    int ln = strlen(s);
    int end = ln-1;

    /* If two different strings have the same bh, then
    we need a separate way to distiguish them when using
    bh to generate a sequence */
    srand(bh*(ln*s[0] + s[end]));
    unsigned long h2 = bh;
    unsigned long sz = x->Table_Size;
    for (int i=0; i<KHASHES; i++) {
        h2 = Hash_Number * h2 ^ rand();
        hashes[i] = h2 % sz;
    }
    
    return hashes;
}


unsigned long _hash(dict* x, const char* s)
{
    if (x == NULL){
        exit(EXIT_FAILURE);
    }

    unsigned long hash = Init_Number;
    unsigned int c;
    int sz = x->Table_Size;
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
    assert(!_hash(NULL,"a"));
    assert(!_hash(NULL,"word"));

    assert(!_hashes(NULL,"abc"));
    assert(!_hashes(NULL,"words"));

    dict* d = dict_init(50);

    assert(_hash(d,"a")==604);
    assert(_hash(d,"boort")==233);

    dict_free(d);
}

