#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <limits>
#include <math.h>

#include <Engine.h>

using namespace Engine;

namespace MyTestGame
{

    class TestGame : Game
    {
        private:
        Spritebatch* spritebatch;
        Shader* shader;
        Texture2D* dude;
        Texture2D* test;
        Camera2D* camera;
        BitmapFont* font;

        glm::vec2 dude_position = glm::vec2(0, 0);

        public:
        
        TestGame(uint32_t screenWidth, uint32_t screenHeight, const char* windowTitle)
        : Game(screenWidth, screenHeight, windowTitle)
        {

        }
        ~TestGame()
        {
            delete spritebatch;
            delete shader;
            delete dude;
            delete test;
            delete camera;
            delete font;
        }

        void Run() override
        {
            Game::Run();
        }

        /*
        * Use this function to load and create the game elements
        */
        void Load() override
        {
            glClearColor(0.392, 0.584, 0.929, 1);  // good ol' cornflower blue

            shader = new Shader("../../Shaders/vertex.vert", "../../Shaders/fragment.frag");
            shader->use();
            dude = new Texture2D("../../Shaders/dude1.png", {});
            test = new Texture2D("../../Shaders/texture.png", {});

            camera = new Camera2D(GetViewport());
            camera->Position.x = 0;
            camera->Position.y = 0;
            camera->Position.z = 1.0f;
            camera->Zoom = 2.0f;

            spritebatch = new Spritebatch();

            font = new BitmapFont("../../Shaders/mbf_big_00.png", 10, 12);     

            CharData d = font->GetCharData('A');

        }

        /*
        * This function will be called once per frame.
        * Use this to update you game logic.
        * delta is the amount of time since the last frame
        */
        void Update(float delta) override
        {
            camera->Update(delta);

            dude_position.x = 0;
            dude_position.y = 60;

            if(Input::IsKeyJustDown(Key::L))
            {
                // std::string s = spritebatch->GetStats().String();
                std::string s = spritebatch->GetStats().String();
                std::cout << s << std::endl;
            }

            float speed = 200.0;
            if(Input::IsKeyPressed(Key::W))
            {
                camera->Position.y -= speed * delta;
            }
            if(Input::IsKeyPressed(Key::S))
            {
                camera->Position.y += speed * delta;
            }
            if(Input::IsKeyPressed(Key::A))
            {
                camera->Position.x -= speed * delta;
            }
            if(Input::IsKeyPressed(Key::D))
            {
                camera->Position.x += speed * delta;
            }
        }

        /*
        * Use this function to render your game
        * delta is the amount of time since the last frame
        */
        void Render(float delta) override
        {
            glClear(GL_COLOR_BUFFER_BIT);


            spritebatch->Begin(shader, camera, glm::vec4(1), 0);
            spritebatch->Draw(test, 0, 0);
            spritebatch->Draw(dude, dude_position.x, dude_position.y, 0);
            spritebatch->End();

            spritebatch->Begin(shader, camera, glm::vec4(1, 0, 0, 1), 0);
            spritebatch->DrawString(font, 0, -24, "Hello text!");
            spritebatch->DrawString(font, -100, -80, "What if I add a new\nline?");
            spritebatch->DrawString(font, 0, 0, "I guess\nthis thing\nreally\nworks?\n\n\nyeahhhh");
            spritebatch->DrawString(font, -200, 0, "LET'S GO\nALL CAPS\nHERE!");
            spritebatch->End();
        }


    };

}
