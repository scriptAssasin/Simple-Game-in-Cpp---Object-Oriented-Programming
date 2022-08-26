#include <iostream>
#include <string>
#include "Monster.h"
using namespace std;
#pragma once

class Spirit : public Monster {
    public:
        Spirit(string in_name, int in_level, int in_healthPower, int in_MinimumDamage, int in_MaximumDamage, int in_Defense);
        ~Spirit();

        bool dodge();
};