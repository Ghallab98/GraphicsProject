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


/**
Main
*/
void main() {
    
    vec2 position = gl_FragCoord.xy;
    vec2 g_Center = vec2(mouseCoord.x,720-mouseCoord.y);
    
    float G = distance(position,g_Center);

    if(G <= 100 && G >= 70 )
    {
        frag_color = vec4(1.0,1.0,1.0,1.0);
    }
    else
    {
        frag_color = vec4(0.0,0.0,0.0,1.0);
    }
    vec3 triangle1 = vec3(g_Center.x,g_Center.y,0);
    vec3 triangle2 = vec3(g_Center.x+ 100,g_Center.y - 90,0);
    vec3 triangle3 = vec3(g_Center.x +100 ,g_Center.y +90,0);
    if (PointInTriangle(position,triangle1,triangle2,triangle3 )&& G <= 100)
    {
        frag_color = vec4(0.0,0.0,0.0,1.0);

    }
    vec3 rect1 = vec3(g_Center.x+50,g_Center.y-15,0);
    vec3 rect2 = vec3(g_Center.x+ 75,g_Center.y-12,0);
    vec3 rect3 = vec3(g_Center.x + 50 ,g_Center.y -65,0);
    vec3 rect4 =vec3(g_Center.x + 75,g_Center.y - 67,0);
    if (position.x < rect2.x && position.x > rect1.x && position.y < rect1.y && position.y > rect4.y)
    {
        frag_color = vec4(1.0,1.0,1.0,1.0);

    }
}
