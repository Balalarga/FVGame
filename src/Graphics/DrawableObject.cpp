#include "DrawableObject.h"

#include <GL/glew.h>

DrawableObject::DrawableObject(ShaderProgram *shaderProgram):
    _shaderProgram(shaderProgram),
    _drawType(DrawType::Triangles),
    _isCreated(false),
    _verticesFilling(0),
    _verticesCount(0),
    _vboHandler(0),
    _vaoHandler(0)
{

}

void DrawableObject::Create(const std::vector<float> &data)
{
    glGenVertexArrays(1, &_vaoHandler);
    glBindVertexArray(_vaoHandler);

    glGenBuffers(1, &_vboHandler);
    glBindBuffer(GL_ARRAY_BUFFER, _vboHandler);
    glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(data[0]),
                 data.data(), GL_STATIC_DRAW);
    auto& layout = _shaderProgram->GetLayout();
    auto& layoutItems = _shaderProgram->GetLayout().GetLayoutItems();
    unsigned offset = 0;
    for(int i = 0; i < layoutItems.size(); ++i)
    {
        auto item = layoutItems[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i,
                              item.count,
                              ShadersLayout::GetOpenglType(item.type),
                              GL_FALSE,
                              layout.GetStride(),
                              reinterpret_cast<void*>(offset));
        offset += item.size;
    }
}

void DrawableObject::Destroy()
{
    glDeleteVertexArrays(1, &_vaoHandler);
}

bool DrawableObject::IsCreated() const
{
    return _isCreated;
}

void DrawableObject::SetPrimitive(DrawType drawType)
{

}

void DrawableObject::BindShader()
{

}

void DrawableObject::ReleaseShader()
{

}

void DrawableObject::Render()
{

}

ShaderProgram *DrawableObject::GetShaderProgram()
{
    return _shaderProgram;
}
