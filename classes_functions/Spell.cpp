#include "Spell.h"
#include "Hero.h"
#include <iostream>

using namespace std;

Spell::Spell(string in_Name, int in_Price, int in_Required_Level, int in_MinimumDamage, int in_MaximumDamage, int in_Required_Magic)
{
    Name = in_Name;
    Price = in_Price;
    Required_Level = in_Required_Level;
    MinimumDamage = in_MinimumDamage;
    MaximumDamage = in_MaximumDamage;
    Required_Magic = in_Required_Magic;
}


int Spell::use(Hero* hero, Monster* target) {
    if(hero->get_level() < Required_Level) {
        cout << "Cannot use spell: low level!" << endl;
        return 0;
    }
    
    if(hero->get_magic_power() < Required_Magic) {
        cout << "Cannot use spell: not enough Magic Power!" << endl;
        return 0;
    }
  
    //ass dexterity of the hero increases so does the damage dealt
    int damage_dealt = MinimumDamage + ( (MaximumDamage - MinimumDamage) * ((hero->get_dexterity()) * 0.1) );
    cout << "Magic Damage dealt to " << target->get_name() << endl;
    target->reduce_health(damage_dealt);
    
    cout << "Spell casted!" << endl;
    return Required_Magic; 
}

int IceSpell::use(Hero* hero, Monster* target) {
    target->temporary_damage_reduction();
    return Spell::use(hero,target);
}

int FireSpell::use(Hero* hero, Monster* target) {
    target->temporary_defense_reduction();
    return Spell::use(hero,target);
}

int LightningSpell::use(Hero* hero, Monster* target) {
    target->temporary_dodge_reduction();
    return Spell::use(hero,target);
}

void Spell::print() {
    cout << Name << " Spell";
    cout << " ,Price: " << Price;
    cout << ",RequiredLevel: " << Required_Level;
    cout << ",RequiredMagic: " << Required_Magic;
    cout << ",MaximumDamage: " << MaximumDamage;
} 