
set(HEADERS
    ${HEADERS}
    Utils.h
)

set(SOURCE
    ${SOURCE}
    Utils.cpp
)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
