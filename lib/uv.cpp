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

#include "uv.h"


 std::istream& operator>>(std::istream &is, uv &t) {
    is >> t.e[0] >> t.e[1] ;
    return is;
}

 std::ostream& operator<<(std::ostream &os, const uv &t) {
    os << t.e[0] << " " << t.e[1] ;
    return os;
}


 uv uv::clamp()
{
	float uu,vv;
	uu=u();
	vv=v();
	if(uu<0) uu=0;
	else if(uu>1) uu=1;
	if(vv<0) vv=0;
	else if(vv>1) vv=1;
	return uv(uu,vv);
}

 uv operator+(const uv &v1, const uv &v2) {
    return uv(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1]);
}

 uv operator-(const uv &v1, const uv &v2) {
    return uv(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1]);
}

 uv operator*(const uv &v1, const uv &v2) {
    return uv(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1]);
}

 uv operator/(const uv &v1, const uv &v2) {
    return uv(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1]);
}

 uv operator*(float t, const uv &v) {
    return uv(t*v.e[0], t*v.e[1]);
}

 uv operator/(uv v, float t) {
    return uv(v.e[0]/t, v.e[1]/t);
}

 uv operator*(const uv &v, float t) {
    return uv(t*v.e[0], t*v.e[1]);
}

 float dot(const uv &v1, const uv &v2) {
    return v1.e[0] *v2.e[0] + v1.e[1] *v2.e[1];
}



 uv& uv::operator+=(const uv &v){
    e[0]  += v.e[0];
    e[1]  += v.e[1];
    return *this;
}

 uv& uv::operator*=(const uv &v){
    e[0]  *= v.e[0];
    e[1]  *= v.e[1];
    return *this;
}

 uv& uv::operator/=(const uv &v){
    e[0]  /= v.e[0];
    e[1]  /= v.e[1];
    return *this;
}

 uv& uv::operator-=(const uv& v) {
    e[0]  -= v.e[0];
    e[1]  -= v.e[1];
    return *this;
}

 uv& uv::operator*=(const float t) {
    e[0]  *= t;
    e[1]  *= t;
    return *this;
}

 uv& uv::operator/=(const float t) {
    float k = 1.0/t;
    
    e[0]  *= k;
    e[1]  *= k;
    return *this;
}


 uv lerp(const uv& u, const uv& v, float t)
{
	return (1.0 - t) * u + t * v;
}

                                                
