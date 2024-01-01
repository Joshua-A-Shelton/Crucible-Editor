#version 450 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

layout(set = 0, binding = 0) uniform globals
{
    mat4 camera;
}Globals;
layout(set = 1, binding = 0) uniform locals
{
    mat4 position;
}Locals;


layout(location = 0) out struct { vec2 UV; } Out;


void main()
{
    gl_Position = Globals.camera * vec4(position,1);
    Out.UV = uv;
}