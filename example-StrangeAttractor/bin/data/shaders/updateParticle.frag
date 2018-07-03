#version 330

// ping pong inputs
uniform sampler2DRect particles0;
uniform sampler2DRect particles1;

uniform float timestep;

in vec2 texCoordVarying;

layout(location = 0) out vec4 posOut;
layout(location = 1) out vec4 velOut;

float dx = 0.0;
float dy = 0.0;
float dz = 0.0;

void main(){
    int id = int(texCoordVarying.s) + int(texCoordVarying.t)*int(textureSize(particles0).x);
    vec3 pos = texture(particles0, texCoordVarying.st).xyz;
    vec3 vel = texture(particles1, texCoordVarying.st).xyz;
    vel = vec3(0, 0, 0);
    
    // get the previous position
    float x = pos.x;
    float y = pos.y;
    float z = pos.z;
    
    // Dedras
    float a = 3;
    float b = 2.7;
    float c = 1.7;
    float d = 2;
    float e = 9;
    
    dx = (y- a*x +b*y*z) * timestep;
    dy = (c*y -x*z +z) * timestep;
    dz = (d*x*y - e*z) * timestep;
    
    vec3 attractorForce = vec3(dx, dy, dz) ;
    pos += attractorForce;
    
    posOut = vec4(pos, id);
    velOut = vec4(vel, 0.0);
}
