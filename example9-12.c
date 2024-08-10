//loccheck.c -- 변수들이 어디에 저장되는지 확인한다
#include<stdio.h>
void mikado(int);             // 함수 선언
int main(void)
{
    int pooh = 2, bah = 5;    // main()의 지역 변수
    printf("main()에 있는 pooh = %d, &pooh = %p\n", pooh , &pooh);
    printf("main()에 있는 bah = %d, &bah = %p\n", bah, &bah);
    mikado(pooh);

    return 0;
}

void mikado(int bah)          //함수 정의
{
    int pooh = 10;            //mikado()의 지역 변수

    printf("mikado()에 있는 pooh = %d, &pooh =%p\n",pooh ,&pooh);
    printf("mikado()에 있는 bah = %d, &bah = %p\n", bah, &bah);
}
/*예제 9.12는 주소를 출력하기위해 ANSI C의 %p 포맷을 사용한다.
%p가 주소를 표시하는 방식은 시스템마다 다르다. 그러나 이 예제를 위해 우리가 사용한 시스템과 같은,
대부분의 컴파일러들이 16진수 표기로 주소를 출력한다.
이 출력은 첫째, 두개의 pooh는 서로 다른 주소를 가진다.
둘째, 함수 호출 mikado(pooh)는 실전달인자(main()에 있는 pooh)의 값(2)를 형식매개변수(miakdo()에 있는 bah)에 전달한다.*/
