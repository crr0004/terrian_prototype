#version 300 es
uniform mat4 project;
uniform mat4 modelview;
in vec3 vert;
void main()
{
   gl_Position = project * modelview * vec4(vert, 1.0);
}

