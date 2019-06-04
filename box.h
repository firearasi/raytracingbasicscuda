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
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    virtual bool bounding_box(float t0, float t1, aabb& box) const;
	aabb bb;
	hitable *front, *back, *top, *bottom, *left, *right;
	bvh_node *node;
	vec3 _min;
	vec3 _max;
	material *mat;
};

box::box(const vec3& p, const vec3& q, material *m):bb(p,q), mat(m)
{
	_min = bb.min();
	_max = bb.max();

	int a=_min.x(), b = _min.y(), c = _min.z(), d = _max.x(), e = _max.y(), f = _max.z();
	front = new xy_rect(a,d,b,e,f,m);
	back = new flip_normals(new xy_rect(a,d,b,e,c,m));
	top = new xz_rect(a,d,c,f,e,m);
	bottom = new flip_normals(new xz_rect(a,d,c,f,b,m));
	left = new flip_normals(new yz_rect(b,e,c,f,a,m));
	right = new yz_rect(b,e,c,f,d,m);
	hitable *list[6];
	list[0] = front;
	list[1] = back;
	list[2] = top;
	list[3] = bottom;
	list[4] = left;
	list[5] = right;
	node = new bvh_node(list, 6, 0, 0);
}

bool box::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	bool bHit = node->hit(r, t_min, t_max, rec);
	rec.mat_ptr = mat;
	return bHit;
}

bool box::bounding_box(float t0, float t1, aabb& box) const
{
	box = bb;
	return true;
}
#endif
