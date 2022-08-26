#include <iostream>
#include <string>
#include "Item.h"
using namespace std;
#pragma once

class Monster;

class Weapon : public Item {
    private:
        int Damage;
    public:
        Weapon(int damage,string in_Name, int in_Price, int in_Required_Level);
        ~Weapon() {}
        int use();
        void print();
};