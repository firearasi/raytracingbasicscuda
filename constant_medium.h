#ifndef CONSTANTMEDIUMH
#define CONSTANTMEDIUMH

#include "hitable.h"
#include "material.h"
#include <float.h>
#include <stdlib.h>

class constant_medium: public hitable
{
public:
    constant_medium(hitable *b, float d, texture *a): boundary(b), density(d)
    {phase_function=new isotropic(a);}
    ~constant_medium(){free();}
	virtual void free();
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, aabb &bx) const;
	hitable *boundary;
	float density;
	material *phase_function;
};

void constant_medium::free()
{
	if(boundary)
		delete boundary;
}

bool constant_medium::hit(const ray& r, float tmin, float tmax, hit_record& rec) const
{
	bool db=false;
	hit_record rec1,rec2;
	if(boundary->hit(r, -FLT_MAX, FLT_MAX,rec1))
	{
		if(boundary->hit(r,rec1.t+0.0001,FLT_MAX,rec2))
		{
			if(rec1.t<tmin)
				rec1.t=tmin;
			if(rec2.t>tmax)	
				rec2.t=tmax;
			if(rec1.t>rec2.t)
				return false;
			if(rec1.t<0)
				rec1.t=0;
			float distance_inside_boundary=(rec2.t-rec1.t)*r.direction().length();
			float hit_distance = -(1/density)*log(drand48());
			if(hit_distance < distance_inside_boundary)
			{
				rec.t=rec1.t+hit_distance/r.direction().length();
				rec.p=r.point_at_parameter(rec.t);
				rec.normal=vec3(1,0,0); //whatever
				rec.mat_ptr=phase_function;
				return true;
			}
		}
	}		
	return false;
}

bool constant_medium::bounding_box(float t0, float t1, aabb& box) const
{
	return boundary->bounding_box(t0, t1, box);
}


#endif
