#include <iostream>
#include <string>
#include "Warrior.h"
#include "Monster.h"
#include "Paladin.h"
#include "Spirit.h"
#include "Sorcerer.h"
#include "Dragon.h"
#include "Hero.h"
#include "Exoskeleton.h"
#include "Potion.h"
#include "Spell.h"
#include "Weapon.h"
#include "Armor.h"
#include "Market.h"
#include "List.h"
using namespace std;
#pragma once

const bool accesible = true;
const bool non_accesible = false;
const bool common = true;
const bool non_common = false;

class Grid;

class Square {
    private:
        bool accesible;
        bool common;
        Market* market;         //square's market
        Hero **TeamHeroes;     //Team of heroes tha are currently in the square
        bool heroes_defeated();
        bool monsters_defeated(Monster **monsters,int j);
        void heroes_win(int number); 
        void heroes_lose();
        int create_monsters(Monster **monsters,int level);
        void delete_monsters(Monster** monsters,int number);
    public:
        Square(bool is_accesible, bool is_common,List<Spell> *List1=NULL,List<Item> *List2=NULL);
        ~Square();

        bool insert_team(Hero **array,bool initial=false);
        Hero **remove_team();
        Hero **get_team();
        bool nonAccessible() { return !accesible; }
        bool is_common() { return common; }
        void acces_market(); 
        void fight(bool chance);     
        void printHeroes();   
        void displayStats(Monster **monsters);
};

class HeroSquare {         //class that holds inforation about the current position oh the geroes in the grid 
    private:
        Square *hero_square;
        int x;
        int y;
    public:
        HeroSquare(Square *starting_square,int a, int b) : 
        hero_square (starting_square), x(a), y(b) {}

        void set(Square *square,int a, int b);
        Square *get_square() { return hero_square; }
        int get_x() { return x; }
        int get_y() { return y; }
};

class Grid {
    private:
        HeroSquare *hero_square;
        Square* grid[3][3];
        bool fight_chance();   //returns chance for heroes to engage in a fight
        bool square_move(Square *square,int x,int y);
    public:
        Grid(int x, int y, Hero *team[3], List<Item> *l1, List<Spell> *l2);
        ~Grid();

        void createSquares(List<Item> *l1, List<Spell> *l2);
        void set_hero_square(Square *s,int x1, int y1);
        void displayMap();
        void displayStats();
        void move();
        Square *get_current_square() { return hero_square->get_square(); }  //returns square that heroes are currently in
        void checkInventory();
        Square *getSquare(int x, int y) { return grid[x][y]; }  //returns a specific squares pointer
        void UsePotion();
        void ChangeItems();
};

