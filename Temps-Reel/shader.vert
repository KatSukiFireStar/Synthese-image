#version 460

layout(location=0) in vec2 position;
layout(location=1) in vec3 color;

out vec4 color_frag;

void main()
{
    gl_Position = vec4(position, 0, 1);
    gl_PointSize = 20;

    color_frag = vec4(color, 1);
}