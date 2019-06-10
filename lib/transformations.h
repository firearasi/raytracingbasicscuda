#ifndef TRANSFORMATIONSH
#define TRANSFORMATIONSH

#include "hitable.h"
#include "matrix.h"

class translate: public hitable
{
public:
	translate(vec3 o, hitable *_obj):offset(o), obj(_obj){}
	~translate(){free();}
	virtual void free();
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const ;
    virtual bool bounding_box(float t0, float t1, aabb& box) const;
	vec3 offset;
	hitable *obj;
};

// linear
class linear: public hitable
{
public:
	linear(mat3 _m, hitable *_obj):m(_m), obj(_obj)
	{
		invTranspose = m.invTranspose();
		inv=invTranspose.transpose();
	}
	~linear()
	{
		free();
	}
	virtual void free();
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const ;
    virtual bool bounding_box(float t0, float t1, aabb& box) const;
	mat3 m;
	mat3 inv;
	mat3 invTranspose;
	hitable *obj;
};


#endif
