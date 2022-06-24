
set(HEADERS
    ${HEADERS}
    VertexArray.h
    VertexBuffer.h
    IndexBuffer.h
    VertexPositionNormalTexture.h
    ShaderAttributes.h
    GLUtils.h
    Shader.h
)

set(SOURCE
    ${SOURCE}
)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
