#include <iostream>
#include "Living.h"

using namespace std;

Living::Living(string in_name, int in_level, int in_healthPower)
{
    Name = in_name;
    Level = in_level;
    healthPower = in_healthPower;
    healthPower_original = in_healthPower;
    in_combat = false;
    round = 0;
}

void Living::print() 
{
    cout << Name << endl;
}

void Living::faint() 
{
    in_combat = false; //incapable to fight
}

void Living::reduce_health(int ammount) 
{
    healthPower -= ammount;

    if (healthPower < 0) {
        healthPower = 0;
        faint();
    }
}

void Living::healthPower_regain()
{
    if(healthPower == 0) return;
    healthPower = (healthPower * 3) / 2;
}