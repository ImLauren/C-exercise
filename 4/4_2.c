#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define Wide 5
#define Tall 5
#define Gen 6

void see(int board[Tall][Wide]);
void next_board(int board[Tall][Wide]);
int inhabited_cell(int board[Tall][Wide],int m,int n);

int main(void){

    int board[Tall][Wide] = {{0,0,0,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,0,0,0}};
    
    see(board);
    for(int k=0; k<Gen;k++){
        next_board(board);
        see(board);
    }


    return 0;

}

void see(int board[Tall][Wide])
{
    for(int i=0; i<Tall;i++){
        for(int j=0;j<Wide;j++){
            printf("%d ",board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void next_board(int board[Tall][Wide])
{
    int arr[Tall][Wide];
    for(int i=0;i<Tall;i++){
        for(int j=0;j<Wide;j++){
            arr[i][j] = board[i][j];
        }
    }

    int sum=0;
    for (int i=0; i<Tall;i++){
        for (int j=0; j<Wide; j++){
            sum  = inhabited_cell(arr,i,j);
            if (arr[i][j] == 1){
                if(sum < 2 || sum > 3){
                    board[i][j] = 0;
                }else{
                    board[i][j] = 1;
                }
            }else if(arr[i][j] == 0){
                if(sum == 3){
                    board[i][j] = 1;
                }else{
                    board[i][j] = 0;
                }
            }
        }
    }

}

int inhabited_cell(int board[Tall][Wide],int m,int n)
{
    int sum = 0;

    if (m==0 && n==0){  //左上角
        sum = board[m][n+1] + board[m+1][n+1] + board[m+1][n];
    }else if(m==0 && n==Wide-1){  //右上角
        sum = board[m][n-1] + board[m+1][n-1] + board[m+1][n];
    }else if(m==0 && n>0 && n<Wide-1){  //第一行（除角）
        sum = board[m][n-1] + board[m+1][n-1] + board[m+1][n] + board[m+1][n+1] + board[m][n+1];
    }else if(m==Tall-1 && n==0){  //左下角
        sum = board[m-1][n] + board[m-1][n+1] + board[m][n+1];
    }else if(m==Tall-1 && n==Wide-1){  //右下角
        sum = board[m-1][n] + board[m-1][n-1] + board[m][n-1];
    }else if(m==Tall-1 && n>0 && n<Wide-1){  //最后一行（除角）
        sum = board[m][n-1] + board[m-1][n-1] + board[m-1][n] + board[m-1][n+1] + board[m][n+1];
    }else if(n==0 && m>0 && m<Tall-1){ //第一列（除角）
        sum = board[m-1][n] + board[m-1][n+1] + board[m][n+1] + board[m+1][n+1] + board[m+1][n];
    }else if(n==Wide-1 && m>0 && m<Tall-1){  //最后一列（除角）
        sum = board[m-1][n] + board[m-1][n-1] + board[m][n-1] + board[m+1][n-1] + board[m+1][n];
    }else{
        sum  = board[m-1][n-1] + board[m-1][n] + board[m-1][n+1] + board[m][n-1] + board[m][n+1] 
               + board[m+1][n-1] + board[m+1][n] + board[m+1][n+1];
    }
    return sum;
}

