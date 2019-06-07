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

bool disk::hit(const ray& r, float tmin, float tmax, hit_record & rec) const
{
	if(r.direction().y()==0)
	{
			return false;		
	}
	
	float t=(y0-r.origin().y())/r.direction().y();
	if(t<tmin || t>tmax)
		return false;
		
	rec.t=t;
	rec.p = r.point_at_parameter(rec.t);
	if(rec.p.x()*rec.p.x()+rec.p.z()*rec.p.z()>=radius*radius)
		return false;

	rec.normal = vec3(0,1.0,0);
	if(dot(r.direction(), rec.normal) > 0)
		rec.normal = -rec.normal;		
	rec.mat_ptr = mat;

	float phi=atan2(rec.p.x(),rec.p.z());
	rec.u = 1-(phi + M_PI)/(2*M_PI);
	rec.v = sqrt(rec.p.x()*rec.p.x()+rec.p.z()*rec.p.z())/radius;

	return true;
}

#endif
