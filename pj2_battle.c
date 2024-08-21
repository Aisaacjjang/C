#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int scan(int, int, int);
int main(void)
{
    int num,b_cnt;

    printf("전투 발생!\n");
    sleep(1);
    system("clear");
    b_cnt += 1;

    for(int i = 0 ; ;i++){
        for(int i=0; ;i++){
            printf("1.공격\n2.스킬\n3.아이템\n4.도망\n");
            scanf("%d", &num);
            scan(num ,1 , 4);
            if( num == 1){
            printf("공격!\n");
            printf("적 사망!\n");
            b_cnt = 0;
            break;
            }
            if( num == 2){
            printf("1.나선환\n2.치도리\n3.사륜안\n");    
            scanf("%d", &num);
            scan(num ,1 , 3);
            break;
            }
            if( num == 3){
            printf("1.빨간물약 개수\n2.주황물약 개수\n3.하얀물약 개수\n4.아메리카노 개수\n");
            scanf("%d", &num);
            scan(num ,1 , 4);
            break;
            }
            if( num == 4){
            printf("도망 성공!\n");
            break;
            }
        }
    if (b_cnt == 0)
    break;
    }
        
}


int scan(int n,int n1,int n2)
{
    if ( n < n1 || n > n2 ){
        printf("다시 입력해주세요.\n");
        while (getchar() != '\n')
        continue;
    }
}


