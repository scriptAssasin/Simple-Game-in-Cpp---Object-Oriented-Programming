#include "Item.h"
#include <iostream>
#include <string>
using namespace std;

Item::Item(string in_Name, int in_Price, int in_Required_Level)
{
    Name = in_Name;
    Price = in_Price;
    Required_Level = in_Required_Level;
    use_both_hands = false;
}


int Item::use() {
    return 1;
}

void Item::print() {
    cout << Name;
    switch(kind) {
        case(1) :
            cout << ", Armor ,";
            break;
        case(2) :
            cout << ", Weapon ,";
            break;
        case(3) :
            cout << ", Potion ,";
            break;
    }
    cout << "Price: " << Price;
    cout << ", Required Level: " << Required_Level;
}