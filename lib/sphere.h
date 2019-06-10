#ifndef SPHEREH
#define SPHEREH
#include "hitable.h"
#include <stdlib.h>
#include <math.h>
#include "material.h"

void get_sphere_uv(const vec3&p, float&u, float& v);

class sphere: public hitable
{
public:
	sphere() {}
	sphere(vec3 cen, float r, material *m): center(cen), radius(r), mat(m) {};
	virtual void free(){}
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record & rec) const;
	virtual bool bounding_box(float t0, float t1, aabb& box) const
	{
		box = aabb(center-vec3(radius,radius,radius), center+vec3(radius,radius,radius));
		return true;
	}
	vec3 center;
	float radius;
	material *mat;
};

#endif
