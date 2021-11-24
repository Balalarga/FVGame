#version 330

in vec4 gColor;
in vec3 gNorm;

out vec4 fFragColor;

void main(void)
{
    fFragColor = gColor;
}
