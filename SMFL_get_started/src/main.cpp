#include "stdafx.h"
#include "GamePlat/Game4.h"


int main()
{    
    //creating a window     

    
    Game4 game;

    srand(static_cast<unsigned>(time(NULL)));
    
    //Game loop
    game.run();
    return 0;
}