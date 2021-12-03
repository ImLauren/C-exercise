#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define BIGSTR 1000
#define GRID 100

struct crossword{
   char arr[GRID][GRID];
   int sz;
}; 
typedef struct crossword crossword; 

bool str2crossword(int sz, char* ip, crossword* cw);
void getcluestring(const crossword* c, char* str);
int getchecked(crossword c);
void test(void);

int main(void){
    crossword c;
    char str[BIGSTR];
    str2crossword(8, ".....X.XX.X.X..........XX.X.X......X.X.XX..........X.X.XX.X.....", &c);
    getcluestring(&c,str);
    getchecked(c);

    test();
    return 0;
}

bool str2crossword(int sz, char* ip, crossword* cw) 
{
    //未传入字符串或cw
    if(ip==0 || cw==0){
        return false;
    }
    //传入字符串数量不符合sz*sz大小
    if(strlen(ip) != sz*sz){
        return false;
    }
    //传入size过大或过小
    if(sz>100 || sz<=0){
        return false;
    }

    cw->sz=sz;
    int count=0;
    for(int i=0;i<cw->sz;i++){
        for(int j=0;j<cw->sz;j++){
            cw->arr[i][j]=* (ip+count);
            count ++;
        }
    }


    for(int y=0; y<cw->sz; y++){
        for(int x=0; x<cw->sz; x++){
            printf("%c", cw->arr[y][x]);
        }
        printf("\n");
    }

    for(int i=0;i<cw->sz;i++){
        for(int j=0;j<cw->sz;j++){
            if(cw->arr[i][j]==' ' || cw->arr[i][j]=='.'){
                cw->arr[i][j] = 1;
            }else if(cw->arr[i][j]=='*' || cw->arr[i][j]=='X'){
                cw->arr[i][j] = 0;
            }
        }
    }


    return true;
}

void getcluestring(const crossword* c,char* str){
    int A[50]={0},D[50]={0}; //储存横或竖的数字，有为1，无为0
    int cnt=0; 

    //遍历数组，计算行列标号及每个格子用的次数
    for(int i=0; i<c->sz;i++)
    {
        for (int j=0;j<c->sz;j++)
        {
            if(i==0)
            {
                if(c->arr[i][j]==1 && c->arr[i+1][j]==1) //第一行，数列上边不用判断 D情况
                {
                    D[cnt] = 1;
                }
                if(j!=0 && c->arr[i][j] == 1 && c->arr[i][j-1] == 0 && c->arr[i][j+1] == 1) //第一行除0.0，A情况
                {
                    A[cnt] = 1;
                }
            } 

            if(j==0){
                if(c->arr[i][j]==1 && c->arr[i][j+1]==1)  //第一列，左边不用判断 A情况
                {
                    A[cnt] = 1;
                }
                if(i!=0 && c->arr[i][j] == 1 && c->arr[i-1][j] == 0 && c->arr[i+1][j] == 1) //第一列除0.0，D情况
                {
                    D[cnt]=1;
                }
            }

            //除第一行和第一列的其他情况
            if(i!=0 && j!=0)
            {    
                if(c->arr[i][j] == 1 && c->arr[i][j-1] == 0 && c->arr[i][j+1] == 1) //如果空格为'.'，且左边的空格为X，则横A可计数
                {
                    A[cnt]=1;
                }
                if(c->arr[i][j] == 1 && c->arr[i-1][j] == 0 && c->arr[i+1][j] == 1) //如果空格为'.'，且上边的空格为X，则竖D可计数
                {
                    D[cnt]=1;
                }
            }
        
            //如果A或者D数组中，有1个或2个被计数，则进入下一个count
            if(A[cnt]==1 || D[cnt]==1)
            {
                cnt++;
            }
        }
    }

    for(int i=0; i<15;i++){
        printf("A[%d]=%d ",i,A[i]);
    }
    printf("\n");
    for(int i=0; i<15;i++){
        printf("D[%d]=%d ",i,D[i]);
    }
    printf("\n");

    //将计算好的标号用str保存
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
                sprintf(tmp,"%d",1);
                str[k] = *tmp;
                k++;
                sprintf(tmp,"%d",i-9);
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
    for(int i=0;i<cnt;i++){
        if(D[i]==1)
        {
            sprintf(tmp,"%c",'-');
            str[k] = *tmp;
            k++;
            if(i+1>=10){
                sprintf(tmp,"%d",1);
                str[k] = *tmp;
                k++;
                sprintf(tmp,"%d",i-9);
                str[k] = *tmp;
                k++;
            }else{
                sprintf(tmp,"%d",i+1);
                str[k] = *tmp;
                k++;
            }
        }
    }
    sprintf(tmp,"%c",'\0');
    str[k] = *tmp;

    printf("%s\n",str);
}

int getchecked(crossword c){
    int count[100][100]={0}; //创建数组保存每个格子用的次数
    //将count数组用0 1 2使用次数填满
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

    //计算重复使用的格子及空格格子
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

    printf("getcheckd = %d\n",check);

    return check;

}

void test(void)
{
    char str[BIGSTR];
    crossword c;

    assert(!str2crossword(0, NULL, &c));
    assert(!str2crossword(2, "...x.x...", NULL));

    assert(str2crossword(3, "X.X...X.X", &c));
    getcluestring(&c, str);
    assert(strcmp("A-2|D-1", str)==0);
    assert(getchecked(c)==20);

}
