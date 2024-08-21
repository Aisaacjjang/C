#include<stdio.h>
#include<string.h>
#define MAX 20
char * s_gets(char * st, int n);
int M_hero();
struct character{
    char c_name[MAX];
    int c_atk;
    int c_max_hp;
    int c_hp;
    int c_max_mp;
    int c_mp;
    int c_level;
    int c_max_exp;
    int c_exp;
    int c_coin;
};

int main(void) 
{ 
    struct character hero = {"용사복이",0,0,0,0,0,0,0};
    hero.c_atk = 10;
    hero.c_max_hp = 100;
    hero.c_hp = 100;
    hero.c_max_mp = 10;
    hero.c_mp = 10;
    hero.c_level = 1;
    hero.c_max_exp = 30;
    hero.c_exp = 0;
    hero.c_coin = 300;
    printf("%s",hero.c_name);
}
    