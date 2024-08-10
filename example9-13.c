//swap1.c -- 맞교환 함수 제1 버전
#include<stdio.h>
void interchange(int u, int v);     //함수 선언

int main(void)
{
    int x = 5, y = 10;

    printf("교환 전 x = %d, y = %d\n", x, y);
    interchange(x, y);
    printf("교환 후 x = %d, y = %d\n", x, y);

    return 0;
}

void interchange(int u, int v)     //함수 정의
{
    int temp;

    temp = u;
    u = v;
    v = temp;
}

//x,y 의 값을 교환하려고 하는 예제이나 교환이 되지않은 예이다.
//이를 수정하기위해 interchange()함수 안에 몇 개의 출력문을 넣어 본다.