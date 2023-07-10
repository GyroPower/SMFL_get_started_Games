#include "Game3/Game3.h"


int main()
{    
    //creating a window     

    
    Game3 game;

    srand(static_cast<unsigned>(time(NULL)));
    
    //Game loop
    game.run();
    return 0;
}