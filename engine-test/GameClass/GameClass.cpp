#include <iostream>

#include <glm/glm.hpp>
#include <vector>
#include <limits>
#include <math.h>

#include <Engine.h>

using namespace Engine;

class TestGame : Game
{

    public:
    
    TestGame(uint32_t screenWidth, uint32_t screenHeight, const char* windowTitle)
    : Game(screenWidth, screenHeight, windowTitle)
    {

    }
    ~TestGame() { }

    void Run() override
    {
        Game::Run();
    }

    /*
     * Use this function to load and create the game elements
     */
    void Load() override
    {

    }

    /*
     * This function will be called once per frame.
     * Use this to update you game logic.
     * delta is the amount of time since the last frame
     */
    void Update(float delta) override
    {
        
    }

    /*
     * Use this function to render your game
     * delta is the amount of time since the last frame
     */
    void Render(float delta) override
    {
        glClear(GL_COLOR_BUFFER_BIT);


    }


};

int main()
{

    TestGame game = TestGame(800, 600, "My new game");
    game.Run();

    exit(EXIT_SUCCESS);

}