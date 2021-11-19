 #version 330

layout(location = 0) in vec3 iPosition;
layout(location = 1) in vec4 iColor;

out vec4 vColor;

uniform mat4 worldToView;


void main(void)
{
    gl_Position = vec4(iPosition, 1.0);
    vColor = iColor;
}