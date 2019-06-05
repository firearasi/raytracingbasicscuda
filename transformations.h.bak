#ifndef TRANSFORMATIONSH
#define TRANSFORMATIONSH

#include "hitable.h"
#include "matrix.h"

class translate: public hitable
{
public:
	translate(vec3 o, hitable *_obj):offset(o), obj(_obj){}
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const ;
    virtual bool bounding_box(float t0, float t1, aabb& box) const;
	vec3 offset;
	hitable *obj;
};

bool translate::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	ray r_tl(r.origin()-offset, r.direction());
	bool bHit = obj->hit(r_tl, t_min, t_max, rec);
	if(bHit)
	{
		rec.p += offset;
	}
	return bHit;
}

bool translate::bounding_box(float t0, float t1, aabb& box) const
{
	bool bBound = obj->bounding_box(t0, t1, box);
	if(bBound)
	{
		box._min += offset;
		box._max += offset;
	}
	return bBound;
}

// orthogonal
class orthogonal: public hitable
{
public:
	// here o must be an onthogonal matrix!
	orthogonal(mat3 _o, hitable *_obj):o(_o), obj(_obj){inv=o.transpose();}
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const ;
    virtual bool bounding_box(float t0, float t1, aabb& box) const;
	mat3 o;
	mat3 inv;
	hitable *obj;
};

bool orthogonal::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	ray r_inv=inv*r;
	bool bHit = obj->hit(r_inv, t_min, t_max, rec);
	if(bHit)
	{
		rec.p = o * rec.p;

		// Since o is orthogonal, tr(inv(o)) happens to be o
		rec.normal = o * rec.normal;
	}
	return bHit;
}

bool orthogonal::bounding_box(float t0, float t1, aabb& box) const
{
	bool bBound = obj->bounding_box(t0, t1, box);
	if(bBound)
	{
		box=o*box;
	}
	return bBound;
}


#endif
