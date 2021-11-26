 #version 330

layout(location = 0) in vec3 iPosition;
layout(location = 1) in vec4 iColor;

out vec4 vColor;

uniform mat4 MVP;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;


void main(void)
{
    gl_Position = MVP * vec4(iPosition, 1.0);
    vColor = iColor;
}
