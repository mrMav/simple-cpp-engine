#include <iostream>

#include "TestGame.h"

int main()
{

    MyTestGame::TestGame game = MyTestGame::TestGame(800, 600, "My new game");
    game.Run();

    exit(EXIT_SUCCESS);

}