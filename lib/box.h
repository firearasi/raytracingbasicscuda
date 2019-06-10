#ifndef BOXH
#define BOXH
#include "ray.h"
#include "hitable.h"
#include "aabb.h"
#include "aarect.h"
#include "bvh_node.h"
class box: public hitable
{
public:
	box(const vec3& p, const vec3& q, material *m);
	~box(){free();}
	virtual void free();
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    virtual bool bounding_box(float t0, float t1, aabb& box) const;
	aabb bb;
	hitable *front, *back, *top, *bottom, *left, *right;
	bvh_node *node;
	vec3 _min;
	vec3 _max;
	material *mat;
};

#endif
