#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Grid.h"
using namespace std; 

void give_initial_items(Hero **array) {    //initial items for the possibility that a fight occurs before heroes visit a market
    for(int i = 0; i < 3; i++) {
        if(array[i] != nullptr) {
            array[i]->equip(new Weapon(10,"weapon1",0,0));
            array[i]->insert_item(new Weapon(10,"weapon2",0,0));
            array[i]->insert_item(new Weapon(10,"weapon3",0,0));
            array[i]->equip(new Armor(10,"armor",0,0));
            array[i]->insert_item(new Potion(1,10,"potion",0,0));
            array[i]->insert_spell(new Spell("spell",0,0,10,20,0));
        }
    }
}

Grid *startGame()
{
    srand(time(NULL));
    fstream names;
    fstream spells;
    fstream hero_names;

    cout << "Welcome to the game. Game starts now!" << endl;
    cout << endl;

    Hero **hero_array = new Hero*[3];
    
    List<Item> *names_list = new List<Item>();
    List<Spell> *spell_list = new List<Spell>();

    names.open("files/weapons.txt", ios::in);
    spells.open("files/spells.txt", ios::in);
    hero_names.open("files/names.txt", ios::in);

    int price = 1;

    if(!names) 
    {
        cout<<"No such file";
    }
    else
    {
        if(names.is_open())
        {
            string name;
            while(getline(names, name))   //items creation
            {
                name.resize(name.size() - 1);
                names_list->insert_start(new Armor(10,name, price++, 2));
                names_list->insert_start(new Potion(1,1,name, price++, 2));
                names_list->insert_start(new Weapon(10,name, price++, 2));
            }

            names.close();
        }
    }

    if(!spells) 
    {
        cout<<"No such file";
    }
    else
    {
        if(spells.is_open())
        {
            string spell;
            while(getline(spells, spell))    //spells creation
            {
                spell.resize(spell.size() - 1);
                spell_list->insert_start(new Spell(spell, price++, 2, 2, 2, 2));
            }

            spells.close();
        }
    }

    if(!hero_names)
    {
        cout<<"No such file!"<<endl;
    }
    else
    {
        if(hero_names.is_open())
        {
            string HeroName;

            srand(time(NULL));
            int hero_number = rand() % 3;

            for(int i=0; i<3; i++)    //hero creation
            {
                getline(hero_names, HeroName);

                if(i <= hero_number)
                    hero_array[i] = new Hero(HeroName, rand() % 10, rand() % 10, rand() % 100 + 1, rand() % 100 + 1, rand() % 100 + 1, rand() % 10, rand() % 1000 + 1);
                else
                    hero_array[i] = nullptr;

            }


            hero_names.close();

        }
    }


    give_initial_items(hero_array);
    return (new Grid(0,0,hero_array, names_list, spell_list));   //game world creation

}

int menu()  
{
    int option;

    cout<<"\n--------------Game Menu--------------\n"<<endl;
    cout<<"1.\tDisplay the Map of the game"<<endl;
    cout<<"2.\tMove to another square"<<endl;
    cout<<"3.\tDisplay the stats of the game"<<endl;
    cout<<"4.\tOpen the Market"<<endl;
    cout<<"5.\tCheck the Inventory"<<endl;
    cout<<"6.\tUse Potion"<<endl;
    cout<<"7.\tInterchange, equip or use items"<<endl;
    cout<<"0.\tQuit\n"<<endl;
    cout<<"Q: Make your selection:"<<endl;

    cin >> option;
    cout << endl;
    if(option < 0 || option > 7)
    {
      cout<<"INFO: That selection isn't valid. Please try again.\n"<<endl;
      cout<<"Q: Your choice? "<<endl;
    }
    cout<<"--------------"<<endl;

    return option;
}

void quitGame(Grid *world) {
    delete world;
    cout << "Game ended, world destroyed...." << endl;
    cout << "_______________________________" << endl;
    cout << "           GAME OVER!          " << endl;
    cout << "_______________________________" << endl;
}

