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

/*
For your own testing - you'll probably have many auxiliary/sub-functions
inside crossword.c that you'll want to test ... 
对于您自己的测试，您可能会有许多辅助/子功能
在crossword.c中，您将要测试它。。。
*/
void test(void);

/*
   Convert a size (sz) & string (ip) into a crossword*
   White squares are ' ' or '.', black squares 'X' or '*'
   将大小（sz）和字符串（ip）转换为纵横字谜*
   白色方块为“ ”或“.”，黑色方块为“X”或“*”
*/
bool str2crossword(int sz, char* ip, crossword* cw);

// Convert crossword to string of across & down numbers   转换为字符串
void getcluestring(const crossword* c, char* str);

// Get percentage of empty squares that are shared between two clues  获取两条线索之间共享的空方块百分比
int getchecked(crossword c);
