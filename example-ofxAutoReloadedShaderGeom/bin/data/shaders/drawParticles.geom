#version 330 core

uniform mat4 modelview;
uniform mat4 projection;

layout (points) in;
layout (line_strip, max_vertices = 2) out;

in vec4 vertColor[];
in vec4 position[];

out vec4 color;
  
void main() {
    vec4 eyeVector = modelview * (position[0] + vec4(-100.0, 0.0, 0.0, 0.0));
    gl_Position = projection * eyeVector;
    color = vec4(0.0, 0.0, 1.0, 1.0) ;
    EmitVertex();

    eyeVector = modelview * (position[0] + vec4(100.0, 0.0, 0.0, 0.0));
    gl_Position = projection * eyeVector;
    color = vec4(0.0, 1.0, 0.0, 1.0);
    EmitVertex();
    
    EndPrimitive();
}
