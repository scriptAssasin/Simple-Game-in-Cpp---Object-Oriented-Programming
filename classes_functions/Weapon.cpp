#include "Weapon.h"
#include <cstdlib>
#include <ctime>

Weapon::Weapon(int damage,string in_Name, int in_Price, int in_Required_Level) :
Item(in_Name,in_Price,in_Required_Level), Damage(damage) 
{
    srand(time(NULL));
    kind = 2;
    if( (rand() % 10) > 5)
        use_both_hands = true;
    else
        use_both_hands = false;
}

int Weapon::use() {
    return Damage;
}

void Weapon::print() {
    Item::print();
    cout << ", Damage: " << Damage;
}