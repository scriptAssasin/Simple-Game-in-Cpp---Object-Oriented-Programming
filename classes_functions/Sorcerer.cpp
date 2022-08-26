#include <Sorcerer.h>
#include <iostream>

using namespace std;

Sorcerer::Sorcerer(string in_name, int in_level, int in_healthPower, int in_magicPower, int in_Strength, int in_dexterity, int in_agility, int in_money)
:Hero(in_name, in_level, in_healthPower, in_magicPower, in_Strength, in_dexterity + 2, in_agility * 2,in_money)
{}

Sorcerer::~Sorcerer() {}

void Sorcerer::levelUp()
{
    Level += 1;
    experience = 0;
    magicPower += 1;
    Strength += 1;
    dexterity += 4;  //buffed
    agility += 10;  
}