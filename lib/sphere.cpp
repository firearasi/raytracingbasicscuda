#include "sphere.h"

inline void get_sphere_uv(const vec3&p, float&u, float& v)
{
    float phi=atan2(p.z(),p.x());
    float theta = asin(p.y());
    u = 1-(phi + M_PI)/(2*M_PI);
    u = fmod(u + 0.65, 1.0f);
    v = (theta+M_PI/2)/M_PI;
}

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record & rec) const
{
    vec3 oc = r.origin()-center;
    float a=dot(r.direction(), r.direction());
    float b=dot(oc, r.direction());
    float c=dot(oc,oc)-radius*radius;
    float discriminant = b*b-a*c;
    if(discriminant < 0)
        return false;
    float temp;
    float temp1 = (-b - sqrt(b*b - a*c))/a;
    if(temp1 <= t_max && temp1 >= t_min)
    {
        temp = temp1;
    }
    else
    {
        float temp2 = (-b + sqrt(b*b + a*c))/a;
        if(temp2 <= t_max && temp1 >= t_min)
        {
            temp = temp2;
        }
        else
        {
            return false;
        }
    }
    rec.t = temp;
	rec.p = r.point_at_parameter(rec.t);
    rec.normal = (rec.p - center) / radius;
    rec.mat_ptr = mat;
    get_sphere_uv(rec.normal,rec.u,rec.v);
    return true;
}

