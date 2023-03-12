#include <iostream>

#include "FrameBufferTest.h"

int main()
{

    FrameBufferTestGame::TestGame game = FrameBufferTestGame::TestGame(800, 800, "My new game");
    game.Run();

    exit(EXIT_SUCCESS);

}
