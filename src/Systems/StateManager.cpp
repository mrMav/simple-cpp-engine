#include "StateManager.h"

namespace Engine
{
    StateManager stateManager;

    StateManager::StateManager()
    {

    }

    StateManager::~StateManager()
    {
        
    }

    void StateManager::AddState(std::string name, Ref<GameState> state)
    {
        auto it = _States.find(name);

        if (it != _States.end())
        {
            // animation exists, return that
            _ENGINE_LOG("StateManager", "Could not add state. Key already exists: " << name)
            return;
        } else
        {
            _ENGINE_LOG("StateManager", "Added state with key: " << name)
            _States.insert({name, state});
        }
    }

    void StateManager::ChangeState(std::string name, bool preserveCurrent)
    {   
        if(_CurrentState != nullptr && name == _CurrentState->GetName())
        {
            _ENGINE_LOG("StateManager", "Cannot change states because state is already the active one.")
            return;
        }

        if(_CurrentState != nullptr)
        {
            _CurrentState->Shutdown();
        }

        auto it = _States.find(name);

        if(it != _States.end())
        {
            // state exists
            _CurrentState = it->second;

            // init here or on next update loop?
            _CurrentState->Init();
        }

    }

    void StateManager::Update(float delta)
    {
        if(_CurrentState == nullptr) return;

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

        _CurrentState->Shutdown();
    }

}