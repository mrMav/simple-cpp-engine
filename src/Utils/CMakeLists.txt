
set(HEADERS
    ${HEADERS}
    Utils.h
    Rectangle.h
)

set(SOURCE
    ${SOURCE}
    Utils.cpp
    Rectangle.cpp
)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
