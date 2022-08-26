#include <Paladin.h>
#include <iostream>

using namespace std;

Paladin::Paladin(string in_name, int in_level, int in_healthPower, int in_magicPower, int in_Strength, int in_dexterity, int in_agility, int in_money)
:Hero(in_name, in_level, in_healthPower, in_magicPower, in_Strength * 2, in_dexterity + 2, in_agility, in_money)
{}

Paladin::~Paladin() {}

void Paladin::levelUp()
{
    Level += 1;
    experience = 0;
    magicPower += 1;
    Strength += 10;  //buffed
    dexterity += 4;
    agility += 1;
}