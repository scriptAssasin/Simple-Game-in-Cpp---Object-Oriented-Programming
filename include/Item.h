#include <iostream>
#include <string>
using namespace std;
#pragma once

class Hero;

class Item {
    private:
        string Name;
        int Price;
    protected:
        int kind;   //eidos item
        bool use_both_hands;
        int Required_Level;
    public:
        Item(string in_Name, int in_Price, int in_Required_Level);
        virtual ~Item() {}
        virtual int use();   //effect of item
        int get_level() { return Required_Level; }
        string get_name() const { return Name; }  
        int get_price() const { return Price; }
        int get_level() const { return Required_Level; }
        virtual void print();
        int get_kind() { return kind; }
        bool needs_both_hands() { return use_both_hands; }
};