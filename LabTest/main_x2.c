/*
   Tests whether string s1 contains alphabetical
   characters which are ordered i.e. the next letter
   is alphabetically >= to the current one. All non-letters
   (e.g. spaces, punctuation etc.) are ignored..
*/

#include "common.h"

bool strsorted(const char* s1);

int main(void)
{

   assert(strsorted("abc"));
   assert(strsorted("AbC"));
   assert(strsorted("AAA"));
   assert(strsorted("A-AZ-"));
   assert(strsorted("a m z !"));

   assert(!strsorted("cba"));
   assert(!strsorted("CbA"));
   assert(!strsorted("!Cb *A!"));

   return 0;
}
