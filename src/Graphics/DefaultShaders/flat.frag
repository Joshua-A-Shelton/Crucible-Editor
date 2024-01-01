#version 450 core
layout(location = 0) out vec4 fColor;
layout(set = 1, binding = 1) uniform sampler2D colorTex;
layout(location = 0) in struct { vec2 UV; } In;
void main()
{
    fColor = texture(colorTex, In.UV.st);
}