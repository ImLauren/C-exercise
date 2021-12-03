#include "crossword.h"

// Might be useful to be able to print them
// to hep with debugging
void print_crossword(const crossword* c)
{
   for(int y=0; y<c->sz; y++){
      for(int x=0; x<c->sz; x++){
         printf("%c", c->arr[y][x]);
      }
      printf("\n");
   }
}

bool str2crossword(int sz, char* ip, crossword* cw)
{
   //ip or cw is empty
   if(ip==0 || cw==0)
   {
      return false;
   }
   //the number of ip does not fit sz*sz
   int len=strlen(ip);
   if(len != sz*sz)
   {
      return false;
   }
   //sz is too large or too small
   if(sz>100 || sz<=0)
   {
      return false;
   }
   
    
   //put ip into the array in cw
   cw->sz=sz;
   int count=0;
   for(int i=0;i<cw->sz;i++)
   {
      for(int j=0;j<cw->sz;j++)
      {
         cw->arr[i][j]=* (ip+count);
         count ++;
      }
   }
    
   //If "" and "." are entered, replace with 1; If you enter "*" and "X", replace with 0
   for(int i=0;i<cw->sz;i++)
   {
      for(int j=0;j<cw->sz;j++)
      {
         if(cw->arr[i][j]==' ' || cw->arr[i][j]=='.')
         {
            cw->arr[i][j] = 1;
         }else if(cw->arr[i][j]=='*' || cw->arr[i][j]=='X')
         {
            cw->arr[i][j] = 0;
         }
      }
   }

   return true;
}


int getchecked(crossword c)
{
   int count[100][100]; //reserve the number used of each space
   memset(count,0,sizeof(count)); //Initialize to 0

   //Fill the count array with 0, 1, 2 usage times
   for(int i=0; i<c.sz;i++)
   {
      for (int j=0;j<c.sz;j++)
      {
         if(c.arr[i][j] == 1 && c.arr[i][j-1] == 0 && c.arr[i][j+1] == 1)
         {
            int k=j;
            while(c.arr[i][k] == 1)
            {
               count[i][k]++;
               k++;
            }
         }
         if(c.arr[i][j] == 1 && c.arr[i-1][j] == 0 && c.arr[i+1][j] == 1)
         {
            int k=i;
            while(c.arr[k][j] == 1)
            {
               count[k][j]++;
               k++;
            }
         }
      }
   }

   //Calculate the checked space
   int cover = 0;
   int blank = 0;
   int check;
   for (int i=0;i<c.sz;i++){
      for(int j=0;j<c.sz;j++){
         if (count[i][j]>0){
            blank++;
         }
         if(count[i][j]>1){
            cover++;
         }
      }
   }

   double cv=cover;
   double ba=blank;
   check = 100 * cv / ba + 0.5;

   return check;
}

void getcluestring(const crossword* c, char* str)
{
   int A[100]={0},D[100]={0}; //Store across or down numbers, with 1 for any and 0 for none
   int cnt=0; 

   //Traverse the array, calculate the row and column labels and the number of times each space is used
   for(int i=0; i<c->sz;i++)
   {
      for (int j=0;j<c->sz;j++)
      {
         if(i==0)
         {
            if(c->arr[i][j]==1 && c->arr[i+1][j]==1) //first row, D situation
            {
               D[cnt] = 1;
            }
            if(j!=0 && c->arr[i][j] == 1 && c->arr[i][j-1] == 0 && c->arr[i][j+1] == 1) //except(0,0), first row, A situaion
            {
               A[cnt] = 1;
            }
         } 

         if(j==0)
         {
            if(c->arr[i][j]==1 && c->arr[i][j+1]==1)  //First column, A situation
            {
               A[cnt] = 1;
            }
            if(i!=0 && c->arr[i][j] == 1 && c->arr[i-1][j] == 0 && c->arr[i+1][j] == 1) //except(0,0), first column, D situaion
            {
               D[cnt]=1;
            }
         }

         //other situation except first row and first column
         if(i!=0 && j!=0)
         { 
            if(c->arr[i][j] == 1 && c->arr[i][j-1] == 0 && c->arr[i][j+1] == 1)  //the space is 1 and left is 0, count A 
            {
               A[cnt]=1;
            }
            if(c->arr[i][j] == 1 && c->arr[i-1][j] == 0 && c->arr[i+1][j] == 1)  //the space is 1 and above is 0, count D
            {
               D[cnt]=1;
            }
         }
        
         //If A or D arrays are counted, the next count will be entered
         if(A[cnt]==1 || D[cnt]==1)
         {
            cnt++;
         }
      }
   }


   //Save the calculated label with str
   char tmp[100];
   sprintf(tmp,"%c",'A');
   str[0] = *tmp;
   int k=1;

   for(int i=0;i<cnt;i++)
   {
      if(A[i]==1)
      {
         sprintf(tmp,"%c",'-');
         str[k] = *tmp;
         k++;
         if(i+1>=10)
         {
            sprintf(tmp,"%d",(i+1)/10);
            str[k] = *tmp;
            k++;
            sprintf(tmp,"%d",(i+1)%10);
            str[k] = *tmp;
            k++;
         }else{
            sprintf(tmp,"%d",i+1);
            str[k] = *tmp;
            k++;
         }
      }
   }

   sprintf(tmp,"%c",'|');
   str[k] = *tmp;
   k++;
   sprintf(tmp,"%c",'D');
   str[k] = *tmp;
   k++;
   for(int i=0;i<cnt;i++)
   {
      if(D[i]==1)
      {
         sprintf(tmp,"%c",'-');
         str[k] = *tmp;
         k++;
         if(i+1>=10)
         {
            sprintf(tmp,"%d",1);
            str[k] = *tmp;
            k++;
            sprintf(tmp,"%d",i-9);
            str[k] = *tmp;
            k++;
         }else
         {
            sprintf(tmp,"%d",i+1);
            str[k] = *tmp;
            k++;
         }
      }
   }
   sprintf(tmp,"%c",'\0');
   str[k] = *tmp;

}

void test(void)
{
   char str[BIGSTR];
   crossword c;

   assert(!str2crossword(0, NULL, &c));
   assert(!str2crossword(2, "...x.x...", NULL));
   assert(!str2crossword(3, "...x.x", &c));

   //one situaion
   assert(str2crossword(3, "X.X...X.X", &c));
   getcluestring(&c, str);
   assert(strcmp("A-2|D-1", str)==0);
   assert(getchecked(c)==20);

   //enter ' ', '*', '.' and 'X'
   assert(str2crossword(5, "..  X.XX.X.X......*.X*...", &c));
   getcluestring(&c, str);
   assert(strcmp("A-1-3-5-6|D-1-2-3-4", str)==0);
   assert(getchecked(c)==53);

}
