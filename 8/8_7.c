#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#define MAX 6
#define MaxQueue 999999


typedef struct Board{
    int row;
    int col;
    int father_index;
    int list_num; 
    int f;  
    int array[MAX][MAX];
} Board;


Board* readfile(FILE *fp, Board *board_init);
void see(Board *board);
Board* roll(Board *board, int mode, int num);
int IsSame(Board *board, Board *board_list);
int NewInList(Board *board, Board **list, int cnt);
int IsFinal(Board *board);
int BFS(Board **list, int cnt);
void StepPrint(Board **list, int cnt, Board *tep);
void test(void);


int main(int argc, char **argv)
{
    FILE* fp;
    int type=0;
    char *v="-v";

    if(argc ==2) {
        type = 1;
        if((fp = fopen(argv[1],"r"))==NULL){
            exit(EXIT_FAILURE);
        }
    }else if(argc == 3){
        if(strcmp(v,argv[1]) == 0){
            type = 2;
        }
        argv[1] = argv[2];
        if((fp = fopen(argv[2],"r"))==NULL){
            exit(EXIT_FAILURE);
        }
    }

    fp = fopen(argv[1],"r");   //read file
    int row=0, col=0;
    fscanf(fp, "%d %d\n", &row, &col);

    Board *board_init = (Board*)malloc(sizeof(Board));  // define father board
    board_init->row = row;
    board_init->col = col;
    board_init->father_index = 0;
    board_init->list_num = 0;
    board_init->f = 0;
    board_init = readfile(fp, board_init); //give father board the value of array
    fclose(fp);

    Board **list = (Board**)malloc(MaxQueue*sizeof(Board*));  //creat queue
    list[0] = board_init;  //first board(array)
    int cnt=1;  //count board (cnt+1个board)

    cnt = BFS(list, cnt);
    int step = list[cnt-1]->f;

    if( type==1 )
    {
        printf("%d moves\n",step);
    }else if( type==2 )
    {
        Board *tep = (Board*)malloc(sizeof(Board));
        StepPrint(list, cnt, tep);
        free(tep);
    }

    for(int i=0; i<cnt;i++){  //free space
        free(list[i]);
    }
    free(list);

    test();
    return 0;
}

Board* readfile(FILE *fp, Board *board_init)    //read array in file
{
    char *temp = (char *)calloc((board_init->row*board_init->col+1), sizeof(char));
    char c[MAX]={0};
    int i=0,k=0;
    while(fgets(temp,sizeof(temp),fp)){
        sscanf(temp, "%s", c);
        if(k>0){i++;k=0;}
        while(c[k]!='\0') 
        {
            board_init->array[i][k]=c[k];
            k++;
        }
    }
    free(temp);
    return board_init;
}

void see(Board *board)
{
    for(int i=0; i<board->row;i++){
        for(int j=0; j<board->col;j++){
            printf("%c ", board->array[i][j]);
        }
        printf("\n");
    }
}

Board* roll(Board *board, int mode, int num)  //roll, num - fixed number of rows and columns
{
    Board *board_new = (Board *) malloc (sizeof(Board));
    board_new->row = board->row;
    board_new->col = board->col;
    board_new->father_index = board->list_num;   //mark father index
    board_new->f = board->f+1;            //mark f

    //copy array
    for(int i=0; i<board->row;i++){
        for(int j=0; j<board->col;j++){
            board_new->array[i][j] = board->array[i][j];
        }
    }

    int temp=0;
    if (mode ==1){        //left
        temp = board_new->array[num][0];
        for(int j=1;j<board_new->col;j++){
            board_new->array[num][j-1]=board_new->array[num][j];
        }
        board_new->array[num][board_new->col-1] = temp;
    }else if( mode==2 ){    //right
        temp = board_new->array[num][board_new->col-1];
        for(int j=board_new->col-1;j>0;j--){
            board_new->array[num][j]=board_new->array[num][j-1];
        }
        board_new->array[num][0] = temp;
    }else if( mode==3 ){    //up
        temp = board_new->array[0][num];
        for(int i=1; i<board_new->row;i++){
            board_new->array[i-1][num]=board_new->array[i][num];
        }
        board_new->array[board_new->row-1][num] = temp;
    }else if( mode== 4){     //down
        temp = board_new->array[board_new->row-1][num];
        for(int i=board_new->row-1;i>0;i--){
            board_new->array[i][num]=board_new->array[i-1][num];
        }
        board_new->array[0][num] = temp;
    }

    return board_new;

}

int IsSame(Board *board, Board *board_list)  //Whether arrat is same
{
    int repeat = 0;    //same - 0
    for(int i=0; i<board->row;i++){
        for(int j=0;j<board->col;j++){
            if ( board->array[i][j] != board_list->array[i][j]){
                repeat = 1;
            }
        }
    }
    return repeat;
}

int NewInList(Board *board, Board **list, int cnt)
{
    int same = 1;  
    for (int i=0; i<cnt;i++){
        same = IsSame(board,list[i]);
        if (same==0){
            return 0;  //repeat - 0
        }
    }
    return 1;
}

int IsFinal(Board *board)
{
    int final = 1;  //last array- final = 1
    for(int j=0; j<board->col;j++){
        if( board->array[0][j] != '1'){
            final = 0;
        }
    }
    return final;
}

int BFS(Board **list, int cnt)
{
    int final = 0;
    int repeat = 0;
    int row = list[0]->row;
    int col = list[0]->col;
    int start=0;  //record board is changed
    int number=0;  //record value of listnumber
    Board *board_new;
    while(final == 0 && start<cnt)
    {
        number = 0;
        for(int i=0; i<row && final==0;i++)
        {
            board_new = roll(list[start],1,i);  //left
            repeat = NewInList(board_new,list,cnt);
            if (repeat == 1)
            {
                board_new->list_num = number;
                number++;
                list[cnt] = board_new;             //add into list
                cnt++;
                final  = IsFinal(board_new);
            }else if( repeat ==0 ){
                free(board_new);
            }

            board_new = roll(list[start],2,i);  //right
            repeat = NewInList(board_new,list,cnt);
            if (repeat == 1)
            {
                board_new->list_num = number;
                number++;
                list[cnt] = board_new;             //add into list
                cnt++;
                final  = IsFinal(board_new);
            }else if( repeat ==0 ){
                free(board_new);
            }
        }

        for(int i=0; i<col && final==0;i++)
        {
            board_new = roll(list[start],3,i);  //up
            repeat = NewInList(board_new,list,cnt);
            if (repeat == 1)
            {
                board_new->list_num = number;
                number++;
                list[cnt] = board_new;             //add into list
                cnt++;
                final  = IsFinal(board_new);
            }else if( repeat ==0 ){
                free(board_new);
            }

            board_new = roll(list[start],4,i);  //down
            repeat = NewInList(board_new,list,cnt);
            if (repeat == 1)
            {
                board_new->list_num = number;
                number++;
                list[cnt] = board_new;             //add into list
                cnt++;
                final  = IsFinal(board_new);
            }else if( repeat ==0 ){
                free(board_new);
            }
        }

        start++;
    }
    return cnt;
}

void StepPrint(Board **list, int cnt, Board *tep)
{
    int step = list[cnt-1]->f;
    int *count = (int *)malloc(20*sizeof(int));
    tep = list[cnt-1];
    count[0] = cnt-1;
    int num=0;
    step--;
    for(int i=cnt-2;i>=0;i--)
    {
        if(list[i]->f == step){
            if(tep->father_index == list[i]->list_num){
                num++;
                count[num] = i;
                tep = list[i];
                step--;
            }
        }
    }

    for(int i=num;i>=0;i--)
    {
        printf("%d:\n",list[count[i]]->f);
        see(list[count[i]]);
        printf("\n");
    }
    free(count);
}

void test(void)
{
    Board *test1 = (Board*)malloc(sizeof(Board));
    test1->row = 3;
    test1->col = 3;
    test1-> father_index = 0;
    test1->list_num = 0;
    test1->f = 0;
    for(int i=0; i<test1->row;i++){
        for (int j=0; j<test1->col;j++){
            if (i==0){
                test1->array[i][j] = '1';
            }else{
                test1->array[i][j]='0';
            }
        }
    }

    Board *test2 = (Board*)malloc(sizeof(Board));
    test2->row = 3;
    test2->col = 3;
    test2-> father_index = 0;
    test2->list_num = 0;
    test2->f = 0;
    for(int i=0; i<test2->row;i++){
        for (int j=0; j<test2->col;j++){
            if (i==0){
                test2->array[i][j] = '1';
            }else{
                test2->array[i][j]='0';
            }
        }
    }
    test2->array[0][0]='0';
    test2->array[test2->row-1][0]='1';
    Board *test3;
    test3 = roll(test1,3,0);
    assert(IsSame(test1,test2)==1);
    assert(IsSame(test2,test3)==0);


    free(test1);
    free(test2);
    free(test3);
}