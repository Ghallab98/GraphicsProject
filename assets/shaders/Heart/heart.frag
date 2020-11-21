#version 330 core

uniform vec2 mouseCoord;
out vec4 frag_color;
#define PI 3.1415926535897932384626433832795

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


void main() {
    vec2 position = gl_FragCoord.xy;
    vec2 heartCenter = vec2 (mouseCoord.x,720-mouseCoord.y);
    vec3 triangle1 = vec3(heartCenter.x,heartCenter.y-50,0);
    vec3 triangle2 = vec3(heartCenter.x+ 100,heartCenter.y + 90,0);
    vec3 triangle3 = vec3(heartCenter.x -100 ,heartCenter.y +90,0);
    if (PointInTriangle(position,triangle1,triangle2,triangle3 ))
    {
        frag_color = vec4(1.0,0.0,0.0,1.0);

    }
    vec2 g_Center1 = vec2(heartCenter.x-48,heartCenter.y+90);
    
    float G1 = distance(position,g_Center1);

    if(G1 <= 52 && position.y > heartCenter.y +90 )
    {
        frag_color = vec4(1.0,.0,.0,1.0);
    }
    vec2 g_Center2 = vec2(heartCenter.x+48,heartCenter.y+90);
    
    float G2 = distance(position,g_Center2);

    if(G2 <= 52 && position.y > heartCenter.y +90 )
    {
        frag_color = vec4(1.0,.0,.0,1.0);
    }
    
}

/*float heart(float theta) {
	return 2. - 2.*sin(theta) + sqrt(abs(cos(theta)))*sin(theta)/(1.4 + sin(theta));
}
void main() {

 // Generate world UVs

    vec2 uv =  50/gl_FragCoord.xy;
    uv = (uv - 0.5);
    float aspect = gl_FragCoord.x / gl_FragCoord.y;
    uv.x *= aspect;
    uv.y -= 0.01;    // Displace the uv to center the heart
    
    
    float a = atan(uv.x,-uv.y) / PI;     // angle
    float r = length(vec2(uv.x,uv.y));  // radius
    
    float global_scale = 0.25;
    float d = global_scale *
                (0.2
               + 0.6 * abs(a)                     // main
               - (0.1) * cos(abs(a) * PI * 2.0)     // wide
               + (0.05) * pow(abs(a), 20.0)         // bottom
                );

    vec3 heart_color = vec3(1.0, 0.0, 0.15);
    vec3 background = vec3(0.0, 0.0, 0.0);
    float is_heart = smoothstep(d, d+fwidth(r)*2.0, r);
    vec3 color = mix(heart_color, background, is_heart);

    // Output to screen
    frag_color = vec4(color,1.0);
}
*/
/// ayman we hussein 

/*vec4 frag_color;
    float x= gl_FragCoord.x +640;
    float y= gl_FragCoord.y + 360;
    float eqn = ((x*x) + (y*y) - 1);
    float neweqn = (eqn*eqn*eqn) - (x*x) * (y*y*y);
    //float eqn = pow(xxx, 3.0) - (pow(gl_FragCoord.x, 2.0) * pow(gl_FragCoord.y, 3.0));

    if(neweqn > 0){
        frag_color=vec4(0.0,0.0,0.0,1.0);
    }
    else{
        frag_color=vec4(0.0,0.0,1.0,1.0);
    }
    */