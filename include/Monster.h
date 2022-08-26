#include <iostream>
#include <string>
#include "Living.h"
using namespace std;
#pragma once

class Hero;

class Monster : public Living {
    protected:
        int MinimumDamage;
        int MaximumDamage;
        int MinimumDamage_original;
        int MaximumDamage_original;
        int Defense;
        int Defense_original;
        int dodge_chance;
        virtual bool dodge();
    public:
        Monster(string in_name, int in_level, int in_healthPower, int in_MinimumDamage, int in_MaximumDamage, int in_Defense);
        virtual ~Monster() {}

        void reduce_health(int ammount);
        void attack(Hero *target);
        void temporary_damage_reduction();
        void temporary_defense_reduction();
        virtual void temporary_dodge_reduction();
        void displayStats();
};