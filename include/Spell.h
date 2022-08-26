#include <iostream>
#include <string>
#include "Monster.h"
using namespace std;
#pragma once

class Hero;

class Spell {
    private:
        string Name;
        int Price;
        int Required_Level;
        int MinimumDamage;
        int MaximumDamage;
        int Required_Magic;
    public:
        Spell(string in_Name, int in_Price, int in_Required_Level, int in_MinimumDamage, int in_MaximumDamage, int in_Required_Magic);
        ~Spell() {}
        
        virtual int use(Hero* hero, Monster* target);    
        string get_name() const { return Name; }
        int get_price() const { return Price; }
        int get_level() const { return Required_Level; }
        int get_magic() const { return Required_Magic; }
        void print();
};

class IceSpell : public Spell {
    public:
        int use(Hero* hero, Monster* target);
};

class FireSpell : public Spell {
    public:
        int use(Hero* hero, Monster* target);
};

class LightningSpell : public Spell {
    public:
        int use(Hero* hero, Monster* target);
};

