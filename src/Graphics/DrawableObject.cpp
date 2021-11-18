#include "DrawableObject.h"

#include <GL/glew.h>
#include "ErrorHandle.h"

unsigned GetDrawMode(DrawMode type)
{
    switch (type) {
    case DrawMode::Triangles:
        return GL_TRIANGLES;
    case DrawMode::Quads:
        return GL_TRIANGLE_FAN;
    case DrawMode::Lines:
        return GL_LINES;
    case DrawMode::Points:
        return GL_POINTS;
    }
}


DrawableObject::DrawableObject(ShaderProgram *shaderProgram):
    _shaderProgram(shaderProgram),
    _drawMode(GL_TRIANGLES),
    _isCreated(false),
    _verticesFilling(0),
    _verticesCount(0),
    _vboHandler(0),
    _vaoHandler(0)
{

}

void DrawableObject::Create(const std::vector<float> &data)
{
    GLCall(glGenVertexArrays(1, &_vaoHandler));
    GLCall(glBindVertexArray(_vaoHandler));

    GLCall(glGenBuffers(1, &_vboHandler));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, _vboHandler));
    GLCall(glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(data[0]),
                 data.data(), GL_STATIC_DRAW));
    auto& layout = _shaderProgram->GetLayout();
    auto& layoutItems = _shaderProgram->GetLayout().GetLayoutItems();
    unsigned offset = 0;
    for(int i = 0; i < layoutItems.size(); ++i)
    {
        auto item = layoutItems[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i,
                              item.count,
                              ShadersLayout::GetOpenglType(item.type),
                              GL_FALSE,
                              layout.GetStride(),
                              reinterpret_cast<void*>(offset)));
        offset += item.size;
    }
    _verticesFilling = data.size() / layout.GetWidth();
    _verticesCount = _verticesFilling;
}

void DrawableObject::Destroy()
{
    GLCall(glDeleteVertexArrays(1, &_vaoHandler));
}

bool DrawableObject::IsCreated() const
{
    return _isCreated;
}

void DrawableObject::SetPrimitive(DrawMode drawType)
{
    _drawMode = GetDrawMode(drawType);
}

void DrawableObject::BindShader()
{
    _shaderProgram->Bind();
}

void DrawableObject::ReleaseShader()
{
    _shaderProgram->Release();
}

void DrawableObject::Render()
{
    GLCall(glBindVertexArray(_vaoHandler));
    GLCall(glDrawArrays(_drawMode, 0, _verticesFilling));
    GLCall(glBindVertexArray(0));
}

ShaderProgram *DrawableObject::GetShaderProgram()
{
    return _shaderProgram;
}
