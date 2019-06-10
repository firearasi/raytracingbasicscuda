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

#ifndef UVH
#define UVH

#include <math.h>
#include <stdlib.h>
#include <iostream>

class uv  {

    
public:
    uv() {e[0]=0;e[1]=0;}
    uv(float e0, float e1) { e[0] = e0; e[1] = e1; }
    inline float u() const { return e[0]; }
    inline float v() const { return e[1]; }
    
    inline const uv& operator+() const { return *this; }
    inline uv operator-() const { return uv(-e[0], -e[1]); }
    inline float operator[](int i) const { return e[i]; }
    inline float& operator[](int i) { return e[i]; };
    
    uv& operator+=(const uv &v2);
    uv& operator-=(const uv &v2);
    uv& operator*=(const uv &v2);
    uv& operator/=(const uv &v2);
    uv& operator*=(const float t);
    uv& operator/=(const float t);
    
	uv clamp();    
    float e[2];
};



std::istream& operator>>(std::istream &is, uv &t);

std::ostream& operator<<(std::ostream &os, const uv &t);

uv operator+(const uv &v1, const uv &v2);

uv operator-(const uv &v1, const uv &v2);

uv operator*(const uv &v1, const uv &v2);

uv operator/(const uv &v1, const uv &v2);

uv operator*(float t, const uv &v);

uv operator/(uv v, float t);

uv operator*(const uv &v, float t);

float dot(const uv &v1, const uv &v2);

uv lerp(const uv& u, const uv& v, float t);
                                                
#endif
