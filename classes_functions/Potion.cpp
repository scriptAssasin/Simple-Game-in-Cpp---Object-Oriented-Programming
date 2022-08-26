#include "Potion.h"
#include "Hero.h"


void Potion::use(Hero *hero) {
    if(hero->get_level() < Required_Level) {
        cout << "Cannot use potion: low level!" << endl;
        return;
    }
    
    switch(effect) {
        case(1) :
            hero->increaseAg(percentage);
            break;
        case(2) :
            hero->increaseDex(percentage);
            break;
        case(3) :
            hero->increaseMP(percentage);
            break;
        case(4) :
            hero->increaseStr(percentage);
            break;
    }
    cout << "Potion " << this->get_name() << " used!" << endl;
}