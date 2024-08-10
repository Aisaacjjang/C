//lathead1.c
#include<stdio.h>
#define NAME "GIGATHINK, INC."
#define ADDRESS "101 Megabuck Plaza"
#define PLACE "Megapol is, CA 94904"
#define WIDTH 40

void starbar(void);          //함수 프로토타입

int main(void)
{
    starbar();
    printf("%s\n", NAME);
    printf("%s\n", ADDRESS);
    printf("%s\n", PLACE);
    starbar();                  //함수의 사용

    return 0;
}

void starbar(void)            //함수의 정의
{
    int count;
    for (count = 1; count <= WIDTH; count++)
        putchar('*');
    putchar('\n');
}
/*예제에서는 식별자 starbar를 세 군데에서 사용하고 있다.
첫 번째는, starbar()가 어떤 유형의 함수인지 컴파일러에게 알려 주는 함수 프로토타입이다.
두 번째는, 그 함수를 실행되게 만드는 함수 호출이다.
세 번째는, 그 함수가 무엇을 하는 것인지 정확하게 서술하고 있는 함수 정의이다.*/
