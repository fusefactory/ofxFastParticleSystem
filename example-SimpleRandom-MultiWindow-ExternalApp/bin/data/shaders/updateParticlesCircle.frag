#version 330

#define M_PI 3.1415926535897932384626433832795

uniform sampler2DRect particles0; // position
uniform sampler2DRect particles1; // velocity

uniform vec2 center;
uniform float radius;
uniform float centerStiffness;
uniform float maxSpeed;

in vec2 vertTexCoord;

layout(location = 0) out vec4 posOut;
layout(location = 1) out vec4 velOut;

float rand(vec2 A){
    const vec2 s = vec2(12.9898, 78.233);
    float tmp = dot(A,s);
    return fract(sin(tmp) * 43758.5453);
}

vec3 limit(vec3 v, float m){
    float lengthSquared = v.x * v.x + v.y * v.y + v.z * v.z;
    if( lengthSquared > m * m && lengthSquared > 0.0 ) {
        float ls = sqrt(lengthSquared);
        float ratio = m / ls;
        v *= ratio;
    }
    return v;
}

void main() {
    vec4 texel0 = texture(particles0, vertTexCoord);
    vec4 texel1 = texture(particles1, vertTexCoord);
    
    vec3 pos = texel0.xyz;
    float timeOfLife = texel0.w;
    vec3 vel = texel1.xyz;
    float maxVelocity = texel1.w;
    
    // center spring
    vec3 dir = pos - vec3(center.x, center.y, 0);
    float dist = length(dir);
    float f = (radius - dist) * centerStiffness;
    dir = normalize(dir);
    vec3 forces = dir * f;
    
    vel += forces;
    vel = limit(vel, maxSpeed);
    pos += vel;
    vel *= 0.96;
    
    posOut = vec4(pos, timeOfLife);
    velOut = vec4(vel, maxVelocity);
}
