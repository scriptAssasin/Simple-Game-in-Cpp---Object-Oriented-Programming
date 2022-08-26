#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Grid.h"
using namespace std;

Grid::~Grid() {
    for(int i=0; i < 3; i++) {
        for(int j=0; j < 3; j++) {
            delete grid[i][j];
        }
    }
    delete hero_square;
    cout << "Grid deleted!" << endl;
}

void Grid::createSquares(List<Item> *l1, List<Spell> *l2) 
{

    srand(time(NULL));

    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++)
        {
            List<Item> *lista1 = new List<Item>(); //List of items. We will need this list for uncommon squares, to pass the items
            List<Spell> *lista2 = new List<Spell>(); //List of spells. We will need this list for uncommon squares, to pass the spells 
            
            for(int i=1; i<=5; i++)
            {
                lista1->insert_start(l1->remove(1)); //Each square will get different items, so once we use an item we delete it from the main (big) list
                lista2->insert_start(l2->remove(1)); //Same goes for spells
            }

            int random1 = rand() % 2;
            int random2 = rand() % 2;
            int random = random1 + random2; //it ranges from 0 to 2. So three cases

            switch (random) {
                case(0) : //if random == 0 -> uncommon Square non accessible
                    grid[i][j] = new Square(non_accesible,non_common,lista2,lista1);   //only uncommon squares take lists cause of market
                    break;
                case(1) : //if random == 1 -> common Square
                    if(random1) //depends on random1 if we will pick accesible or non_accesible
                        grid[i][j] = new Square(accesible,common);
                    else 
                        grid[i][j] = new Square(non_accesible,common);

                    delete lista1;
                    delete lista2;
                    break;
                case(2) : //if random == 1 -> common, accesible Square
                    grid[i][j] = new Square(accesible,common);
                    delete lista1;
                    delete lista2;
                    break;
            }
            // cout << "position in grid: (" << i << "," << j << ")" << endl;
            cout << endl; 
            
        }
    }

    delete l1;
    delete l2;

}


Grid::Grid(int x, int y, Hero **team, List<Item> *l1, List<Spell> *l2)
{
    createSquares(l1, l2); //Creating the Squares of the grid
    hero_square = new HeroSquare(grid[x][y],x,y); //the team of the Heroes will be at this square when the game starts
    grid[x][y]->insert_team(team,true);
    cout << "The world of the game has been created!" << endl;
}


void Grid::set_hero_square(Square *s,int x1, int y1) {
    hero_square->set(s,x1,y1);
}

void Grid::displayMap() {
    cout << "Game map is: " << endl;
    cout << endl;
    for (int i=0; i < 3; i++) {
            for (int k=0; k < 3; k++) {
                cout << "Square (" << i << "," << k << ")  "; 
            }
            cout << endl;
            for(int z=0; z < 3; z++) {
                if((this->getSquare(i,z))->is_common()) cout << "    common     ";
                else { cout << "non_common   "; } 
            }
            cout << endl;
            for (int a=0; a < 3; a++) {
                if((this->getSquare(i,a))->nonAccessible()) cout << "non_accessible! ";
                else cout << "accessible!   ";
            }
            cout << endl;
            for (int l=0; l < 3; l++) {
                if( (hero_square->get_x() ==  i) && (hero_square->get_y() ==  l)) cout << "heroes in column:" << l << ""; //column where heroes are
            }
            cout << endl;
            cout << endl;     
        }
        cout << endl;

}

bool Grid::fight_chance() { //this function returns true or false, if there will be a fight or not. 
    srand(time(NULL));
    int chance = rand() % 4;   //about 25% chance
    if(chance == 2) return true;
    else return false;
}

bool Grid::square_move(Square *square,int x,int y) {  //function that puts heroes in a given square
    
    Square *current_square = hero_square->get_square();
    Hero **Hero_Team = current_square->get_team();
    
    if(square->insert_team(Hero_Team)) {
        current_square->remove_team();
        set_hero_square(square,x,y);
        grid[x][y]->fight(fight_chance()); 
        return true;   
    }
    
    return false;
}

void Grid::move() {
    
    int x = hero_square->get_x();
    int y = hero_square->get_y();
    //cout << "x: " << x << " y: " << y << endl;
    int direction;
    cout << "Select direction to move to:" << endl;
    cout << "1 : Right, 2 : Left, 3 : Up, 4 : Down" << endl;
    
    bool end = false;
    while(!end) {
        cin >> direction;
        if (direction < 1 || direction > 4) cout << "ERROR" << endl;
        switch(direction) {
            case (1) :
                if(y < 3) {
                    if(square_move(grid[x][y+1],x,y+1)) {
                        end = true;
                    }
                }
                break;

            case (2) :
                if(y > 0) {
                    if(square_move(grid[x][y-1],x,y-1)) {
                        end = true;
                    }
                }
                break;

            case (3) :
                if(x > 0) {
                    if(square_move(grid[x-1][y],x-1,y)) {
                        end = true;
                    }
                }
                break;

            case (4) :
                if (x < 3) {
                    if(square_move(grid[x+1][y],x+1,y)) {
                        end = true;
                    }
                }
                break;    
            
        }
        
        if (!end) cout << "Cannot move to that square, enter another direction" << endl; 
    }
}

void Grid::displayStats() {
    cout << "Select hero to check stats:" << endl;
    (hero_square->get_square())->printHeroes();
    cout << "4: All" << endl;
    int choice;
    cin >> choice;
    if (choice < 4 && choice > 0)
    (*((hero_square->get_square())->get_team()+choice-1))->display_stats();
    else if (choice == 4) {
        for(int i=0; i < 3; i++) {
            if((*((hero_square->get_square())->get_team()+choice-1)) != NULL) 
                (*((hero_square->get_square())->get_team()+i))->display_stats();
        }
    }
    else cout << "ERROR!" << endl;
 
}

void Grid::checkInventory() {
    cout << "Select hero to check his inventory:" << endl;
    (hero_square->get_square())->printHeroes();
    cout << "4: All" << endl;
    int choice;
    cin >> choice;
    if (choice < 4 && choice > 0)
    (*((hero_square->get_square())->get_team()+choice-1))->checkInventory();
    else if (choice == 4) {
        for(int i=0; i < 3; i++) {
            if((*((hero_square->get_square())->get_team()+choice-1)) != NULL) 
                (*((hero_square->get_square())->get_team()+i))->checkInventory();
        }
    }
    else cout << "ERROR!" << endl;
 
}

void Grid::UsePotion() {
    Square *current_square = hero_square->get_square();
    Hero **heroes = current_square->get_team();
    cout << "Select hero that will use a potion:" << endl;
    current_square->printHeroes();
    int selection;
    cin >> selection;
    if (selection > 3 || selection < 1) {
        cout << "Error: invalid selection!" << endl;
        return;
    }
    heroes[selection-1]->use(heroes[selection-1]->get_potion());
}

void Grid::ChangeItems() {
Square *current_square = hero_square->get_square();
    Hero **heroes = current_square->get_team();
    cout << "Select hero that will use a potion:" << endl;
    current_square->printHeroes();
    int selection;
    cin >> selection;
    if (selection > 3 || selection < 1) {
        cout << "Error: invalid selection!" << endl;
        return;
    }
    heroes[selection-1]->changeItem();
}