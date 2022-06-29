
set(HEADERS
    ${HEADERS}
    StackAllocator.h
)

set(SOURCE
    ${SOURCE}
    StackAllocator.cpp
)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
