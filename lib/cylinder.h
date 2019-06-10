#ifndef CYLINDERH
#define CYLINDERH
#include "hitable.h"
#include <stdlib.h>
#include <math.h>
#include "material.h"
#include "disk.h"
#include "bvh_node.h"
#include "hitable.h"

class cylinder: public hitable
{
public:
	cylinder() {}
	cylinder(float r, float _ymin, float _ymax, material *m): radius(r), ymin(_ymin), ymax(_ymax),mat(m) {};
	virtual void free(){}
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record & rec) const;
	virtual bool bounding_box(float t0, float t1, aabb& box) const
	{
		box = aabb(vec3(-radius,ymin,-radius), vec3(radius, ymax, radius));
		return true;
	}
	float radius;
	float ymin, ymax;
	material *mat;
};


class solid_cylinder: public hitable
{
public:
	
	solid_cylinder(float r, float _ymin, float _ymax, material *m): radius(r), ymin(_ymin), ymax(_ymax),mat(m) 
	{
		cyl = new cylinder(r, _ymin, _ymax, m);
		upper = new disk(r, ymax, m);
		lower = new flip_normals(new disk(r, ymin, m));
		hitable *list[3] = {cyl, upper, lower};
		node = new bvh_node(list,3);
		
	}
	~solid_cylinder(){free();}
	virtual void free();
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record & rec) const;
	virtual bool bounding_box(float t0, float t1, aabb& box) const
	{
		node->bounding_box(t0,t1,box);
		//box = aabb(vec3(-radius,ymin,-radius), vec3(radius, ymax, radius));
		return true;
	}
	float radius;
	float ymin, ymax;
	material *mat;
	cylinder* cyl;
	hitable *upper, *lower;
	bvh_node* node;
};

#endif
