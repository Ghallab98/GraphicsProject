#version 330 core

uniform vec2 mouseCoord;
out vec4 frag_color;

#define PI 3.1415926535897932384626433832795

/**
UTILS
*/
void main(){
    vec2 position = gl_FragCoord.xy;
    vec2 faceCenter = vec2(mouseCoord.x,720- mouseCoord.y);
    vec2 eye1Center = vec2(faceCenter.x-40,faceCenter.y+40);
    vec2 eye2Center = vec2(faceCenter.x +40,faceCenter.y+40);
    
    float eye1 = distance(position,eye1Center);
    float eye2 = distance(position,eye2Center);
    float face = distance(position,faceCenter);
    if(face <= 100 )
    {
        frag_color = vec4(1.0,1.0,0.0,1.0);
    }
    else
    {
        frag_color = vec4(0.0,0.0,0.0,1.0);
    }
    if(face <=75 && face >=65 && position.y < (720-mouseCoord.y))
    {
        frag_color = vec4(0.0,0.0,0.0,1.0);
    }
    if(eye1 <= 10 )
    {
        frag_color = vec4(0.0,0.0,0.0,1.0);
    }
    if( eye2 <= 10)
    {
        frag_color = vec4(0.0,0.0,0.0,1.0);
    }
}