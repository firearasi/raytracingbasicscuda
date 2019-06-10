#ifndef MATERIALH
#define MATERIALH
#include "ray.h"
#include "vec3.h"
#include "sphere.h"
#include "texture.h"
#include <math.h>
#include <string>

float schlick(float cosine, float ref_idx);

class material
{
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
	virtual vec3 emitted(float u, float v, const vec3& p) const {
		return vec3(0,0,0);
	}
};


class lambertian: public material
{
public:
	lambertian(texture *a): albedo(a) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target-rec.p);
		attenuation = albedo->value(rec.u,rec.v,rec.p);
		return true;
	}
	static material* from_image(std::string imgfile);
	texture *albedo;
};

class metal: public material
{
public:
	metal(const vec3& a,float f=0):albedo(a){if(f<1) fuzz=f; else fuzz=1.0;}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected+fuzz*random_in_unit_sphere());
		attenuation = albedo;
		return(dot(scattered.direction(), rec.normal) > 0);
	}
	vec3 albedo;
	float fuzz;
};


class dielectric: public material
{
public:
	dielectric(float ri):ref_idx(ri) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.direction(), rec.normal);
		float ni_over_nt;
		attenuation = vec3(1.0,1.0,1.0);
		vec3 refracted;
		float reflect_prob;
		float cosine;
		if(dot(r_in.direction(), rec.normal) > 0)
		{
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
			cosine = ref_idx*dot(r_in.direction(), rec.normal)/ r_in.direction().length();
		}
		else
		{
			outward_normal = rec.normal;
			ni_over_nt = 1.0/ref_idx;
			cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
		}
		if(refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
		{
			reflect_prob = schlick(cosine, ref_idx);
		}
		else
		{
			scattered = ray(rec.p, reflected);
			reflect_prob = 1.0;
		}
		if(drand48() < reflect_prob)
		{
			scattered = ray(rec.p, refracted);
		}
		else
		{
			scattered = ray(rec.p, reflected);
		}
		return true;
		
		return true;
	}	
	float ref_idx;
};

/*class diffuse_light: public material
{
public:
        diffuse_light(texture *a):emit(a) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		return false;
	}
	virtual vec3 emitted(float u, float v, const vec3& p) const {
		return emit->value(u, v,p);
	}
	texture *emit;
};
*/

class phong: public material
{
public:
	texture *surface;
	texture *ambient;
	texture *diffuse;
	texture *specular;
	float shininess;
};

class isotropic: public material
{
public:
    isotropic(texture* a):albedo(a){}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const;
    texture* albedo;
};


#endif




