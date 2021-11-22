#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <vector>

#include "ShaderProgram.h"
#include "BaseObject.h"


enum class DrawMode
{
    Triangles, Quads, Lines, Points
};


class DrawableObject: public BaseObject
{
public:
    DrawableObject(ShaderProgram *shaderProgram);

    virtual void Create(const std::vector<float>& data);
    virtual void Destroy();

    bool IsCreated() const;

    void SetPrimitive(DrawMode drawType);

    void BindShader();
    void ReleaseShader();

    void Render();

    inline ShaderProgram* GetShaderProgram() { return _shaderProgram; }


private:
    ShaderProgram* _shaderProgram;

    bool _isCreated;

    unsigned _drawMode;
    unsigned _vaoHandler;
    unsigned _vboHandler;
    unsigned _verticesCount;
    unsigned _verticesFilling;

};

#endif // DRAWABLEOBJECT_H
