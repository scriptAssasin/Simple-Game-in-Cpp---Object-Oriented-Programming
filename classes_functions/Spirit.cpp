#include "Spirit.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Spirit::Spirit(string in_name, int in_level, int in_healthPower, int in_MinimumDamage, int in_MaximumDamage, int in_Defense) :
Monster(in_name,in_level,in_healthPower,in_MinimumDamage,in_MaximumDamage,in_Defense) {
    dodge_chance = 8;
}

Spirit::~Spirit() {}

bool Spirit::dodge()
{
    srand(time(NULL));
    int chance = rand() % dodge_chance;
    
    if(chance == 0)
        return false;
    else
        return true;
}