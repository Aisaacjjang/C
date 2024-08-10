//lesser.c -- 둘 중에서 작은 것을 구한다.
#include<stdio.h>
int imin(int, int);

int main(void)
{
    int evil1, evil2;
    printf("두 정수를 입력하시오(끝내려면 q): \n");
    while(scanf("%d %d", &evil1, &evil2) == 2)
    {
        printf("(%d, %d)에서 작은 것은 %d\n", evil1, evil2, imin(evil1,evil2));
        printf("두 정수를 입력하시오(끝내려면 q):\n");
    }
    printf("종료!\n");

    return 0;
}

int imin(int n, int m)
{
    int min;

    if (n < m)
        min = n;
    else
        min = m;

    return min;
}
//예제에서는 imin()함수는 min에 대입된 값을 리턴한다. min이 int형이기 때문에,
//imin 함수도 int형이다. 변수min은 imin()에만 알려진다. 
//그러나 min의 값은 키워드 return을 통해 호출 함수로 리턴된다. 