const int Quit = 0;
const int DisplayMap = 1;
const int Move = 2;
const int DisplayStats = 3;
const int OpenMarket = 4;
const int CheckInventory = 5;
const int UsePotion = 6;
const int ChangeItems = 7;

class Grid;
Grid *startGame(); 
int menu();
void quitGame(Grid *world);


