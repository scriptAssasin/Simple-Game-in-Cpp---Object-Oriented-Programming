#include "Dragon.h"

Dragon::Dragon(string in_name, int in_level, int in_healthPower, int in_MinimumDamage, int in_MaximumDamage, int in_Defense) :
Monster(in_name,in_level,in_healthPower,in_MinimumDamage,in_MaximumDamage*2,in_Defense) {}

Dragon::~Dragon() {}