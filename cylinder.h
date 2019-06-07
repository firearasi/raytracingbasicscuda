#ifndef CYLINDERH
#define CYLINDERH
#include "hitable.h"
#include <stdlib.h>
#include <math.h>
#include "material.h"
#include "disk.h"
#include "bvh_node.h"
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

bool cylinder::hit(const ray& r, float tmin, float tmax, hit_record & rec) const
{
	if(r.direction().x()==0 && r.direction().z()==0)
	{
			return false;		
	}
	
	float a,b,c;
	a=r.direction().x()*r.direction().x()+r.direction().z()*r.direction().z();
	b=r.direction().x()*r.origin().x()+r.direction().z()*r.origin().z();
	c=r.origin().x()*r.origin().x()+r.origin().z()*r.origin().z()-radius*radius;

	float det=b*b-a*c;
	if(det < 0)
		return false;
	float t1 = (-b-sqrt(det))/a;
	float y1 = r.origin().y() + t1 * r.direction().y();
	if(t1 >= tmin && t1 <= tmax && y1 >= ymin && y1 <= ymax)
	{
		rec.t=t1;
	}
	else
	{
		float t2 = (-b+sqrt(det))/a;
		float y2 = r.origin().y() + t2 * r.direction().y();
	    if(t2 >= tmin && t2 <= tmax && y2 >= ymin && y2 <= ymax)
  		{
       	 rec.t=t2;
	    }
		else
			return false;
	}
	
	
	rec.p = r.point_at_parameter(rec.t);

	rec.normal = rec.p/radius;
	rec.normal.e[1] = 0;
	//Checking whether the intersection is from within or without
	if(dot(rec.normal, r.direction()) > 0)
		rec.normal = -rec.normal;		
		
	rec.mat_ptr = mat;

	float phi=atan2(rec.p.x(),rec.p.z());
	rec.u = 1-(phi + M_PI)/(2*M_PI);
	rec.v = (rec.p.y()-ymin)/(ymax-ymin);

	return true;
}

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

void solid_cylinder::free()
{
	if(node)
		delete node;
}

bool solid_cylinder::hit(const ray& r, float tmin, float tmax, hit_record & rec) const
{
	return node->hit(r, tmin, tmax, rec);
}

#endif
