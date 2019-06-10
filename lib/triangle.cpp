#include "triangle.h"

void Barycentric(vec3 p, vec3 a, vec3 b, vec3 c, float &u, float &v, float &w)
{
    vec3 v0 = b - a, v1 = c - a, v2 = p - a;
    float d00 = dot(v0, v0);
    float d01 = dot(v0, v1);
    float d11 = dot(v1, v1);
    float d20 = dot(v2, v0);
    float d21 = dot(v2, v1);
    float denom = d00 * d11 - d01 * d01;
    v = (d11 * d20 - d01 * d21) / denom;
    w = (d00 * d21 - d01 * d20) / denom;
    u = 1.0f - v - w;
}

triangle::triangle(vec3 _p0, vec3 _p1, vec3 _p2, material *_m,
    uv _uv0, uv _uv1, uv _uv2):p0(_p0),p1(_p1),p2(_p2),m(_m),uv0(_uv0),uv1(_uv1),uv2(_uv2)
{
}

bool triangle::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{

    vec3 normal = unit_vector(cross(p1-p0,p2-p0));
    rec.normal = normal;
    if(dot(r.direction(),normal)==0)
        return false;
    float t = dot(p0-r.origin(), normal)/dot(r.direction(),normal);
    if(t<t_min || t>t_max)
        return false;
    rec.t=t;
    rec.mat_ptr=m;
    rec.p=r.point_at_parameter(t);

    float u,v,w;
    Barycentric(rec.p, p0,p1,p2,u,v,w);
    if(u<0 || v<0 || w<0)
        return false;
    uv uv_point = u*uv0+v*uv1*w*uv2;
    rec.u=uv_point.u();
    rec.v=uv_point.v(); 

    return true;
}

bool triangle::bounding_box(float t0, float t1, aabb& box) const
{
    box=aabb::surrounding_box(aabb(p0,p1),aabb(p0,p2));
    return true;
}

