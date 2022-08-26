#include <iostream>
#include "Hero.h"
#include <cstdlib>
#include <ctime>
using namespace std;

Hero::Hero(string in_name, int in_level, int in_healthPower, int in_magicPower, int in_Strength, int in_dexterity, int in_agility, int in_money) : Living(in_name, in_level, in_healthPower)
{
    magicPower = in_magicPower;
    Strength = in_Strength;
    dexterity = in_dexterity;
    agility = in_agility;
    money = in_money;
    experience = 0;
    both_hands = false;
    in_action = false;
    hand1 = NULL;
    hand2 = NULL;
    clothing_slot = NULL;
}

void Hero::display_stats()
{
    cout<<"Name: "<<Name<<" - Level:"<<Level<<" - healthPower:"<<healthPower<<" - magicPower:"<<magicPower<<" - Strength:"<<Strength<<" - dexterity:"<<dexterity<<" - agility:"<<agility<<" - money: "<<money<<endl;
}

void Hero::buyItem(Item *item) {

    if (item == NULL) 
        return;

    money -= (item->get_price()); //the money of the hero will be reduced
    ItemInventory.insert_start(item); //hero now owns the item

    if(item->get_kind() == 3) 
    { 
        ((Potion *)item)->set_user(this);
    }

    cout << "Item: " << item->get_name() << " added to " << this->get_name() << " inventory" << endl;
}

void Hero::buySpell(Spell *spell) {

    if (spell == NULL) 
        return;

    money -= (spell->get_price());
    SpellInventory.insert_start(spell);

    cout << "Spell: " << spell->get_name() << " added to " << this->get_name() << " inventory" << endl;
}


void Hero::checkInventory() {
    cout << "Inventory of " << this->get_name() << " is:" << endl;
    cout << endl;
    cout << "Owned items are:" << endl;

    ItemInventory.display();

    cout << endl;
    cout << "Owned spells are: " << endl;

    SpellInventory.display();
}

Item *Hero::sellItem() {   //add exeptions

    if(ItemInventory.get_length() == 0) //ItemInventory is a list. If list size == 0, it means that hero has not bought items.
    {
        cout<<"No items available to be sold"<<endl;
        return NULL;
    }

    cout << "Owned items are:" << endl;
    ItemInventory.display();

    int selection;
    cout << "Select a specific one:" << endl;
    cin >> selection;
    return ItemInventory.remove(selection); //remove the item, that user will choose
}

Spell *Hero::sellSpell() {

    if(ItemInventory.get_length() == 0)
    {
        cout<<"No spells available to be sold"<<endl;
        return NULL;
    }

    cout << "Owned spells are: " << endl;
    SpellInventory.display();

    int selection;
    cout << "Select a specific one:" << endl;
    cin >> selection;
    return SpellInventory.remove(selection);
} 

Hero::~Hero() {
    if(hand1 != NULL) 
        delete hand1;
    if(hand2 != NULL)
        delete hand2;
    if(clothing_slot != NULL)
        delete clothing_slot;
}

void Hero::increaseMP(int ammount) {
    magicPower += ammount;
}

void Hero::increaseStr(int ammount) {
    Strength += ammount;
}

void Hero::increaseDex(int ammount) {
    dexterity += ammount;
}
    
void Hero::increaseAg(int ammount) {
    agility += ammount;
}

void Hero::equip(Item *item) 
{

    if(item->get_kind() == 1) {
        clothing_slot = item;
        return;
    }
    
    else 
    {
        if(item->needs_both_hands()) //check if items needs both hands to be used
        { 
            hand1 = item;
            hand2 = item;
            both_hands = true;
            return;
        }

        if(both_hands) { //if both hands are already being used
            cout << "ERROR cannot equip item!" << endl;
            return;
        }

        else 
        {
            cout << "select hand to equip item:" << endl;

            int selection;
            cin >> selection;
            switch(selection) {
                case(1) :
                    hand1 = item;
                    break;
                case(2) :
                    hand2 = item;
                    break; 
            }
        }

    }
}

void Hero::use(Potion *potion) 
{

    if(potion == NULL) 
    {
        cout << "ERROR: Potion doesnt exist!" << endl;
        return;
    }

    potion->use(this);
    delete potion;
}

void Hero::attack(Monster *target) 
{

    if(hand1 == NULL) 
    {
        cout << "Cannot attack: no weapon equipped!" << endl;
        return;
    }

    int damage_dealt = hand1->use() + Strength;
        //hand2 is free always, cannot equip 2 weapons at the same time
        //or it has the same weapon as hand1 (2 handed weapon)
        //hand2 is free so a potion can be used
    target->reduce_health(damage_dealt);
}

void Hero::castSpell(Spell *spell, Monster *target) 
{
    magicPower -= spell->get_magic();
    if(spell == NULL) {
        cout << "ERROR: spell doesnt exist!" << endl;
        return;
    }
    spell->use(this,target);
    cout << "Hero " << get_name() << " casted spell!" << endl;
}

void Hero::reduce_health(int ammount) {
    if(dodge()) {
        cout << "Hero " << get_name() << " dodged the attack!" << endl;
        return;
    }
    
    int armor;
    if(clothing_slot != NULL) {
        armor = clothing_slot->use();   
    }
    else {
        armor = 0;
    }
    int damage_dealt = ammount - armor;   //armor reduces damaged received by the attack
    if (damage_dealt < 0) damage_dealt = 0;
    cout << "Hero " << get_name() << " received an attack of " << damage_dealt << " damage" << endl;
    healthPower -= damage_dealt;
    if (healthPower <= 0) {
        healthPower = 0;
        faint();
    }
}

bool Hero::dodge()
{
    srand(time(NULL));
    int chance = rand() % dexterity;

    if(chance == 0) {
        return false;
    }

    else if(chance >= 1) {   //the more dexterity grows, it is more likely to dodge th attck
        return true;
    }

    return false;
        
}

void Hero::win_money(int number_of_monsters)
{
    int money_to_win = number_of_monsters + 2 * Level;
    money += money_to_win;
}

void Hero::gain_experience(int number_of_monsters)
{
    int experience_to_gain = number_of_monsters/2 + Level;

    if(experience + experience_to_gain >= 10)
    {
        this->levelUp();
    }
    else
    {
        experience += experience_to_gain;
    }
}

void Hero::levelUp()
{
    Level += 1;
    experience = 0;
    magicPower += 1;
    Strength += 1;
    dexterity += 1;
    agility += 1;
}

Spell *Hero::get_spell() 
{
    cout << "select spell to use:" << endl;
    SpellInventory.display();

    int selection;
    cin >> selection;
    return SpellInventory.get_ith(selection-1);
}

Potion *Hero::get_potion() {
    cout << "select potion to use:" << endl;

    ItemInventory.display();
    int selection;
    cin >> selection;

    if(ItemInventory.get_ith(selection-1)->get_kind() == 3)
        return ((Potion *) ItemInventory.get_ith(selection-1));
    else 
    {
        cout << "Error: item is not a potion!" << endl;
        return NULL;
    }
}

void Hero::changeItem() {
    cout << "Select armor or weapon to change: " << endl;

    ItemInventory.display();
    int selection;
    cin >> selection;

    Item *item = ItemInventory.get_ith(selection-1); 

    if(item->get_kind() == 1) 
    {
        clothing_slot = item;
        cout << get_name() << " equiped armor " << item->get_name() << endl;
        return;
    }
    
    else if(item->get_kind() == 2) 
    {
        if(item->needs_both_hands()) 
        {
            hand1 = item;
            hand2 = item;
            both_hands = true;
            cout << get_name() << " equiped weapon " << item->get_name() << endl;
            return;
        }
        else {
            hand1 = item;
            cout << get_name() << " equiped weapon " << item->get_name() << endl;
            return;
        }
    }
    else {
        cout << "Error: invalid item!" << endl;
        return;
    }
}
void Hero::lose_half_money()
{
    money = money / 2; 
}

void Hero::insert_spell(Spell *spell) {
    SpellInventory.insert_start(spell);
}

void Hero::insert_item(Item *item) {
    ItemInventory.insert_start(item);
}

void Hero::revive()
{
    if(healthPower == 0)
    {
        healthPower = healthPower_original / 2;
        return;
    }
}