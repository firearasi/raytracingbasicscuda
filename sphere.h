#ifndef SPHEREH
#define SPHEREH
#include "hitable.h"
#include <stdlib.h>
#include <math.h>
#include "material.h"

inline void get_sphere_uv(const vec3&p, float&u, float& v)
{
	float phi=atan2(p.z(),p.x());
	float theta = asin(p.y());
	u = 1-(phi + M_PI)/(2*M_PI);
	u = fmod(u + 0.65, 1.0f);
	v = (theta+M_PI/2)/M_PI;
}

class sphere: public hitable
{
public:
	sphere() {}
	sphere(vec3 cen, float r, material *m): center(cen), radius(r), mat(m) {};
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

#endif
