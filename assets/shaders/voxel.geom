#version 330

layout(points) in;
layout(triangle_strip, max_vertices = 24) out;

uniform mat4 MVP;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

in vec4 vColor[];
in float vVoxelSize[];
out vec4 gColor;
out vec3 gNorm;

void AddQuad(vec4 center, vec4 dy, vec4 dx)
{
    mat4 quad = mat4(center + (dx - dy),
                     center + (-dx - dy),
                     center + (dx + dy),
                     center + (-dx + dy));

    gl_Position = quad[0];
    EmitVertex();
    gl_Position = quad[1];
    EmitVertex();
    gl_Position = quad[2];
    EmitVertex();
    gl_Position = quad[3];
    EmitVertex();

    vec4 edge1 = quad[1]-quad[0];
    vec4 edge2 = quad[3]-quad[0];
    vec3 gNorm = normalize(cross(edge1.xyz, edge2.xyz));
    EndPrimitive();
}

void main()
{
    gColor = vColor[0];
    vec4 center = gl_in[0].gl_Position;

    vec4 dx = MVP[0]/2.0f * vVoxelSize[0];
    vec4 dy = MVP[1]/2.0f * vVoxelSize[0];
    vec4 dz = MVP[2]/2.0f * vVoxelSize[0];

    AddQuad(center + dx, dy, dz);
    AddQuad(center - dx, dz, dy);
    AddQuad(center + dy, dz, dx);
    AddQuad(center - dy, dx, dz);
    AddQuad(center + dz, dx, dy);
    AddQuad(center - dz, dy, dx);
}
