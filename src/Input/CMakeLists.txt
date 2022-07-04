
set(HEADERS
    ${HEADERS}
    Input.h
    KeyCodes.h
    GamePadButtonCodes.h
    MouseCodes.h
)

set(SOURCE
    ${SOURCE}
    Input.cpp
)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
