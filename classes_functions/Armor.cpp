#include "Armor.h"

Armor::Armor(int dmr, string in_Name, int in_Price, int in_Required_Level) :
Item(in_Name,in_Price,in_Required_Level), damage_reduction(dmr) 
{
    kind = 1;
}

int Armor::use() {
    return damage_reduction;
}

void Armor::print() {
    Item::print();
    cout << " ,DamageReduction: " << damage_reduction;
}
        