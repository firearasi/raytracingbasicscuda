#ifndef TRIANGLEH
#define TRIANGLEH
#include "hitable.h"
#include "uv.h"
#include "material.h"

void Barycentric(vec3 p, vec3 a, vec3 b, vec3 c, float &u, float &v, float &w);

class triangle: public hitable
{
public:
	triangle(vec3 _p0, vec3 _p1, vec3 p2, material *_m, 
		uv _uv0=uv(0.5,1), uv _uv1=uv(0,0), uv _uv2=uv(1,0));
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    virtual bool bounding_box(float t0, float t1, aabb& box) const;
    virtual void free() {}
	vec3 p0,p1,p2;
	material *m;
	uv uv0,uv1,uv2;
};


#endif
