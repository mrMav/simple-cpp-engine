
set(HEADERS
    ${HEADERS}
    VertexArray.h
    VertexBuffer.h
    IndexBuffer.h
    ShaderAttributes.h
    GLUtils.h
    Shader.h
)

set(SOURCE
    ${SOURCE}
    glad.c
    ShaderAttributes.cpp
)

target_sources(${PROJECT_NAME} 
    PUBLIC ${HEADERS}
    PUBLIC ${SOURCE}
)
