
set(HEADERS
    ${HEADERS}
    Internal.h
    Engine.h
    Game.h
)

set(SOURCE
    ${SOURCE}
    Game.cpp
)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
