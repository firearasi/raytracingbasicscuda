#ifndef UTILSH
#define UTILSH
#include <math.h>
#include "ray.h"

float hit_sphere(const vec3& center, float radius, const ray& r)
{
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(r.direction(), oc);
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b*b - 4.0 * a * c;
	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		return (-b-sqrt(discriminant))/(2.0*a);
	} 
}


#endif
