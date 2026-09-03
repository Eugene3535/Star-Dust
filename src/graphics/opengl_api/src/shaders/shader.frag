#version 450 core

uniform sampler2D texture0;

in vec2 texCoords;
out vec4 FragColor;


void main() 
{
    vec4 texColor = texture(texture0, texCoords);

    if(texColor.a < 0.99f)
        discard;

    FragColor = texColor;
}
