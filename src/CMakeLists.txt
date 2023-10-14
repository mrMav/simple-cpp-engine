
set(HEADERS
    ${HEADERS}
    Typedefs.h
    Internal.h
    Engine.h
    Game.h
    Timer.h    
    Singleton.h
)

set(SOURCE
    ${SOURCE}
    Game.cpp
    Timer.cpp
)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
