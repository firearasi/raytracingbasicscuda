#ifndef AABBH
#define AABBH
#include "vec3.h"
#include "ray.h"
#include <iostream>
float ffmin(float a, float b);
float ffmax(float a, float b);

class aabb{
public:
	aabb(){}
	aabb(const vec3&a, const vec3&b) 
	{	
		_min.e[0]=ffmin(a.x(),b.x());
		_min.e[1]=ffmin(a.y(),b.y());
		_min.e[2]=ffmin(a.z(),b.z());
		_max.e[0]=ffmax(a.x(),b.x());
		_max.e[1]=ffmax(a.y(),b.y());
		_max.e[2]=ffmax(a.z(),b.z());
	 	
	}
	vec3 min() const {return _min;}
	vec3 max() const {return _max;}

	bool hit(const ray& r, float tmin, float tmax) const
	{
		for(int a=0;a<3;a++)
		{
			float invD = 1.0f/r.direction()[a];
			float t0 = (min()[a]-r.origin()[a]) * invD;
			float t1 = (max()[a]-r.origin()[a]) * invD;
			if(invD < 0.0f)
				std::swap(t0, t1);
			tmin = ffmax(tmin, t0);
			tmax = ffmin(tmax, t1);
			if(tmax <= tmin)
				return false;
		}
		return true;	
	}
	static aabb surrounding_box(aabb box0, aabb box1)
	{
		vec3 small(ffmin(box0.min().x(), box1.min().x()),
				   ffmin(box0.min().y(), box1.min().y()),
				   ffmin(box0.min().z(), box1.min().z()));
		vec3 large(ffmax(box0.max().x(), box1.max().x()),
	               ffmax(box0.max().y(), box1.max().y()),
	   			   ffmax(box0.max().z(), box1.max().z()));
	                                      				   
		return aabb(small, large);		   
	}
	void print()
	{
		std::cerr << "("<<_min.x()<<", "<<_min.y()<<", "<<_min.z()<<") - ";
		std::cerr << "("<<_max.x()<<", "<<_max.y()<<", "<<_max.z()<<")\n";
	
	}
	vec3 _min;
	vec3 _max;
};


#endif
