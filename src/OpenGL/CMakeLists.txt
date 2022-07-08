
set(HEADERS
    ${HEADERS}
    VertexArray.h
    VertexBuffer.h
    IndexBuffer.h
    ShaderAttributes.h
    GLUtils.h
    Shader.h
    Texture2D.h
)

set(SOURCE
    ${SOURCE}
    ShaderAttributes.cpp
    Texture2D.cpp
)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
