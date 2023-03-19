
#include "FrameBufferTest.h"

#include <glm/glm.hpp>
#include <vector>
#include <limits>
#include <math.h>


using namespace Engine;

namespace FrameBufferTestGame
{

    bool useFrameBuffer = false;
    float angle = 0;

    Camera2D* currentCamera = nullptr;


    TestGame::TestGame(uint32_t screenWidth, uint32_t screenHeight, const char* windowTitle)
        : Game(screenWidth, screenHeight, windowTitle)
    {

    };

    TestGame::~TestGame()
    {
        delete quad;
        delete[] quad_vertices;
        delete[] quad_indices;
        delete framebuffer;
        delete sceneViewport;
        delete camera;
        delete spritebatch;
        delete dude;
    }


    /*
    * Use this function to load and create the game elements
    */
    void TestGame::Load()
    {

        // creating a square with normalized positions

        renderTargetWidth  = 24 * 3;
        renderTargetHeight = 24 * 3;

        sceneViewport = new Viewport(renderTargetWidth, renderTargetHeight);

        quad = new VertexArray(&VertexPositionTexture::Attributes);
        
        quad_vertices = new VertexPositionTexture[4];
        quad_vertices[0].Position = glm::vec3(-1,  1, 0);  // top left
        quad_vertices[1].Position = glm::vec3( 1,  1, 0);  // top right
        quad_vertices[2].Position = glm::vec3( 1, -1, 0);  // bottom right
        quad_vertices[3].Position = glm::vec3(-1, -1, 0);  // bottom left

        quad_vertices[0].Texture = glm::vec2(0, 1);   // top left
        quad_vertices[1].Texture = glm::vec2(1, 1);   // top right
        quad_vertices[2].Texture = glm::vec2(1, 0);   // bottom right
        quad_vertices[3].Texture = glm::vec2(0, 0);   // bottom left

        quad->SetVertices(quad_vertices, 4 * sizeof(VertexPositionTexture));

        quad_indices = new uint16_t[6];
        quad_indices[0] = 0;
        quad_indices[1] = 1;
        quad_indices[2] = 2;

        quad_indices[3] = 0;
        quad_indices[4] = 2;
        quad_indices[5] = 3;

        quad->SetIndices(quad_indices, 6);

        // create a framebuffer smaller than the screen size
        framebuffer = new FrameBuffer(renderTargetWidth, renderTargetHeight);
        screenSpaceShader = Shader("Resources/normalized_vertex.vert", "Resources/sample_fragment.frag");
        //screenSpaceShader.setInt("screenTexture", 0);

        // load game world related stuff
        spritebatchShader = Shader("Resources/vertex.vert", "Resources/fragment.frag");
        dude = new Texture2D("Resources/dude1.png", {});

        sceneCamera = new Camera2D(*sceneViewport);
        camera = new Camera2D(GetViewport());
        camera->Zoom = static_cast<float>(GetViewport().Width()) / renderTargetWidth;

        spritebatch = new Spritebatch();

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    };

    /*
    * This function will be called once per frame.
    * Use this to update you game logic.
    * delta is the amount of time since the last frame
    */
    void TestGame::Update(float delta)
    {
        
        if (Input::IsKeyJustDown(Key::F))
        {
            useFrameBuffer = !useFrameBuffer;
            
        }
        if (Input::IsKeyJustDown(Key::T))
        {
            camera->Zoom = static_cast<float>(GetViewport().Width()) / renderTargetWidth;
        }
        if (Input::IsKeyJustDown(Key::R))
        {
            camera->Zoom = 1;
        }

        if (useFrameBuffer)
            currentCamera = sceneCamera;
        else
            currentCamera = camera;

        sceneCamera->Update(delta);
        camera->Update(delta);
        
    };

    /*
    * Use this function to render your game
    * delta is the amount of time since the last frame
    */
    void TestGame::Render(float delta)
    {

        if (useFrameBuffer)
        {
            // render to framebuffer first
            glViewport(0, 0, renderTargetWidth, renderTargetHeight);
            framebuffer->Bind();

        }
        else
        {
            glViewport(0, 0, GetViewport().Width(), GetViewport().Height());
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        glClearColor(0.392, 0.584, 0.929, 1);  // good ol' cornflower blue
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        angle += 45.0f * delta;

        // draw our scene
        spritebatch->Begin(&spritebatchShader, currentCamera, glm::vec4(1));
        spritebatch->Draw(dude, -dude->GetWidth() / 2.0, -dude->GetHeight() / 2.0, glm::radians(angle));  // drawing the dude centered
        spritebatch->End();


        if (useFrameBuffer)
        {
            // draw the screen quad with the rendered framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(0, 0, GetViewport().Width(), GetViewport().Height());
            glDisable(GL_DEPTH_TEST);
            glClearColor(0.8, 0.8, 0.8, 1);
            glClear(GL_COLOR_BUFFER_BIT); // only need to clear the color, since we do not perform depth or stencil here

            // maybe i can just use the spritebatch as well?

            // spritebatch->Begin(&screenSpaceShader, currentCamera, glm::vec4(1), 0);
            // spritebatch->Draw(framebuffer->GetColorTexture(), 0, 0);
            // spritebatch->End();

            screenSpaceShader.use();
            quad->Bind();
            framebuffer->BindTexture();
            dude->Bind();
            quad->DrawElements();

        }


    };

}
