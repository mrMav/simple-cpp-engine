
set(HEADERS
    ${HEADERS}
    Spritebatch.h
)

set(SOURCE
    ${SOURCE}
    Spritebatch.cpp
)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
