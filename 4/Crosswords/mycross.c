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
}; //创建crossword结构体，包含字符类型arr数组，和int类型sz大小
typedef struct crossword crossword; //定义结构变量 第二个‘crossword’为名称，类型为此前定义的‘crossword’

void test(void);
bool str2crossword(int sz, char* ip, crossword* cw);
// Convert crossword to string of across & down numbers   转换为字符串
void getcluestring(const crossword* c, char* str);
// Get percentage of empty squares that are shared between two clues  获取两条线索之间共享的空方块百分比
int getchecked(crossword c);
void test(void);

int main(void){

    reutrn 0;
}

/*
   Convert a size (sz) & string (ip) into a crossword*
   White squares are ' ' or 1, black squares 0 or '*'
   将大小（sz）和字符串（ip）转换为纵横字谜*
   白色方块为“ ”或“.”，黑色方块为“X”或“*”
*/
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
    
    //将ip字符串传给cw中的二维数组
    cw->sz=sz;
    int count=0;
    for(int i=0;i<cw->sz;i++){
        for(int j=0;j<cw->sz;j++){
            cw->arr[i][j]=* (ip+count);
            count ++;
        }
    }
    
    //若输入的为“ ”和“.”，换成1;若输入为“*”和“X”，替换为0
    for(int i=0;i<cw->sz;i++){
        for(int j=0;j<cw->sz;j++){
            if(cw->arr[i][j]==' ' || cw->arr[i][j]==1){
                cw->arr[i][j] = 1;
            }else if(cw->arr[i][j]=='*' || cw->arr[i][j]==0){
                cw->arr[i][j] = 0;
            }
        }
    }

    return true;
}

void getcluestring(const crossword* c, char* str){
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

            if(j==0)
            {
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

            //如果A或者D数组中，有1个或2个被计数，则进入下一个cnt
            if(A[cnt]==1 || D[cnt]==1)
            {
                cnt++;
            }
        }
    }

    //将计算好的标号用str保存
    char tmp[100];
    str[0] = 'A';
    int k=1;

    for(int i=0;i<cnt;i++)
    {
        if(A[i]==1)
        {
            str[k] = '-';
            k++;
            sprintf(tmp,"%d",i+1);
            str[k] = *tmp;
            k++;
        }
    }

    str[k] = '|';
    k++;
    str[k] = 'D';
    k++;
    for(int i=0;i<cnt;i++){
        if(D[i]==1)
        {
            str[k] = '-';
            k++;
            if(i+1>=10){
                str[k] = '1';
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
    assert(getchecked(c)==25);

}
