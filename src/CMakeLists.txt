
set(HEADERS
    ${HEADERS}
    Typedefs.h
    Internal.h
    Engine.h
    Singleton.h
    StateManager.h
    GameState.h
    Game.h
    Timer.h    
)

set(SOURCE
    ${SOURCE}
    StateManager.cpp
    GameState.cpp
    Game.cpp
    Timer.cpp
)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
