#include "Market.h"
#include <iostream>
#include <string>

using namespace std;

Market::Market(List<Spell> *Li1,List<Item> *Li2) 
{
    l1 = Li1;
    l2 = Li2;
}

void Market::display_items() 
{
    cout << "Items are:" << endl;
    l2->display();
}

void Market::display_spells() 
{
    cout << "Spells are: " << endl;
    l1->display();
}

Item *Market::buy_item(int place,Hero *hero) 
{
    if( (l2->get_ith(place - 1))->get_price() <=  hero->get_money()) 
    {
        cout<<"Item "<<l2->get_ith(place - 1)->get_name()<<" purchased!"<<endl;
        return l2->remove(place);
    }
    else 
    {
        cout << "Not enough money!" << endl;
        return NULL;
    }
}

Spell *Market::buy_spell(int place,Hero *hero) 
{
    if( (l1->get_ith(place - 1))->get_price() <=  hero->get_money()) //hero has enough money
    {
        cout << "Spell " << (l1->get_ith(place - 1))->get_name() <<  " purchased!" << endl;
        return l1->remove(place);
    }

    else 
    {
        cout << "Not enough money!" << endl;
        return NULL;
    }

}

int Market::sell_spell(Spell *spell) 
{
    if(spell == NULL)
        return 0;
        
    l1->insert_start(spell);
    cout << "Spell " << spell->get_name() << " sold for " << spell->get_price() << endl;

    return ((spell->get_price()) / 2);   //sold for half its price
}

int Market::sell_item(Item *item) 
{

    if(item == NULL)
        return 0;

    l2->insert_start(item);
    cout << "Item " << item->get_name() << " sold for " << item->get_price() << endl;

    return ((item->get_price()) / 2);
}

void Market::display() 
{
    cout << endl;
    display_items();

    cout << endl;
    display_spells();
}

Market::~Market() 
{
    delete l1;
    delete l2;
}