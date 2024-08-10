//proto.c -- 함수 프로토타입을 사용한다
#include<stdio.h>
int imax(int, int); //프로토 타입
int main(void)
{
    printf("(%d,%d)에서 큰 것은 %d\n", 3, 5, imax(3,5));
    printf("(%d,%d)에서 큰 것은 %d\n", 3, 5, imax(3.0, 5.0));

    return 0;
}

int imax(int n, int m)
{
    return( n > m ? n : m);
}

/*예제 9.5를 컴파일하려고 시도했을 때, 컴파일러는 imax() 호출에서 형식매개변수의 개수가 너무 적다고 에러를 출력한다.
에러메시지와 경고메시지의 차이는, 에러는 컴파일을 중단하지만 경고는 컴파일을 허용한다는 것이다.*/