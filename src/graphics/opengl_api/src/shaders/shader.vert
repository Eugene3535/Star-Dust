#version 450 core

layout (std140) uniform Matrices
{
    mat4 modelViewProjection;
};

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

out vec2 texCoords;

void main() 
{
    gl_Position = modelViewProjection * vec4(inPosition, 1.f);
    texCoords = inTexCoord;
}