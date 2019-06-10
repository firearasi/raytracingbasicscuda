#include "disk.h"

bool disk::hit(const ray& r, float tmin, float tmax, hit_record & rec) const
{
    if(r.direction().y()==0)
    {
            return false;
    }

    float t=(y0-r.origin().y())/r.direction().y();
    if(t<tmin || t>tmax)
        return false;

    rec.t=t;
    rec.p = r.point_at_parameter(rec.t);
    if(rec.p.x()*rec.p.x()+rec.p.z()*rec.p.z()>=radius*radius)
        return false;

    rec.normal = vec3(0,1.0,0);
    if(dot(r.direction(), rec.normal) > 0)
        rec.normal = -rec.normal;
    rec.mat_ptr = mat;

    float phi=atan2(rec.p.x(),rec.p.z());
    rec.u = 1-(phi + M_PI)/(2*M_PI);
    rec.v = sqrt(rec.p.x()*rec.p.x()+rec.p.z()*rec.p.z())/radius;

    return true;
}

