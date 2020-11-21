#version 330 core

uniform vec2 mouseCoord;
out vec4 frag_color;

#define PI 3.1415926535897932384626433832795

/**
UTILS
*/
float sign (vec2 p1, vec3 p2, vec3 p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle (vec2 pt, vec3 v1, vec3 v2, vec3 v3)
{
    float d1, d2, d3;
    bool has_neg, has_pos;

    d1 = sign(pt, v1, v2);
    d2 = sign(pt, v2, v3);
    d3 = sign(pt, v3, v1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

void main(){
    vec2 position = gl_FragCoord.xy;

    vec2 circleCenter = vec2(mouseCoord.x,720- mouseCoord.y);

    float circle = distance(position,circleCenter);

    if (circle <= 100)
    {
        frag_color = vec4(1.0,1.0,0.0,1.0);
    }
    else
    {
        frag_color = vec4(.0,.0,.0,1.0);
    }
    vec2 eyeCenter = vec2(circleCenter.x +15.0, circleCenter.y+55.0);
    float eye = distance(position,eyeCenter);

    if (eye <= 10)
    {
        frag_color = vec4(0.0,0.0,0.0,1.0);
    }
    vec3 triangle1 = vec3(circleCenter.x,circleCenter.y,0);
    vec3 triangle2 = vec3(circleCenter.x+ 100,circleCenter.y - 90,0);
    vec3 triangle3 = vec3(circleCenter.x +100 ,circleCenter.y +90,0);
    if (PointInTriangle(position,triangle1,triangle2,triangle3 )&& circle <= 100)
    {
        frag_color = vec4(0.0,0.0,0.0,1.0);

    }
}