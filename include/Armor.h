#include <iostream>
#include <string>
#include "Item.h"
using namespace std;
#pragma once

class Armor : public Item {
    private:
        int damage_reduction;
    public:
        Armor(int dmr, string in_Name, int in_Price, int in_Required_Level);
        ~Armor() {}

        int use();
        void print();
        
};