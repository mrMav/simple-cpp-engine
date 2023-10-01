
#include "FrameBufferTest.h"

#include <glm/glm.hpp>
#include <vector>
#include <limits>
#include <math.h>


using namespace Engine;

namespace FrameBufferTestGame
{
    float angle = 0;

    TestGame::TestGame(uint32_t screenWidth, uint32_t screenHeight, const char* windowTitle)
        : Game(screenWidth, screenHeight, windowTitle)
    {
        
    };

    TestGame::~TestGame() { };

    /*
    * Use this function to load and create the game elements
    */
    void TestGame::Load()
    {
        // Configure render target here, since we now have a opengl context.
        useRenderTarget = true;
        renderTargetWidth = 24;
        renderTargetHeight = 24;
        SetRenderTarget();

        // load game world related stuff
        spritebatchShader = std::make_shared<Shader>("Resources/vertex.vert", "Resources/fragment.frag");
        dude = std::make_shared<Texture2D>("Resources/dude1.png", TextureParams());

        camera = std::make_shared<Camera2D>(GetViewport());
        camera->Zoom = 1.0f;        

        spritebatch = std::make_shared<Spritebatch>();

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    };

    /*
    * This function will be called once per frame.
    * Use this to update you game logic.
    * delta is the amount of time since the last frame
    */
    void TestGame::Update(float delta)
    {
        camera->Update(delta);        
    };

    /*
    * Use this function to render your game
    * delta is the amount of time since the last frame
    */
    void TestGame::Render(float delta)
    {

        glClearColor(0.392, 0.584, 0.929, 1);  // good ol' cornflower blue
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        angle += 45.0f * delta;

        // draw our scene
        spritebatch->Begin(spritebatchShader.get(), camera.get(), glm::vec4(1));
        spritebatch->Draw(dude.get(), -dude->GetWidth() / 2.0, -dude->GetHeight() / 2.0, glm::radians(angle));  // drawing the dude centered
        spritebatch->End();

    };

}
