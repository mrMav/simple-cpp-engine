#include "StateManager.h"

namespace Engine
{
    // the only purpose of this is to register
    // the singleton mem adress.
    StateManager stateManager;

    StateManager::StateManager()
    {

    }

    StateManager::~StateManager()
    {
        
    }

    void StateManager::AddState(std::string name, GameState* state)
    {
        auto it = _States.find(name);

        if (it != _States.end())
        {
            // animation exists, return that
            _ENGINE_LOG("StateManager", "Could not add state. Key already exists: " << name)
            return;
        } else
        {
            state->SetName(name);
            _States.insert({name, state});            
            _ENGINE_LOG("StateManager", "Added state with key: " << name)
        }
    }

    void StateManager::ChangeState(std::string name, bool preserveCurrent)
    {   
        if(_CurrentState != nullptr && name == _CurrentState->GetName())
        {
            _ENGINE_LOG("StateManager", "Cannot change states because state is already the active one.")
            return;
        }

        auto it = _States.find(name);

        if(it != _States.end())
        {
            // state exists
            _QueuedState = it->second;

        } else
        {
            _ENGINE_LOG("StateManager", "Cannot change states because state doesn't exists: " << name)
        }

    }

    void StateManager::Update(float delta)
    {
        if(_QueuedState != nullptr)
        {
            if(_CurrentState != nullptr)
            {
                _CurrentState->Shutdown();
            }

            _CurrentState = _QueuedState;
            _CurrentState->Init();
            _QueuedState = nullptr;
        }

        _CurrentState->Update(delta);

    }

    void StateManager::Render(float delta)
    {
        if(_CurrentState == nullptr) return;

        _CurrentState->Render(delta);
    }

    void StateManager::Shutdown()
    {
        if(_CurrentState == nullptr) return;

        // free memory
        for(auto& state : _States)
        {   
            _ENGINE_LOG("StateManager", "Deleting state with key: " << state.second->GetName())
            delete state.second;
        }

    }

}