
set(HEADERS
    ${HEADERS}
    VertexBuffer.h
    IndexBuffer.h
    VertexPositionNormalTexture.h
    GLUtils.h
    Shader.h
)

set(SOURCE
    ${SOURCE}
    VertexBuffer.cpp
    IndexBuffer.cpp 
)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
