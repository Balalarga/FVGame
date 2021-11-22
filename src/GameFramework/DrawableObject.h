#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "Graphics/OpenglDrawable.h"
#include "BaseObject.h"


class DrawableObject: public BaseObject, public OpenglDrawable
{
public:
    DrawableObject(ShaderProgram *shaderProgram);

};

#endif // DRAWABLEOBJECT_H
