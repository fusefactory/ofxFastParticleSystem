#version 330

uniform mat4 projection;
uniform mat4 modelview;

in vec4 position;
in vec2 texcoord;

out vec2 vertTexCoord;

void main() {
    gl_Position = position;
    vertTexCoord = texcoord;
}
