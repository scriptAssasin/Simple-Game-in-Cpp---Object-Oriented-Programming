#include <iostream>
#include <string>
#include "Living.h"
#include "Item.h"
#include "Spell.h"
#include "Potion.h"
#include "List.h"
#include "Weapon.h"
#include "Monster.h"
#include "Armor.h"
using namespace std;
#pragma once

class Hero : public Living {
    protected:
        int magicPower;
        int Strength;
        int dexterity;  //11 different levels of dexterity (0-10)
        int agility;   //same
        int money;
        int experience;
        virtual void levelUp();
        bool in_action;
        bool dodge();      //returns boolean to dodge attack or not
        List<Item> ItemInventory;
        List<Spell> SpellInventory;
        Item *hand1;
        Item *hand2;
        bool both_hands;    //both hands are occupied
        Item *clothing_slot;  
        
    public:
        Hero(string in_name, int in_level, int in_healthPower, int in_magicPower, int in_Strength, int in_dexterity, int in_agility, int in_money);
        virtual ~Hero();
        
        void gain_experience(int number_of_monsters);
        void checkInventory();
        void reduce_health(int ammount);
        void display_stats();
        int get_dexterity() { return dexterity; }
        int get_money() { return money; }
        int get_magic_power() const { return magicPower; }
        void set_money(int ammount) { money += ammount; }
        Spell *get_spell();
        Potion *get_potion();
        void magicPower_regain() { magicPower = (magicPower * 3) / 2; }
        void revive();
        void lose_half_money();
        void win_money(int number_of_monsters);
        void buyItem(Item *item);
        void buySpell(Spell *spell);
        Item *sellItem();
        Spell *sellSpell();
        void equip(Item *item);
        void use(Potion *potion);
        void increaseMP(int ammount);
        void increaseStr(int ammount);
        void increaseDex(int ammount);
        void increaseAg(int ammount);
        void attack(Monster *target);
        void castSpell(Spell* spell, Monster* monster);
        void changeItem();
        void insert_spell(Spell *spell);
        void insert_item(Item *item);
};