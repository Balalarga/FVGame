#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "ShaderProgram.h"
#include <vector>

enum class DrawType
{
    Triangles, Quads, Lines, Points
};

class DrawableObject
{
public:
    DrawableObject(ShaderProgram *shaderProgram);

    virtual void Create(const std::vector<float>& data);

    virtual void Destroy();

    bool IsCreated() const;

    void SetPrimitive(DrawType drawType);

    void BindShader();
    void ReleaseShader();

    void Render();

    ShaderProgram* GetShaderProgram();

private:
    ShaderProgram* _shaderProgram;

    DrawType _drawType;

    bool _isCreated;

    unsigned _vaoHandler;
    unsigned _vboHandler;
    unsigned _verticesCount;
    unsigned _verticesFilling;

};

#endif // DRAWABLEOBJECT_H
