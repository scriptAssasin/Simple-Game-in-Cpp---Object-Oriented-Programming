#include <iostream>
#include <string>
#include "List.h"
#include "Hero.h"

using namespace std;
#pragma once

class Market {
    private:
        List<Spell> *l1;
        List<Item> *l2;
    public:
        Market(List<Spell> *Li1,List<Item> *Li2);
        ~Market();
        
        void display();
        void display_items();
        void display_spells();
        Item *buy_item(int place,Hero *hero);
        Spell *buy_spell(int place,Hero *hero);
        int sell_spell(Spell *spell);
        int sell_item(Item *item);
};