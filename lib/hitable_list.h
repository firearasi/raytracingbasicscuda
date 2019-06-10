#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"
#include "sphere.h"

class hitable_list: public hitable
{
public:
	hitable_list() {}
	~hitable_list() {free();}
	hitable_list(hitable **l, int n) {list=l; list_size = n;}
	virtual void free();
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record &rec) const;
	virtual bool bounding_box(float t0,float t1, aabb& box) const;
	hitable **list;
	int list_size;
};

#endif
