#version 460

in vec4 color_frag;

out vec4 color;

void main()
{
    color = color_frag;
}