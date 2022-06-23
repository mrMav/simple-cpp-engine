
set(HEADERS
    ${HEADERS}
    game.h
    Spritebatch.h
    engine.h
)

set(SOURCE
    ${SOURCE}
    game.cpp
    Spritebatch.cpp
)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
