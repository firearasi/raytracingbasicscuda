#ifndef DISKH
#define DISKH
#include "hitable.h"
#include <stdlib.h>
#include <math.h>
#include "material.h"


class disk: public hitable
{
public:
	disk() {}
	disk(float r, float _y, material *m): radius(r), y0(_y) ,mat(m) {};
	virtual void free(){}
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record & rec) const;
	virtual bool bounding_box(float t0, float t1, aabb& box) const
	{
		box = aabb(vec3(-radius-0.01,y0,-radius-0.01), vec3(radius+0.01, y0, radius+0.01));
		return true;
	}
	float radius;
	float y0;
	material *mat;
};

#endif
