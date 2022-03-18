#pragma once

#include <GL/glew.h>

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"


#define ASSERT(x) \
    if (!(x)) __debugbreak();//wont work with other compilers you need to find the function for others
#define GLCall(x)   \
    GLClearError(); \
    x;              \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();

bool GLLogCall(const char *function, const char *file, int line);

class Renderer {
public:
    void clear();
    void draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
};