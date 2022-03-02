#version 330

#define M_PI 3.1415926535897932384626433832795

uniform sampler2DRect particles0; // position
uniform sampler2DRect particles1; // velocity

uniform float maxSpeed;
uniform float width;
uniform float height;

in vec2 vertTexCoord;

layout(location = 0) out vec4 posOut;
layout(location = 1) out vec4 velOut;

float rand(vec2 A){
    const vec2 s = vec2(12.9898, 78.233);
    float tmp = dot(A,s);
    return fract(sin(tmp) * 43758.5453);
}

void main() {
    vec4 texel0 = texture(particles0, vertTexCoord);
    vec4 texel1 = texture(particles1, vertTexCoord);
    
    vec3 pos = texel0.xyz;
    float timeOfLife = texel0.w;
    vec3 vel = texel1.xyz;
    float maxVelocity = texel1.w;
    
    pos += vel * maxSpeed;
    
    if (pos.x < 0) {
        vel.x *= -1;
    }
    if (pos.x > width) {
        vel.x *= -1;
    }
    if (pos.y < 0) {
        vel.y *= -1;
    }
    if (pos.y > height) {
        vel.y *= -1;
    }
        
    posOut = vec4(pos, timeOfLife);
    velOut = vec4(vel, maxVelocity);
}
