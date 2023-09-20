/*This is your fragment shader for texture and normal mapping*/

#version 330 core

/*default camera matrices. do not modify.*/
layout (std140) uniform camera
{
    mat4 projection;    /*camera's projection matrix*/
    mat4 view;   		 /*camera's view matrix*/
    mat4 pvm;   		 /*camera's projection*view*model matrix*/
    mat4 ortho;   		 /*camera's ortho projection matrix*/
    vec4 position;   	 /*camera's position in world space*/
};

/*uniform variables*/
uniform float iTime;   				 ////time
uniform sampler2D tex_albedo;   		 ////texture color
uniform sampler2D tex_normal;   		 ////texture normal

in vec4 vtx_pos;
in vec4 vtx_color;
in vec4 vtx_nml;
in vec4 vtx_uv;
in vec4 vtx_tan;

/*output variables*/
out vec4 frag_color;

/*This part is the same as your previous assignment. Here we provide a default parameter set for the hard-coded lighting environment.
Feel free to change them.*/
const vec3 LightPosition = vec3(3, 1, 3);
const vec3 LightIntensity = vec3(20);
const vec3 LightColor = vec3(1.);
const vec3 ka = 0.1*vec3(1., 1., 1.);
const vec3 kd = 0.7*vec3(1., 1., 1.);
const vec3 ks = vec3(2.);
const float n = 400.0;

float pi = 3.14159265;
vec3 center = vec3(0., 0., 0.);

float compute_u()
{
    float phi = atan(vtx_pos.y, vtx_pos.x);
    float u = phi / (2 * pi) + .5;

    return u;
}

float compute_v()
{
    float theta = acos(vtx_pos.z / 1.);
    float v = (pi - theta) / pi;

    return v;
}

void main()
{   	 
    // compute uv coordinates
    vec2 computed_uv = vec2(compute_u(), compute_v());

    // sample the earth texture
    vec4 tex_col = texture(tex_albedo, computed_uv);

    frag_color = vec4(tex_col.rgb, 1);

    //frag_color = vec4(128.,91.,37.,255.)/255;
}	

