#pragma once

#include <glm/glm.hpp>
#include <Engine.h>

using namespace Engine;

namespace FrameBufferTestGame
{

    class TestGame : Game
    {

    public:

        TestGame(uint32_t screenWidth, uint32_t screenHeight, const char* windowTitle);

        ~TestGame();

        void Run() override { Game::Run(); };

        /*
        * Use this function to load and create the game elements
        */
        void Load() override;

        /*
        * This function will be called once per frame.
        * Use this to update you game logic.
        * delta is the amount of time since the last frame
        */
        void Update(float delta) override;

        /*
        * Use this function to render your game
        * delta is the amount of time since the last frame
        */
        void Render(float delta) override;


    private:

        Ref<Texture2D> dude;
        Ref<Shader> spritebatchShader;

        Ref<Camera2D> camera;
        Ref<Spritebatch> spritebatch;

        glm::vec2 dude_position;
        
    };
}
