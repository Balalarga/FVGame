#include "ShadersLayout.h"

#include <GL/glew.h>


unsigned GetTypeSize(ShadersLayoutItem::Type type)
{
    switch(type)
    {
    case ShadersLayoutItem::Type::Float:
        return sizeof(float);
    case ShadersLayoutItem::Type::Int:
        return sizeof(int);
    case ShadersLayoutItem::Type::UnsignedInt:
        return sizeof(unsigned);
    default:
        return 0;
    }
}

ShadersLayoutItem::ShadersLayoutItem():
    count(0),
    type(Type::None),
    size(0)
{}

ShadersLayoutItem::ShadersLayoutItem(unsigned count, Type type)
{
    Setup(count, type);
}

void ShadersLayoutItem::Setup(unsigned newCount, Type newType)
{
    count = newCount;
    type = newType;
    size = count * GetTypeSize(type);
}

unsigned ShadersLayout::GetOpenglType(ShadersLayoutItem::Type type)
{
    switch(type)
    {
    case ShadersLayoutItem::Type::Float:
        return GL_FLOAT;
    case ShadersLayoutItem::Type::Int:
        return GL_INT;
    case ShadersLayoutItem::Type::UnsignedInt:
        return GL_UNSIGNED_INT;
    default:
        return GL_NONE;
    }
}

void ShadersLayout::Add(ShadersLayoutItem::Type type, unsigned count)
{
    _width += count;
    _stride += count * GetTypeSize(type);
    _layoutItems.push_back(ShadersLayoutItem(count, type));
}
