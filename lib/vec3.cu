//==================================================================================================
// Written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is distributed
// without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication along
// with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==================================================================================================

#include "vec3.h"
extern "C"{

__device__ __host__  void vec3::make_unit_vector() {
    float k = 1.0 / sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    e[0] *= k; e[1] *= k; e[2] *= k;
}

__device__ __host__ vec3 vec3::clamp()
{
	float rr,gg,bb;
	rr=r();
	gg=g();
	bb=b();
	if(rr<0) rr=0;
	else if(rr>1) rr=1;
	if(gg<0) gg=0;
	else if(gg>1) gg=1;
	if(bb<0) bb=0;
	else if(bb>1) bb=1;
	return vec3(rr,gg,bb);
}

__device__ __host__  vec3 operator+(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

__device__ __host__  vec3 operator-(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

__device__ __host__  vec3 operator*(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

__device__ __host__  vec3 operator/(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

__device__ __host__  vec3 mult(float t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}




__device__ __host__  float dot(const vec3 &v1, const vec3 &v2) {
    return v1.e[0] *v2.e[0] + v1.e[1] *v2.e[1]  + v1.e[2] *v2.e[2];
}

__device__ __host__  vec3 cross(const vec3 &v1, const vec3 &v2) {
    return vec3( (v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1]),
                (-(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0])),
                (v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0]));
}


__device__ __host__  vec3& vec3::operator+=(const vec3 &v){
    e[0]  += v.e[0];
    e[1]  += v.e[1];
    e[2]  += v.e[2];
    return *this;
}

__device__ __host__  vec3& vec3::operator*=(const vec3 &v){
    e[0]  *= v.e[0];
    e[1]  *= v.e[1];
    e[2]  *= v.e[2];
    return *this;
}

__device__ __host__  vec3& vec3::operator/=(const vec3 &v){
    e[0]  /= v.e[0];
    e[1]  /= v.e[1];
    e[2]  /= v.e[2];
    return *this;
}

__device__ __host__  vec3& vec3::operator-=(const vec3& v) {
    e[0]  -= v.e[0];
    e[1]  -= v.e[1];
    e[2]  -= v.e[2];
    return *this;
}

__device__ __host__  vec3& vec3::operator*=(const float t) {
    e[0]  *= t;
    e[1]  *= t;
    e[2]  *= t;
    return *this;
}

__device__ __host__  vec3& vec3::operator/=(const float t) {
    float k = 1.0/t;
    
    e[0]  *= k;
    e[1]  *= k;
    e[2]  *= k;
    return *this;
}

__device__ __host__ vec3& vec3::operator=(const vec3& v2)
{
	e[0]=v2.e[0];
	e[1]=v2.e[1];
	e[2]=v2.e[2];
	return *this;
}

__device__ __host__  vec3 unit_vector(vec3 v) {
    return mult(1.0 / v.length(),v);
}

__device__ __host__  vec3 lerp(const vec3& u, const vec3& v, float t)
{
	return mult((1.0 - t) , u) + mult(t , v);
}

__device__ __host__  vec3 reflect(const vec3& v, const vec3&n)
{
	return v- mult(2*dot(v,n),n);
}

__device__ __host__  bool refract(const vec3&v, const vec3&n, float ni_over_nt, vec3& refracted)
{
	vec3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt*(1-dt*dt);
	if(discriminant > 0)
	{
		refracted = mult(ni_over_nt , (uv-mult(dt,n))) -  mult(sqrt(discriminant),n);
		return true;
	}
	else
		return false;
}

__device__ __host__  vec3 random_in_unit_sphere()
{
    vec3 p;
    do {
    	p = mult(2.0 , vec3(drand48(),drand48(),drand48())-vec3(1,1,1));
    } while(p.squared_length()>=1.0);
    return p;
}

__device__ __host__  vec3 random_in_unit_disk()
{
    vec3 p;
    do {
    	p = mult(2.0 , vec3(drand48(),drand48(),0)-vec3(1,1,0));
    } while(p.squared_length()>=1.0);
	return p;
}
                                                
}
