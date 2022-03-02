#version 330

uniform sampler2DRect particles0; // position

uniform mat4 projection;
uniform mat4 modelview;

in vec2 texcoord;

out vec4 vertColor;
out vec4 position;

void main()
{
    vec4 texel0 = texture(particles0, texcoord);
    vec4 pos = vec4(texel0.xyz, 1);
    
    vec4 eyePos = modelview * pos;
    gl_Position = projection * eyePos;
    
    position = pos;
        
    vec4 color = vec4(1.0, 1.0, 1.0, 0.2);
    vertColor = color;
}
