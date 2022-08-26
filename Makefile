#include path
INCLUDE = include/

# Αρχεία .o
OBJS = main.cpp functions.cpp classes_functions/Grid.cpp classes_functions/Square.cpp classes_functions/Living.cpp classes_functions/Hero.cpp classes_functions/Spell.cpp classes_functions/Item.cpp classes_functions/Monster.cpp classes_functions/Market.cpp classes_functions/Weapon.cpp classes_functions/Potion.cpp classes_functions/Warrior.cpp classes_functions/Sorcerer.cpp classes_functions/Paladin.cpp classes_functions/Armor.cpp

# Το εκτελέσιμο πρόγραμμα
EXEC = game

# Ορίσματα για make run
ARGS = #

$(EXEC): $(OBJS)
	g++ -std=c++11 $(OBJS) -o $(EXEC) -I$(INCLUDE)

run: $(EXEC)
	./$(EXEC) $(ARGS)
