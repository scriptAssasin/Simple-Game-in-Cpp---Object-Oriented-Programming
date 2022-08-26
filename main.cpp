#include <iostream>
#include "Grid.h"
#include "functions.h"
#include "List.h"
using namespace std;

int main() {
    Grid *World = startGame(); 

    int choice = menu();
        while(choice != Quit) {    
            switch(choice) {         //player choices
                case (DisplayMap) :
                    World->displayMap();
                    break;
                case (Move) :
                    World->move();
                    break;
                case (DisplayStats) :
                    World->displayStats();
                    break;
                case (OpenMarket) :
                    if(!((World->get_current_square())->is_common()))
                        (World->get_current_square())->acces_market();
                    else cout << "No market available!" << endl;
                    break;
                case (CheckInventory) :
                    World->checkInventory();
                    break;
                case (UsePotion) :
                    World->UsePotion();
                    break;
                case (ChangeItems) :
                    World->ChangeItems();
                    break;

            }
            choice = menu();
        }

    quitGame(World);  
    return 0;    
}