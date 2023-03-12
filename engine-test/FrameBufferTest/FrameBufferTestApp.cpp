#include <iostream>

#include "FrameBufferTest.h"

int main()
{

    FrameBufferTestGame::TestGame game = FrameBufferTestGame::TestGame(800, 800, "FramebufferTestApp");
    game.Run();

    exit(EXIT_SUCCESS);

}
