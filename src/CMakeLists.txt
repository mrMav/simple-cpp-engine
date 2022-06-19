
set(HEADERS
    ${HEADERS}    
)

set(SOURCE
    ${SOURCE}
    main.cpp
    glad.c
)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
