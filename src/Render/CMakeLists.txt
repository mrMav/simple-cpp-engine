
set(HEADERS
    ${HEADERS}
    Viewport.h
    Camera2D.h
    Spritebatch.h
    BitmapFont.h
)

set(SOURCE
    ${SOURCE}
    Camera2D.cpp
    Spritebatch.cpp
    BitmapFont.cpp
)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
