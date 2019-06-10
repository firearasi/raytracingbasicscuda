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


#endif
