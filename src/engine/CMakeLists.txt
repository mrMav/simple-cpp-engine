
set(HEADERS
    ${HEADERS}
    game.h
    spritebatch.h
    engine.h
)

set(SOURCE
    ${SOURCE}
    game.cpp
    spritebatch.cpp
)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
