#include <iostream>
#include "Monster.h"
#include "Hero.h"
#include <ctime>
#include <cstdlib>

using namespace std; 

Monster::Monster(string in_name, int in_level, int in_healthPower, int in_MinimumDamage, int in_MaximumDamage, int in_Defense)
: Living(in_name, in_level, in_healthPower)
{
    MinimumDamage = in_MinimumDamage;
    MaximumDamage = in_MaximumDamage;
    MinimumDamage_original = in_MinimumDamage;
    MaximumDamage_original = in_MaximumDamage;
    Defense = in_Defense;
    Defense_original = in_Defense;
    dodge_chance = 4;
}

bool Monster::dodge() {

    srand(time(NULL));
    int chance = rand() % dodge_chance;

    if(chance == 0)
        return false;
    else
        return true;
}

void Monster::reduce_health(int ammount) {
    if(dodge()) {
        cout << "Monster " << get_name() << " dodged the attack!" << endl;
        return;
    }
    
    int damage_dealt = ammount - Defense;
    if (damage_dealt < 0) damage_dealt = 0;
    cout << "Monster " << get_name() << " received an attack of " << damage_dealt << " damage" << endl;
    healthPower -= ammount;
    if (healthPower <= 0) {
        healthPower = 0;
        faint();
    }
}

void Monster::temporary_damage_reduction() {
    if(in_combat)
    {
        if(round <= 4)
        {
            MinimumDamage = MinimumDamage / 2;
            MaximumDamage = MaximumDamage / 2;
        }
        else
        {
            MinimumDamage = MinimumDamage_original;
            MaximumDamage = MaximumDamage_original;
        }

    }
    else
    {
            MinimumDamage = MinimumDamage_original;
            MaximumDamage = MaximumDamage_original;
    }
}

void Monster::temporary_defense_reduction() {
    if(in_combat)
    {
        if(round <= 4)
        {
            Defense = MinimumDamage / 2;
        }
        else
        {
            Defense = Defense_original;
        }

    }
    else
    {
        Defense = Defense_original;
    }
}

void Monster::temporary_dodge_reduction() {
    if(in_combat)
    {
        if(round <= 4)
        {
            dodge_chance = 2;
        }
        else
        {
            dodge_chance = 4;
        }

    }
    else
    {
        dodge_chance = 4;
    }
}

void Monster::attack(Hero *target) 
{
    srand(time(NULL));

    int chance = (rand() % 11)*0.1;
    int damage_dealt = MinimumDamage + (MaximumDamage-MinimumDamage)*chance;

    cout << "Monster " << get_name() << " attacks " << " hero " << target->get_name() << endl;
    target->reduce_health(damage_dealt);
}

void Monster::displayStats() 
{
    cout << "Name: " << Name << " - Level: " << Level << " - Health: " << healthPower << " - MaximumDamage: " << MaximumDamage << " - Defense: " << Defense << endl;
}