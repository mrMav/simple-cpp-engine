set(HEADERS
    ${HEADERS}
    FrameAnimation.h
    TileSet.h
    StateManager.h
    GameState.h
)

set(SOURCE
    ${SOURCE}
    FrameAnimation.cpp
    TileSet.cpp
    StateManager.cpp
    GameState.cpp
)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
