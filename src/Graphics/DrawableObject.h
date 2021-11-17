#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "ShaderProgram.h"
#include <vector>

class DrawableObject
{
public:
    DrawableObject(ShaderProgram *shaderProgram);

    virtual void Create(unsigned verticesCount);
    virtual void Create(const std::vector<float>& vertices);
    virtual void Destroy();
    virtual void Clear();

    bool IsCreated() const;
    void SetPrimitive(unsigned primitive);
    void BindShader();
    void ReleaseShader();
    void Render();

    ShaderProgram* GetShaderProgram();

private:
    ShaderProgram* _shaderProgram;

    unsigned _vaoHandler;
    unsigned _vboHandler;
    unsigned _primitive;
    unsigned _verticesCount;
    unsigned _verticesFilling;

};

#endif // DRAWABLEOBJECT_H
