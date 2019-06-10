#ifndef AARECTH
#define AARECTH

#include "hitable.h"
#include "uv.h"
class xy_rect: public hitable  {
    public:
        xy_rect() {}    
        xy_rect(float _x0, float _x1, float _y0, float _y1, float _k, material *mat,uv ll=uv(),uv u=uv(1,0),uv v=uv(0,1)) 
        	: x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat),uv_ll(ll),uv_u(u),uv_v(v) {};
		virtual void free(){}
        virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;
        virtual bool bounding_box(float t0, float t1, aabb& box) const {
               box =  aabb(vec3(x0,y0, k-0.0001), vec3(x1, y1, k+0.0001));
               return true; }
        material  *mp;
        float x0, x1, y0, y1, k;
		uv uv_ll,uv_u,uv_v;
};

class xz_rect: public hitable  {
    public:
        xz_rect() {}
        xz_rect(float _x0, float _x1, float _z0, float _z1, float _k, material *mat,uv ll=uv(),uv u=uv(1,0),uv v=uv(0,1))
        	 : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat),uv_ll(ll),uv_u(u),uv_v(v) {};
		virtual void free(){}
        virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;
        virtual bool bounding_box(float t0, float t1, aabb& box) const {
               box =  aabb(vec3(x0,k-0.0001,z0), vec3(x1, k+0.0001, z1));
               return true; }
        material  *mp;
        float x0, x1, z0, z1, k;
		uv uv_ll,uv_u,uv_v;
};

class yz_rect: public hitable  {
    public:
        yz_rect() {}
        yz_rect(float _y0, float _y1, float _z0, float _z1, float _k, material *mat,uv ll=uv(),uv u=uv(1,0),uv v=uv(0,1)) 
        	: y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat),uv_ll(ll),uv_u(u),uv_v(v) {};
		virtual void free(){}
        virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;
        virtual bool bounding_box(float t0, float t1, aabb& box) const {
               box =  aabb(vec3(k-0.0001, y0, z0), vec3(k+0.0001, y1, z1));
               return true; }
        material  *mp;
        float y0, y1, z0, z1, k;
		uv uv_ll,uv_u,uv_v;
};

#endif
