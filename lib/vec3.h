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

#ifndef VEC3H
#define VEC3H

#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3  {

    
public:
    vec3() {}
    vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }
    
    inline const vec3& operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    inline float operator[](int i) const { return e[i]; }
    inline float& operator[](int i) { return e[i]; };
    
    vec3& operator+=(const vec3 &v2);
    vec3& operator-=(const vec3 &v2);
    vec3& operator*=(const vec3 &v2);
    vec3& operator/=(const vec3 &v2);
    vec3& operator*=(const float t);
    vec3& operator/=(const float t);
    
    float length() const { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
    float squared_length() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
    void make_unit_vector();
	vec3 clamp();    
    
    float e[3];
};

 std::istream& operator>>(std::istream &is, vec3 &t);

 std::ostream& operator<<(std::ostream &os, const vec3 &t);

 vec3 operator+(const vec3 &v1, const vec3 &v2);

 vec3 operator-(const vec3 &v1, const vec3 &v2);

 vec3 operator*(const vec3 &v1, const vec3 &v2); 

 vec3 operator/(const vec3 &v1, const vec3 &v2);

 vec3 operator*(float t, const vec3 &v);

 vec3 operator/(vec3 v, float t);

 vec3 operator*(const vec3 &v, float t);

 float dot(const vec3 &v1, const vec3 &v2);

 vec3 cross(const vec3 &v1, const vec3 &v2);

 vec3 unit_vector(vec3 v);

 vec3 lerp(const vec3& u, const vec3& v, float t);

 vec3 reflect(const vec3& v, const vec3&n);

 bool refract(const vec3&v, const vec3&n, float ni_over_nt, vec3& refracted);

 vec3 random_in_unit_sphere();

 vec3 random_in_unit_disk();                                                
#endif
