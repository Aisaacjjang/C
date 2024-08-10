//swap2.c --  swap1.c에서 무엇이 잘못되었는지 조사한다.
#include<stdio.h>
void interchange(int u, int v);     

int main(void)
{
    int x = 5, y = 10;

    printf("교환 전 x = %d, y = %d\n", x, y);
    interchange(x, y);
    printf("교환 후 x = %d, y = %d\n", x, y);

    return 0;
}

void interchange(int u, int v)     
{
    int temp;

    printf("교환 전 u = %d, v = %d\n", u , v);
    temp = u;
    u = v;
    v = temp;
    printf("교환 후 u = %d, v = %d\n", u , v);
}

//x,y 의 값을 교환하려고 하는 예제이나 교환이 되지않은 예이다.
//이를 수정하기위해 interchange()함수 안에 몇 개의 출력문을 넣어 본다.