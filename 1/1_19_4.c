#include <stdio.h>
#include <assert.h>

// Argument 1 is temperature 
// Argument 2 is scale (0=>Celsius, 1=>Farenheit)
int fvr(double t, int s);

int main(void)
{
   assert(fvr(37.5, 0)==1);
   assert(fvr(36.5, 0)==0);
   assert(fvr(96.5, 1)==0);
   assert(fvr(99.5, 1)==1);
   return 0;
}

int fvr(double t, int s)
{
   int re;
   if (s == 0){
      if (t >= 37.5){
         re = 1;
      }else{
         re = 0;
      }
   }else if (s == 1){
      if (t >= 99.5){
         re =1;
      }else{
         re = 0;
   }
   }

   return re;
}