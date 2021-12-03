#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<assert.h>
#define MAX 6

struct store{
    int ***list;  //store arrray
    int *f;  
    int star;  //star
    int tail;  //end 
};
typedef struct store store;


int **move(int **array,int row,int column,int mode,int num);  //roll mode:1up 2down 3left 4right num：row/column
int unique(int **parent, int **child, int row, int column);  //if the array is new or not
int **creat(int row, int column); 
void delete(int **array);
int find(int **array,int column);  //if the array is final or not
void see(int **array, int row, int column);  //print
void test(void);



int main(int argc, char **argv){
    FILE* board;
    int content=0;
    char *a="-v";
    if( argc==2 )
    {
        if((board = fopen(argv[1],"r"))==NULL){
            exit(EXIT_FAILURE);
        }
    }else if( argc==3 && strcmp(argv[1],a)==0 ){
        content=1;
    }

    board = fopen(argv[1],"r");  //read file
    char size[4]={0};
    fgets(size,4,board);  //read size
    size[1] = size[2];
    size[2] = '\0';
    int sz = atoi(size);
    int row = sz/10;
    int column = sz%10;
    int i=0, j=0;

    //creat array
    int **array;
    array = creat(row,column);

    char *temp = (char *)calloc((row*column+1), sizeof(char));
    char c[MAX]={0};
    int x=0,k=0;
    while(fgets(temp,sizeof(temp),board))
    {
        sscanf(temp, "%s", c);

        if(k>0){x++;k=0;}
        while(c[k]!='\0')  //char
        {
            array[x][k]=c[k];
            k++;
        }

    }
    free(temp);
    fclose(board);   //close file

    store store;
    store.star = 0;  //head
    store.tail = 1;  //end
    store.f = (int *)calloc(1,sizeof(int));  
    store.list = (int ***)calloc(1,sizeof(int **)); 

    store.list[0]=array; 
    store.f[0]=0;

    int roll = (row+column)*2;
    int flag=0;  // sign-new
    int re=0;  //sign-final
    int answer=0; 
    int **temarr;

    while( re == 0 && store.star<store.tail)
    {
        store.list = (int ***)realloc(store.list, (roll + store.tail) * sizeof(int **));    
        store.f = (int *)realloc(store.f, (roll + store.tail) * sizeof(int));

        for(j=0; j<row && answer==0; j++)   //row
        {
            temarr = creat(row,column);
            temarr = move(store.list[store.star], row, column, 3, j); //left
            for(i=0; i<store.tail; i++)
            {
                printf("temarr:\n");
                see(temarr,row,column);
                printf("\n");
                flag = 0;
                flag = unique(store.list[i],temarr,row,column);  //whether the array is new, 1 = new
                if (flag == 1)
                {
                    store.list[store.tail] = creat(row,column);
                    for(int x=0; x<row;x++){
                        for(int y=0;y<column;y++){
                            store.list[store.tail][x][y] = temarr[x][y];
                        }
                    }
                    store.f[store.tail] = store.star+1;
                    
                    printf("tail = %d  f = %d\n",store.tail, store.f[store.tail]);
                    see(temarr,row,column);
                    printf("\n");

                    re = find(temarr,column);  
                    if ( re==1 ) { answer=store.tail; }
                    store.tail++;  
                } 
            }
            delete(temarr);

            temarr = creat(row,column);
            temarr = move(store.list[store.star], row, column, 4, j);  //roll right
            for(i=0; i<store.tail; i++)
            {
                printf("temarr:\n");
                see(temarr,row,column);
                printf("\n");
                flag = 0;
                printf("i=%d  store.list:\n",i);
                see(store.list[i],row,column);
                printf("\n");
                flag = unique(store.list[i],temarr,row,column); 
                if (flag == 1)
                {
                    store.list[store.tail] = creat(row,column);
                    for(int x=0; x<row;x++){
                        for(int y=0;y<column;y++){
                            store.list[store.tail][x][y] = temarr[x][y];
                        }
                    }
                    store.f[store.tail] = store.star+1;

                    printf("tail = %d  f = %d\n",store.tail, store.f[store.tail]);
                    see(temarr,row,column);
                    printf("\n");

                    store.tail++; 
                    re = find(temarr,column);
                    if ( re==1 ) { answer=store.tail; }
                    store.tail++; 
                }
            }
            delete(temarr);

        }

        for(j=0; j<column && answer==0; j++)  //column
        {
            temarr = creat(row,column);
            temarr = move(store.list[store.star], row, column, 1, j); //roll up
            for(i=0; i<store.tail; i++)
            {
                printf("temarr:\n");
                see(temarr,row,column);
                printf("\n");
                flag = 0;
                flag = unique(store.list[i],temarr,row,column); 
                if (flag == 1)
                {
                    store.list[store.tail] = creat(row,column);
                    for(int x=0; x<row;x++){
                        for(int y=0;y<column;y++){
                            store.list[store.tail][x][y] = temarr[x][y];
                        }
                    }
                    store.f[store.tail] = store.star+1;     

                    printf("tail = %d  f = %d\n",store.tail, store.f[store.tail]);
                    see(temarr,row,column);
                    printf("\n");

                    re = find(temarr,column); 
                    if ( re==1 ){ answer=store.tail; }
                    store.tail++;  
                }
            }
            delete(temarr);

            
            temarr = creat(row,column);
            temarr = move(store.list[store.star], row, column, 2, j); //roll down
            for(i=0; i<store.tail; i++)
            {
                printf("temarr:\n");
                see(temarr,row,column);
                printf("\n");
                flag = 0;
                flag = unique(store.list[i],temarr,row,column); 
                if (flag == 1)
                {
                    store.list[store.tail] = creat(row,column);
                    for(int x=0; x<row;x++){
                        for(int y=0;y<column;y++){
                            store.list[store.tail][x][y] = temarr[x][y];
                        }
                    }
                    store.f[store.tail] = store.star+1;

                    printf("tail = %d  f = %d\n",store.tail, store.f[store.tail]);
                    see(temarr,row,column);
                    printf("\n");

                    re = find(temarr,column); 
                    if ( re==1 ){ answer=store.star+1; }
                    store.tail++;  
                }
            }
            delete(temarr);
        }
        store.star++;
    }



	int step = 0;
	int track[20];
	int p = re;
	do
	{
		track[step] = p;
		step++;
		p = store.f[p];
	} while(p != -1);
	
	if (content == 1){
        for (i = step - 1; i >= 0; i--){
			printf("%d:\n", (step - 1 - i));
			see(store.list[track[i]], row, column);
            }
    }else if (content == 0){
        printf("%d moves\n", step - 1);
    }

    test();
    return 0;
}

int **move(int **array,int row,int column,int mode,int num)
{
    int **child;
    child = creat(row, column);

    //copy array
    int i=0, j=0;
    for(i=0; i<row;i++)
    {
        for(j=0; j<column;j++)
        {
            child[i][j]=array[i][j];
        }
    }

    int temp=0;
    if(mode==1){
        temp = child[0][num];
        for(i=1;i<row;i++)
        {
            child[i-1][num]=child[i][num];
        }
        child[row-1][num]=temp;
    }else if(mode==2){
        temp = child[row-1][num];
        for(i=row-1;i>0;i--)
        {
            child[i][num]=child[i-1][num];
        }
        child[0][num]=temp;
    }else if(mode==3){
        temp = child[num][0];
        for(j=1;j<column;j++)
        {
            child[num][j-1]=child[num][j];
        }
        child[num][column-1]=temp;
    }else if(mode==4){
        temp = child[num][column-1];
        for(j=column-1;j>0;j--)
        {
            child[num][j]=child[num][j-1];
        }
        child[num][0]=temp;
    }

    return child;
}

int unique(int **parent, int **child, int row, int column)   //whether array is new
{
    int re=0;
    int i=0, j=0;

    for(i=0;i<row;i++)
    {
        for(j=0;j<column;j++)
        {
            if(child[i][j] != parent[i][j]){
                re = 1;
            }
        }
    }

    return re;
}

int **creat(int row, int column)
{
    int **array;
    int i=0;
    array = (int **)calloc(row,sizeof(int *)); 
    for (i=0;i<row;i++)
    {
        array[i]=(int *)calloc(column,sizeof(int *));  
    }
    return array;
}

void delete(int **array)   
{
    free(*array);
    free(array);
}

int find(int **array,int column)  //1=final
{
    int re=1;
    int j=0;
    for(j=0;j<column;j++){
        if(array[0][j] != '1'){
            re=0;
        }
    }

    return re;
}

void see(int **array, int row, int column)
{
    int i=0,j=0;
    for(i=0;i<row;i++)
    {
        for(j=0;j<column;j++){
            printf("%c",array[i][j]);
        }
        printf("\n");
    }
}

void test(void)
{
    int **array1, **array2;
    array1 = creat(5,4);
    array2 = creat(5,4);
    array1[0][0]=0; array1[0][1]=0; array1[0][2]=0; array1[0][3]=0;
    array1[1][0]=1; array1[1][1]=0; array1[1][2]=1; array1[1][3]=0;
    array1[2][0]=0; array1[2][1]=0; array1[2][2]=0; array1[2][3]=0;
    array1[3][0]=0; array1[3][1]=0; array1[3][2]=0; array1[3][3]=0;
    array1[4][0]=0; array1[4][1]=1; array1[4][2]=0; array1[4][3]=1;

    array2[0][0]=0; array2[0][1]=0; array2[0][2]=0; array2[0][3]=0;
    array2[1][0]=1; array2[1][1]=0; array2[1][2]=1; array2[1][3]=0;
    array2[2][0]=0; array2[2][1]=0; array2[2][2]=0; array2[2][3]=0;
    array2[3][0]=0; array2[3][1]=0; array2[3][2]=0; array2[3][3]=0;
    array2[4][0]=0; array2[4][1]=1; array2[4][2]=0; array2[4][3]=1;

    assert(unique(array1, array2, 5, 4)==0);
    delete(array1);
    delete(array2);

    int **array3, **array4;
    array3 = creat(4,4);
    array4 = creat(4,4);
    array3[0][0]=0; array3[0][1]=0; array3[0][2]=0; 
    array3[1][0]=0; array3[1][1]=0; array3[1][2]=1; 
    array3[2][0]=0; array3[2][1]=1; array3[2][2]=1; 

    array4[0][0]=0; array4[0][1]=0; array4[0][2]=0; 
    array4[1][0]=0; array4[1][1]=1; array4[1][2]=1;
    array4[2][0]=0; array4[2][1]=0; array4[2][2]=1; 
    assert(move(array3,3,3,1,1)==array4);
    delete(array3);
    delete(array4);

}
