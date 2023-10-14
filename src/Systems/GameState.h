#pragma once

#include "Internal.h"
#include "Game.h"

namespace Engine
{

    class GameState
    {

        private:

        std::string Name;

        Game* _Game;

        public:

        GameState(Game* game) : _Game(game) { };
        virtual ~GameState() { };

        const std::string& GetName() const { return Name; };
        Game* GetGame() { return _Game; };

        void virtual Init() { };
        void virtual Update(float delta) { };
        void virtual Render(float delta) { };
        void virtual Shutdown() { };

    };

}