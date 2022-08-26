#include <iostream>
#include <string>
using namespace std;
#pragma once

class Living {
    protected:
        bool in_combat;
        string Name;
        int Level;
        int healthPower;
        int healthPower_original;
        int round;
        void faint();
    public:
        Living(string in_name, int in_level, int in_healthPower);
        virtual ~Living() {};

        string get_name() const { return Name; }
        int get_level() const {return Level;}
        int get_health() const { return healthPower; }
        void print();
        void new_round() { round++; }
        virtual void reduce_health(int ammount);
        virtual void healthPower_regain();
        void set_in_combat() {in_combat = true;}
        void increase_round() {round++;}
        int get_round() {return round;}
    };