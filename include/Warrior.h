#include <iostream>
#include <string>
#include "Hero.h"
using namespace std;
#pragma once

class Warrior : public Hero {
    private:
        void levelUp();
    public:
        Warrior(string in_name, int in_level, int in_healthPower, int in_magicPower, int in_Strength, int in_dexterity, int in_agility, int in_money);
        ~Warrior();        
};