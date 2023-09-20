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

/*input variables*/
in vec4 vtx_pos;
in vec4 vtx_color;
in vec4 vtx_nml;
in vec4 vtx_uv;
in vec4 vtx_tan;

out vec4 frag_color;

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
    // compute uv coordinates to sample both texture files (color and normal)
    vec2 computed_uv = vtx_uv.xy;
    vec4 tex_col = normalize(texture(tex_albedo, computed_uv));
    vec4 tex_nml = normalize(texture(tex_normal, computed_uv) * 2.0 - 1.0);

    // compute TNB matrix
    vec3 N = normalize(vtx_nml.xyz);
    vec3 T = normalize(vtx_tan.xyz);
    vec3 B = normalize(cross(N, T));
    mat3 mat = mat3(T, B, N);

    // tangent-to-world space tranformation
    vec3 tex_nml_transformed = normalize(mat * tex_nml.xyz);

    // calculate values for lambertian lighting
    vec3 l = normalize(LightPosition - vtx_pos.xyz);
    float l_dot_n = dot(l, tex_nml_transformed.xyz);
    float diff = max(0.f, l_dot_n);

    // synthesize different color models
    vec3 amb_c = vec3(ka * LightColor);
    vec3 diff_c = vec3(kd * LightColor * diff * tex_col.rgb);
    vec3 col = amb_c + diff_c;

    frag_color = vec4(tex_col.rgb, 1);
    //frag_color = vec4(.3f, .7f, .1f, 1.f);
}	

