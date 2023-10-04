set(HEADERS
    ${HEADERS}
    FrameAnimation.h
)

set(SOURCE
    ${SOURCE}
    FrameAnimation.cpp
)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
