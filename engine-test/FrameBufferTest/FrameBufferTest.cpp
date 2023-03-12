
#include "FrameBufferTest.h"

#include <glm/glm.hpp>
#include <vector>
#include <limits>
#include <math.h>


using namespace Engine;

namespace FrameBufferTestGame
{

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

        quad = new VertexArray(&VertexPositionTexture::Attributes);
        
        quad_vertices = new VertexPositionTexture[4];
        quad_vertices[0].Position = glm::vec3(-1,  1, 0);  // top left
        quad_vertices[1].Position = glm::vec3( 1,  1, 0);  // top right
        quad_vertices[2].Position = glm::vec3( 1, -1, 0);  // bottom right
        quad_vertices[3].Position = glm::vec3(-1, -1, 0);  // bottom left

        quad_vertices[0].Texture = glm::vec2(0, 0);   // top left
        quad_vertices[1].Texture = glm::vec2(1, 0);   // top right
        quad_vertices[2].Texture = glm::vec2(1, 1);   // bottom right
        quad_vertices[3].Texture = glm::vec2(0, 1);   // bottom left

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
        framebuffer = new FrameBuffer(800, 800);
        screenSpaceShader = Shader("../../Shaders/normalized_vertex.vert", "../../Shaders/sample_fragment.frag");
        //screenSpaceShader.setInt("screenTexture", 0);

        // load game world related stuff
        spritebatchShader = Shader("../../Shaders/vertex.vert", "../../Shaders/fragment.frag");
        dude = new Texture2D("../../Shaders/dude1.png", {});

        camera = new Camera2D(GetViewport());
        camera->Position.x = 0;
        camera->Position.y = 0;
        camera->Position.z = 1.0f;
        camera->Zoom = 8.0f;

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
        camera->Update(delta);

        dude_position.x = GetViewport().HalfWidth();
        dude_position.y = GetViewport().HalfHeight();
    };

    /*
    * Use this function to render your game
    * delta is the amount of time since the last frame
    */
    void TestGame::Render(float delta)
    {
        // render to framebuffer first
        glViewport(0, 0, 240, 240);
        framebuffer->Bind();
        glClearColor(0.392, 0.584, 0.929, 1);  // good ol' cornflower blue
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);


        // draw our scene
        spritebatch->Begin(&spritebatchShader, camera, glm::vec4(1));
        spritebatch->Draw(dude, 0, 0, 0);
        spritebatch->Draw(dude, 0, 0, 45.0, 0);
        spritebatch->End();


        // draw the screen quad with the rendered framebuffer
        glViewport(0, 0, 800, 800);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT); // only need to clear the color, since we do not perform depth or stencil here


        screenSpaceShader.use();
        quad->Bind();
        framebuffer->BindTexture();
        quad->DrawElements();

    };

}
