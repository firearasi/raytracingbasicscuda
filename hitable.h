#ifndef HITABLEH
#define HITABLEH

#include "ray.h"
#include "aabb.h"

class material;
struct hit_record
{
	float t;
	vec3 p;
	vec3 normal;
	material *mat_ptr;
	float u,v;
};

class hitable
{
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
	virtual bool bounding_box(float t0, float t1, aabb& box) const = 0;
};

class flip_normals: public hitable
{
public:
	flip_normals(hitable *o): original(o){}
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const
    {
		bool bHit = original->hit(r, t_min, t_max, rec);
		rec.normal = -rec.normal;
		return bHit;
    }
    virtual bool bounding_box(float t0, float t1, aabb& box) const
    {
    	bool bBound = original->bounding_box(t0,t1,box);
    	return bBound;
    }
        
	hitable *original;
};
#endif
