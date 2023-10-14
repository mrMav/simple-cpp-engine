#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "Internal.h"
#include "GameState.h"

namespace Engine
{

    class StateManager : public Singleton<StateManager>
    {
        private:

            std::map<std::string, Ref<GameState>> _States;

            /// @brief A vector that should act as a stack, to track what states are in a preserved state.
            /// The preserved state serves the purposed of changing state but keeping the last change state
            /// memory intact. An example could be changing from a playing state to the options menu state.
            /// When the options state is closed, we want to restore the playing state with the state it had.
            std::vector<Ref<GameState>> _PreservedStack;

            Ref<GameState>  _CurrentState;

        public:

            StateManager();
            ~StateManager();

            void AddState(std::string name, Ref<GameState> state);

            /// @brief Changes from one state to another.
            /// @param name 
            /// @param preserveCurrent *not implemented*
            void ChangeState(std::string name, bool preserveCurrent);
            void Update(float delta);
            void Render(float delta);
            void Shutdown();

    };

}