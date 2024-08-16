#include<stdio.h>
void poong1(int,int);
void poong2(int,int,int);

int main(void)
{
    int num, num2, num3, num4, i, j, k, l, x, y ;    
    
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
 
    num4 = num;

    if(num % 2 == 0){
        num = num + 2;
    }
    if(num % 2 != 0){
        num = num +1;
    }
    num2 = num/2 + 1;
    num3 = num/2;
    
    //풍차1
    for(i = 0 ; i< num4; i++){
        for(x = 0 ; x < 3; x++)
            printf("   ");
        for(j = 0; j < i + 1 ; j++)
            printf(" * ");
        for(k = 0; k < num4 - i - 1 ; k++)
            printf("   ");
        for(l = num4; l > 0 ; l--){                 //한번 써보고 싶었음.
            if(l < num4-i+1){
            printf(" * ");
            }
        } 
    printf("\n");    
    }

    for(i = 0 ; i< num4; i++){
        for(x = 0 ; x < 3; x++)
            printf("   ");
        for(j = 0; j < num4 - i - 1 ; j++)
            printf("   ");
        for(k = 0; k < i + 1 ; k++)
            printf(" * ");
        for(x = 0; x < i  ; x++)
            printf("   ");
        for(y = 0; y < num4 - i ; y++)
            printf(" * ");
    printf("\n");
    }


//풍차2
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
        for(j = 0; j < num + 1 ; j++)
            printf("   ");
        for(l= 0; l < num3 - i ; l++)
            printf(" * ");
        printf("\n");
    }


    return 0;
}

void poong1(int num, int num4)
{
    int num, num4, i, j, k, l, x, y ;  
    //풍차1
    for(i = 0 ; i< num4; i++){
        for(x = 0 ; x < 3; x++)
            printf("   ");
        for(j = 0; j < i + 1 ; j++)
            printf(" * ");
        for(k = 0; k < num4 - i - 1 ; k++)
            printf("   ");
        for(l = num4; l > 0 ; l--){                 //한번 써보고 싶었음.
            if(l < num4-i+1){
            printf(" * ");
            }
        } 
    printf("\n");    
    }

    for(i = 0 ; i< num4; i++){
        for(x = 0 ; x < 3; x++)
            printf("   ");
        for(j = 0; j < num4 - i - 1 ; j++)
            printf("   ");
        for(k = 0; k < i + 1 ; k++)
            printf(" * ");
        for(x = 0; x < i  ; x++)
            printf("   ");
        for(y = 0; y < num4 - i ; y++)
            printf(" * ");
    printf("\n");
    }
}

void poong2(int num, int num2, int num3)
{
    int num, num4 = num , i, j, k, l, x, y ;

    if(num % 2 == 0){
        num = num + 2;
    }
    if(num % 2 != 0){
        num = num +1;
    }
    num2 = num/2 + 1;
    num3 = num/2;
//풍차2
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
        for(j = 0; j < num + 1 ; j++)
            printf("   ");
        for(l= 0; l < num3 - i ; l++)
            printf(" * ");
        printf("\n");
    }
}