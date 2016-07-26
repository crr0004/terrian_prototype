#version 300 es


precision highp float;
in vec4 pos;
out vec4 color;
void main()
{
    color = vec4(0.2, pos.y /3.0, 1.0, 1.0);
}
