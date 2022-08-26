#include <Warrior.h>
#include <iostream>

using namespace std;

Warrior::Warrior(string in_name, int in_level, int in_healthPower, int in_magicPower, int in_Strength, int in_dexterity, int in_agility,int in_money)
:Hero(in_name, in_level, in_healthPower, in_magicPower, in_Strength * 2, in_dexterity, in_agility * 2,in_money)
{}

Warrior::~Warrior() {}

void Warrior::levelUp()
{
    Level += 1;
    experience = 0;
    magicPower += 1;
    Strength += 10;  //buffed
    dexterity += 1;
    agility += 10;
}