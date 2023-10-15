#pragma once

#include <type_traits>
#include "Internal.h"

namespace Engine
{   
    class GameState
    {
        private:

        std::string Name;

        void* _Game;

        public:

        GameState(void* game) : _Game(game) { };
        virtual ~GameState() { };

        const std::string& GetName() const { return Name; };
        void SetName(std::string name) { Name = name; };

        // I templated this function to be able to have this state
        // manager work for everygame. Not proud of the void ptr to the
        // game reference. But it works.
        template <typename T>
        T* GetGame() { return static_cast<T*>(_Game); };

        void virtual Init() { };
        void virtual Update(float delta) { };
        void virtual Render(float delta) { };
        void virtual Shutdown() { };

    };

}