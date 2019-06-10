#include "aarect.h"

bool xy_rect::hit(const ray& r, float t0, float t1, hit_record& rec) const {
    float t = (k-r.origin().z()) / r.direction().z();
    if (t < t0 || t > t1)
        return false;
    float x = r.origin().x() + t*r.direction().x();
    float y = r.origin().y() + t*r.direction().y();
    if (x < x0 || x > x1 || y < y0 || y > y1)
        return false;

    float a=(x-x0)/(x1-x0);
    float b=(y-y0)/(y1-y0);
    uv uv_coord=uv_ll+a*uv_u+b*uv_v;
    rec.u = uv_coord.u();
    rec.v = uv_coord.v();

    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.point_at_parameter(t);
    rec.normal = vec3(0, 0, 1);
    return true;
}

bool xz_rect::hit(const ray& r, float t0, float t1, hit_record& rec) const {
    float t = (k-r.origin().y()) / r.direction().y();
    if (t < t0 || t > t1)
        return false;
    float x = r.origin().x() + t*r.direction().x();
    float z = r.origin().z() + t*r.direction().z();
    if (x < x0 || x > x1 || z < z0 || z > z1)
        return false;

    float a=(x-x0)/(x1-x0);
    float b=(z-z0)/(z1-z0);
    uv uv_coord=uv_ll+a*uv_u+b*uv_v;
    rec.u = uv_coord.u();
    rec.v = uv_coord.v();

    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.point_at_parameter(t);
    rec.normal = vec3(0, 1, 0);
    return true;
}

bool yz_rect::hit(const ray& r, float t0, float t1, hit_record& rec) const {
    float t = (k-r.origin().x()) / r.direction().x();
    if (t < t0 || t > t1)
        return false;
    float y = r.origin().y() + t*r.direction().y();
    float z = r.origin().z() + t*r.direction().z();
    if (y < y0 || y > y1 || z < z0 || z > z1)
        return false;

    float a=(y-y0)/(y1-y0);
    float b=(z-z0)/(z1-z0);
    uv uv_coord=uv_ll+a*uv_u+b*uv_v;
    rec.u = uv_coord.u();
    rec.v = uv_coord.v();

    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.point_at_parameter(t);
    rec.normal = vec3(1, 0, 0);
    return true;
}

