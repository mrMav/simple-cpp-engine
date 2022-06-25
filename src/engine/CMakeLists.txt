
set(HEADERS
    ${HEADERS}
    Game.h
    Engine.h
)

set(SOURCE
    ${SOURCE}
    Game.cpp
)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
