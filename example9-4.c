//misuse.c -- 부정확하게 함수를 사용한다.
#include<stdio.h>
int imax();            //ANSI C 이전 형식의 함수 선언

int main(void)
{
    printf("(%d, %d)에서 큰 것은 %d\n", 3, 5, imax(3));
    printf("(%d, %d)에서 큰 것은 %d\n", 3, 5, imax(3.0, 5.0));
    
    return 0;
}

int imax(n, m)
int n, m;
{
    return (n > m ? n : m);
}
/*불일치한 전달인자가 발생시키는 문제점에 대한 ANSI C 표준의 해결책은,
함수선언에서 변수들의 데이터형까지도 선언하도록 허용하는 것이다.
그 결과가 함수 프로토타입 - 리턴형, 전달인자의 개수, 전달인자들의 데이터형을 서술하는 선언-이다.*/