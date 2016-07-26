#version 300 es


uniform mat4 project;
uniform mat4 modelview;
in vec3 vert;
out vec4 pos;
void main()
{
   gl_Position = project * modelview * vec4(vert, 1.0);
   pos = vec4(vert,1.0);
}

