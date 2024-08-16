#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
void poong1(int);
void poong2(int,int,int);

int main(void)
{
    int num,num2,num3,num4,i ;    
    
    for(i=0; ;i++){
        printf("6 이상의 수를 입력하세요: ");
        scanf("%d", &num);
        if (6 > num ){
                printf("6 이상의 수만 입력해주세요.\n");
                while (getchar() != '\n');
                continue;
        }
            else break;
    }
    system("clear");
    sleep(1);
    for (int i = 0; i < 60; i++)
    {
        poong1(num);
        sleep(1);
        system("clear");
        poong2(num,num2,num3);
        sleep(1);
        system("clear");
    }

    return 0;
}

void poong1(int n)
{
    int i, j, k, l, x, y ;
    if(n % 2 == 0){
        n = n + 2;
    }
    if(n % 2 != 0){
        n = n + 1;
    }
    //풍차1
    printf("\n\n\n");
    for(i = 0 ; i< n; i++){
        for(x = 0 ; x < 3; x++)
            printf("   ");
        for(j = 0; j < i + 1 ; j++)
            printf(" * ");
        for(k = 0; k < n - i - 1 ; k++)
            printf("   ");
        for(l = n; l > 0 ; l--){                 //한번 써보고 싶었음.
            if(l < n-i+1){
            printf(" * ");
            }
        } 
    printf("\n");    
    }

    for(i = 0 ; i< n; i++){
        for(x = 0 ; x < 3; x++)
            printf("   ");
        for(j = 0; j < n - i - 1 ; j++)
            printf("   ");
        for(k = 0; k < i + 1 ; k++)
            printf(" * ");
        for(x = 0; x < i  ; x++)
            printf("   ");
        for(y = 0; y < n - i ; y++)
            printf(" * ");
    printf("\n");
    }
}

void poong2(int n, int n2, int n3)
{
    int i, j, k, l, x, y ;

    if(n % 2 == 0){
        n = n + 4;
    }
    if(n % 2 != 0){
        n = n + 3;
    }
    n2 = n/2 + 1;
    n3 = n/2;
//풍차2
//윗 날개 1번
    for(i = 0 ; i< n3; i++){
        for(j = 0 ; j < n3 - i+ n2 -1 ; j++)               
            printf("   ");
        for(k = 0 ; k < i + 1 ; k ++)
            printf(" * ");
        printf("\n");
    }

    for(i = 0 ; i< n2; i++){
        for(j = 0 ; j < i+n2-1; j++)
            printf("   ");
        for(k = 0; k < n3 - i + 1; k++)
            printf(" * ");
    //윗 날개 2번
        for(j = 0 ; j < n2 - i -1 ; j++)               
            printf("   ");
        for(k = 0 ; k < i + 1 ; k ++)
            printf(" * ");
        for(l = 0 ; l < i ; l++)
            printf(" * ");
        printf("\n");    
    }


// 아랫 날개 1번
    for(i = 0 ; i< n2; i++){
        for(j = -1 ; j < i - 1 ; j++)               
            printf("   ");
        for(k = 0 ; k < n3 - i + 1 ; k ++)
            printf(" * ");
        for(l = 0 ; l < n3 - i; l++)
            printf(" * ");
        //아랫 날개 2번
        for(x = -1; x < i - 1 ; x++)
            printf("   ");
        for(y = 0; y < i+1; y++)
            printf(" * ");
        printf("\n");
    }
    for(i = 0 ; i < n3 ; i++){
        for(j = 0; j < n + 1 ; j++)
            printf("   ");
        for(l= 0; l < n3 - i ; l++)
            printf(" * ");
        printf("\n");
    }
}