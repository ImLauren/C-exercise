#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>
#define N 21
#define swap(a,b) {int t; t=a; a=b; b=t; }


int **creat(void);
int **mutate(int **board);
int **repeat(int **board);
void see(int **board);


int main(void){
    int **board;
    board = creat();
    see(board);
    board = mutate(board);
    board = repeat(board);
    see(board);


    for(int i=0; i<N; i++){
        free(board[i]);
    }
    free(board);

    return 0;
}

int **creat(void)
{
    int **board = (int**)malloc(N*sizeof(int*));
    for (int i=0; i<N;i++){
        board[i] = (int *)malloc(N*sizeof(int));
    }

    srand(time(NULL));

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            board[i][j] = rand() % 10;
        }
    }


    return board;
}

int **mutate(int **board)
{
    for(int i=0; i<N;i++){
        for(int j=0;j<N/2;j++){
            if (board[i][j]<board[i][j+1]){
                swap(board[i][j],board[i][j+1]);
            }
        }
    }

    for(int i=0; i<N;i++){
        for(int j=N-1;j>N/2;j--){
            if (board[i][j]<board[i][j-1]){
                swap(board[i][j],board[i][j-1]);
            }
        }
    }

    for(int j=0; j<N;j++){
        for(int i=0; i<N/2;i++){
            if(board[i][j]<board[i+1][j]){
                swap(board[i][j],board[i+1][j]);
            }
        }
    }

    for(int j=0; j<N;j++){
        for(int i=N-1; i>N/2;i--){
            if(board[i][j]<board[i-1][j]){
                swap(board[i][j],board[i-1][j]);
            }
        }
    }

    return board;
}

int **repeat(int **board)
{
    for(int i=0;i<N*N*N*N;i++){
        board = mutate(board);
    }

    return board;
}

void see(int **board)
{

    for(int i=0; i<N; i++){
        for(int j=0; j<N;j++){
            printf("%d",board[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}
