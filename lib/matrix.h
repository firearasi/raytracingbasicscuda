#ifndef MATRIXH
#define MATRIXH
#include "vec3.h"
#include "ray.h"
#include "aabb.h"
#include <math.h>
#include <float.h>

class mat3
{
public:
	mat3();
	mat3(const mat3& m);
	mat3(float *a);
	mat3(float **b);
	mat3 operator-() const;
	mat3 transpose() const;
	mat3 invTranspose() const;
	static mat3 rotate_x(float th);
	static mat3 rotate_y(float th);
	static mat3 rotate_z(float th);
	static mat3 scale_xyz(float a, float b, float c);
	float e[3][3];
	//mat3 *inv;
};



mat3 operator+(const mat3 &l, const mat3 &r);
  
mat3 operator-(const mat3 &l, const mat3 &r);

mat3 operator*(const mat3 &l, const mat3 &r);

vec3 operator*(const mat3 &l, const vec3 &r);

ray operator*(const mat3 &l, const ray& r);

aabb operator*(const mat3 &l, const aabb& bbox);

#endif
