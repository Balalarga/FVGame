#version 330

layout(location = 0) in vec3 iPosition;
layout(location = 1) in vec4 iColor;
layout(location = 2) in float iVoxelSize;

out vec4 vColor;
out float vVoxelSize;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main(void)
{
    mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
    gl_Position = MVP * vec4(iPosition, 1.0);
    vColor = iColor;
    vVoxelSize = iVoxelSize;
}
