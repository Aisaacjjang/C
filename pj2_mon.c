#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 30
char * s_gets(char * st, int n);
int randy(int ,int);
struct monster{
    char m_name[MAX];
    int m_atk;
    int m_max_hp;
};

int main(void)
{
    struct monster oak = {"오크용사", 0 , 0};
    oak.m_atk = randy(10,15);
    oak.m_max_hp = randy(50,100);

    struct monster zomb = {"좀비", 0 , 0};
    zomb.m_atk = randy(17,30);
    zomb.m_max_hp = randy(50,180);

    struct monster gool = {"구울", 0 , 0};
    gool.m_atk = randy(20,45);
    gool.m_max_hp = randy(120,280);

    struct monster skul = {"해골", 0 , 0};
    skul.m_atk = randy(28,55);
    skul.m_max_hp = randy(200,360);

    struct monster spa = {"스파토이", 0 , 0};
    spa.m_atk = randy(32,75);
    spa.m_max_hp = randy(260,360);

    struct monster e_hero1 = {"김이삭", 0 , 0};
    e_hero1.m_atk = randy(100,300);
     //e_hero1_max_hp = 히어로 현재체력의 200%

    struct monster e_hero2 = {"최윤식", 0 , 0};
    e_hero2.m_atk = randy(100,300);
    //e_hero2.m_max_hp = 히어로 현재체력의 200%

    struct monster e_hero3 = {"김수현", 0 , 0};
    e_hero3.m_atk = randy(100,300);
     //e_hero3.m_max_hp = 히어로 현재체력의 200%

    struct monster e_hero4 = {"정세현", 0 , 0};
    e_hero4.m_atk = randy(100,300);
     //e_hero4.m_max_hp = 히어로 현재체력의 200%

    struct monster e_hero5 = {"박성민", 0 , 0};
    e_hero5.m_atk = randy(100,300);
     //e_hero5.m_max_hp = 히어로 현재체력의 200%

    struct monster e_hero6 = {"곽성민", 0 , 0};
    e_hero6.m_atk = randy(100,300);
     //e_hero6.m_max_hp = 히어로 현재체력의 200%

    struct monster e_hero7 = {"김지섭", 0 , 0};
    e_hero7.m_atk = randy(100,300);
     //e_hero7.m_max_hp = 히어로 현재체력의 200%








    return 0;
}

int randy(int n1 ,int n2) //난수값의 범위를 n1~n2으로 설정
{
	int randomNumber[1];
    srand((unsigned int)time(NULL));
	for (int i = 0; i < 1; i++) {
		randomNumber[i] = rand() % (n2 - n1 +1) + n1;
		return randomNumber[i];
	}
}