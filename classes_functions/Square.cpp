#include <iostream>
#include <fstream>
#include "Grid.h"
#include "Market.h"
#include <cstdlib>
#include <ctime>
using namespace std;

Square::Square(bool is_accesible, bool is_common, List<Spell> *List1, List<Item> *List2)
{
    accesible = is_accesible;
    common = is_common;

    if(!is_common) 
    {
        market = new Market(List1,List2);
    }
        
    TeamHeroes = NULL;
}

bool Square::insert_team(Hero **array,bool initial) {
    if( (!initial) && (!accesible) ) //scenario at the start of the game
        return false;

    if (array == NULL) 
        cout << "null array at insert team!!" << endl;

    TeamHeroes = array;

    return true;
}

Hero **Square::remove_team() {
    Hero **returning = TeamHeroes;
    TeamHeroes = NULL;
    return returning;
}

Hero **Square::get_team() {
    if (TeamHeroes == NULL) cout << "null array at get_team!" << endl;
    return TeamHeroes; 
}

void Square::acces_market()
{   
    cout << "Welcome to this square's market!" <<endl;
    cout << endl;
    cout << "Select hero to interact with market:" << endl;
    printHeroes();

    int hero;
    cin >> hero;

    while (hero < 4) 
    {
        cout << "This is our inventory:" << endl;
        market->display();
        cout << endl;
        cout << endl;

        cout << "Select what you want to do:" << endl;
        cout << "1: Buy" << endl;
        cout << "2: Sell" << endl;
        cout << "3: See available goods" << endl;
        cout << "4: Go back" << endl;

        int choice;
        cin >> choice;
    
        while (choice != 4) 
        {
            if(choice < 1 || choice > 4) {
                cout << "Invalid option" << endl;
            }

            switch(choice) {
                case(1) :
                    cout << "Select item or spell (1 or 2): " << endl;
                    int selection;
                    cin >> selection;
                    cout << "Select a specific one: " << endl;
                    int sp;
                    cin >> sp;
                    if(selection == 1) {
                        TeamHeroes[hero]->buyItem(market->buy_item(sp,TeamHeroes[hero]));
                    }
                    else {
                        TeamHeroes[hero]->buySpell(market->buy_spell(sp,TeamHeroes[hero]));
                    }
                    break;
                case(2) :
                    cout << "Select item or spell: " << endl;
                    cin >> selection;
                    
                    if(selection == 1) {  //item is sold and hero receives his money
                        TeamHeroes[hero]->set_money(market->sell_item(TeamHeroes[hero]->sellItem())); 
                    }
                    else if(selection == 2) {  
                        TeamHeroes[hero]->set_money(market->sell_spell(TeamHeroes[hero]->sellSpell()));
                    }
                    else {
                        cout << "ERROR: invalid selection!" << endl;
                    }
                    break;
                case(3) :
                    market->display();
                    break;
            }

            cout << "what do you wanna do now?" << endl;
            cin >> choice;
        }

        cout << "Select another hero or exit:" << endl;
        cin >> hero;
    }

    cout << "Exiting market...." << endl;
}

void Square::printHeroes() {
    for(int i=1; i <= 3; i++) {
        if(TeamHeroes[i-1] != nullptr) {
            cout << i << ": ";
            TeamHeroes[i-1]->print();
        }
    }
}

Square::~Square() 
{

    if(!common) 
    {
        delete market;
    }

    if(TeamHeroes != NULL) 
    {
        for(int i=0; i < 3; i++) 
        {
            if(TeamHeroes[i] != nullptr) 
            {
                delete TeamHeroes[i];
            }
        }

        delete[] TeamHeroes;
    }

}



void Square::displayStats(Monster **monsters) {
    cout << "stats of heroes are:" << endl;

    for(int i=0; i < 3; i++) 
    {
        if(TeamHeroes[i] != nullptr) {
            TeamHeroes[i]->display_stats();
        }

    }

    cout << "stats of monsters are:" << endl;

    for(int i=0; i < 3; i++) 
    {
        if(monsters[i] != nullptr) 
        {
            monsters[i]->displayStats();
        }

    }

}

void Square::fight(bool chance) {
    if(!common) 
       return;

    if(TeamHeroes == NULL) 
        return;

    if(!chance) 
        return;

    cout << "A fight has began!!!" << endl;
    cout << endl;
    
    //monster creation
    Monster **Monsters;
    Monsters = new Monster*[3];
    int max_monsters =  create_monsters(Monsters,TeamHeroes[0]->get_level());
    
    bool terminate = false;
    int round = 1;

    while(!terminate) 
    {
        cout << "Round " << round << " of fight begins!" << endl;
        cout << "Do you want to display the stats of the heroes an monster?" << endl;

        string selection;
        string s1 = "yes";

        cin >> selection;
        if(selection.compare(s1) == 0) {
            displayStats(Monsters);
        }
        
        cout << endl;
        if(round % 2 == 0) 
        {
            cout << "Its the monsters turn" << endl;
            for(int i=0; i < max_monsters; i++) 
            {
                for(int j=0; j < 3; j++) 
                {
                    if(TeamHeroes[j] != NULL)
                        Monsters[i]->attack(TeamHeroes[j]);
                        Monsters[i]->set_in_combat();
                }
            }

        }

        else 
        {
            cout << "Its the heroes turn" << endl;

            for(int i=0; i < 3; i++) 
            {
                if(TeamHeroes[i] != nullptr) 
                {
                    cout << "Select action for hero " << TeamHeroes[i]->get_name() << endl;
                    cout << "1: Normal attack" << endl;
                    cout << "2: Spell attack" << endl;
                    cout << "3: Use potion" << endl;
                    cout << "4: Change weapons and armor" << endl;
                    cout << endl;

                    int choice;
                    cin >> choice;

                    switch(choice) 
                    {
                        case(1) :
                            for(int j=0; j < max_monsters; j++) {
                                TeamHeroes[i]->attack(Monsters[j]);
                            }
                            break;
                        case(2) :
                            for(int j=0; j < max_monsters; j++) {
                                TeamHeroes[i]->castSpell(TeamHeroes[i]->get_spell(),Monsters[j]);
                            }
                            break;
                        case(3) :
                            TeamHeroes[i]->use(TeamHeroes[i]->get_potion());
                            break;
                        case(4) :
                            TeamHeroes[i]->changeItem();
                            break;
                    }
                }

                else 
                {
                    break;
                }

            }
        }

        //fight ending scenarios

        if(monsters_defeated(Monsters,max_monsters)) {
            cout << "Heroes win the fight!!" << endl;
            
            heroes_win(max_monsters);
            terminate = true;
            delete_monsters(Monsters,max_monsters);

            break;
        }

        else if(heroes_defeated()) {
            cout << "Monsters win the fight!!" << endl;

            heroes_lose();
            terminate = true;
            delete_monsters(Monsters,max_monsters);

            break;
        }

        //stats regeneration
        for(int i=0; i < 3; i++) 
        {
                if(TeamHeroes[i] != nullptr) 
                {
                    TeamHeroes[i]->healthPower_regain();
                    TeamHeroes[i]->magicPower_regain();
                    TeamHeroes[i]->increase_round();
                }
        }

        for(int i=0; i < max_monsters; i++) 
        {
            Monsters[i]->healthPower_regain();
            Monsters[i]->increase_round();
        }

        cout << "Round " << round << " ends!" << endl;
        round++;
    }
}

bool Square::heroes_defeated() 
{
    int counter = 0;
    int i;

    for(i=0; i < 3; i++) 
    {
        if(TeamHeroes[i] != nullptr) 
        {
            if(TeamHeroes[i]->get_health() == 0) counter++;
        }

        else 
            break;
    }

    if (counter == i) //if all heroes die, they lose
        return true;

    else 
        return false;

}

bool Square::monsters_defeated(Monster **monsters,int j) {
    int counter = 0;
    int i;

    for(i=0; i < 3; i++) 
    {
        if(monsters[i] != nullptr) 
        {
            if(monsters[i]->get_health() == 0) counter++;
        }
        else 
            break;
    }

    if (counter == j) 
        return true;
    else 
        return false;

}

void Square::heroes_win(int number) 
{
     for(int i=0; i<3; i++)
     {
         if(TeamHeroes[i] != nullptr)
         {
            TeamHeroes[i]->win_money(number);
            TeamHeroes[i]->gain_experience(number);
            TeamHeroes[i]->revive();
         }
     }
}

void Square::heroes_lose() 
{
    for(int i=0; i<3; i++)
     {
         if(TeamHeroes[i] != nullptr)
         {
            TeamHeroes[i]->lose_half_money();
            TeamHeroes[i]->revive();
         }
     }
}

int Square::create_monsters(Monster **monsters,int level) {
    srand(time(NULL));
    
    fstream names;
    names.open("files/names.txt", ios::in);
    string name;          
    
    int max = rand() % 3 + 1;
    for(int i=0; i < max; i++) {
        getline(names, name);
        name.resize(name.size() - 1);
        if (TeamHeroes[i] != nullptr) {
            monsters[i] = new Monster(name,level,100,10,100,10);   //correct stats
        }
        else {
            monsters[i] = nullptr;
        }
    }
    names.close();
    return max;
}

void HeroSquare::set(Square *square,int a, int b)
{
    hero_square = square;
    x = a;
    y = b;
}

void Square::delete_monsters(Monster** monsters,int number)
{
    for(int i=0; i < number; i++) {
        delete monsters[i];
    }
    delete[] monsters;
}
