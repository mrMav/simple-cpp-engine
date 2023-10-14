set(HEADERS
    ${HEADERS}
    FrameAnimation.h
    TileSet.h

)

set(SOURCE
    ${SOURCE}
    FrameAnimation.cpp
    TileSet.cpp

)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
