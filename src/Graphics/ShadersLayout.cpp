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

ShadersLayoutItem::ShadersLayoutItem(unsigned count, Type type):
    count(count),
    type(type),
    size(count * GetTypeSize(type))
{}

void ShadersLayout::Add(ShadersLayoutItem::Type type, unsigned count)
{
    _width += count;
    _stride += count * GetTypeSize(type);
    _layoutItems.push_back(ShadersLayoutItem(count, type));
}
