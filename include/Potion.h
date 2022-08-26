#include <iostream>
#include <string>
#include "Item.h"
//#include "Hero.h"
using namespace std;
#pragma once

class Hero;

class Potion : public Item {
    private:
        Hero *user;
        int effect;
        int percentage;
    public:
        Potion(int eff, int perc, string in_Name, int in_Price, int in_Required_Level) :
        Item(in_Name,in_Price,in_Required_Level), effect(eff), percentage(perc) { kind = 3; user = NULL; }
        ~Potion() {}

        void use(Hero *hero);
        void set_user(Hero *hero) { user = hero; }
};