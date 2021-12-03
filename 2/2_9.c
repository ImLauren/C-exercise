#include<stdio.h>
#include<assert.h>
#include<math.h>

int caltime(int time);
void test(void);

int main(void){
    int time;
    printf("Type  the  time  required in second: \n");
    scanf("%d",&time);
    printf("Number  of  button  presses = %d\n",caltime(time));
    test();
    return 0;
}

int caltime(int time){
    int a[3] = {600,60,10};
    int count=0;
    int num = time;
    int i;
    int devide;
    while (num != 0){
        for (i=0;i<3;i++){
            if (num>=a[i]){
                devide = num / a[i];
                num = num % a[i];
                count = count + devide;
            }
        }

        if (num<10 && num!=0){
            count++;
            num = 0;
        }
    }
    return count;
}

void test(void){
    assert(caltime(25)==3);
    assert(caltime(705)==7);
}