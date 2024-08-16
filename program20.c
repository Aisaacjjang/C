#include<stdio.h>
int main(void)
{
    int num,num2,num3, i, j, k, l, x, y, z  ;    

    for(i=0; ;i++){
        printf("2 이상의 수를 입력하세요: ");
        scanf("%d", &num);
        if (2 > num ){
                printf("2 이상의 수만 입력해주세요.\n");
                while (getchar() != '\n');
                continue;
        }
            else break;
    }

    if(num % 2 == 0)
        num = num - 1;
    
    num2 = num/2 + 1;
    num3 = num/2;

//윗 날개 1번
    for(i = 0 ; i< num3; i++){
        for(j = 0 ; j < num3 - i+ num2 -1 ; j++)               
            printf("   ");
        for(k = 0 ; k < i + 1 ; k ++)
            printf(" * ");
        printf("\n");
    }

    for(i = 0 ; i< num2; i++){
        for(j = 0 ; j < i+num2-1; j++)
            printf("   ");
        for(k = 0; k < num3 - i + 1; k++)
            printf(" * ");
    //윗 날개 2번
        for(j = 0 ; j < num2 - i -1 ; j++)               
            printf("   ");
        for(k = 0 ; k < i + 1 ; k ++)
            printf(" * ");
        for(l = 0 ; l < i ; l++)
            printf(" * ");
        printf("\n");    
    }

// 아랫 날개 1번
    for(i = 0 ; i< num2; i++){
        for(j = -1 ; j < i - 1 ; j++)               
            printf("   ");
        for(k = 0 ; k < num3 - i + 1 ; k ++)
            printf(" * ");
        for(l = 0 ; l < num3 - i; l++)
            printf(" * ");
        //아랫 날개 2번
        for(x = -1; x < i - 1 ; x++)
            printf("   ");
        for(y = 0; y < i+1; y++)
            printf(" * ");
        printf("\n");
    }
    for(i = 0 ; i < num3 ; i++){
        for(j = 0; j < num ; j++)
            printf("   ");
        for(l= 0; l < num3 - i ; l++)
            printf(" * ");
        printf("\n");
    }




return 0;
}