#ifndef SHADER_H
#define SHADER_H

#include <string>


class Shader
{
public:
    enum class Type
    {
        None, Vertex, Fragment, Geometry
    };

    Shader();
    Shader(Type type, const std::string& source);

    virtual ~Shader();

    bool Compile();
    void Destroy();

    bool IsCreated();

    Type GetType() const;
    unsigned GetId() const;


protected:
    bool CheckErrors();

private:
    bool _isCreated;
    unsigned _handler;

    Type _type;

    std::string _sourceCode;
};

#endif // SHADER_H
