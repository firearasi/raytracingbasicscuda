#include "cylinder.h"

bool cylinder::hit(const ray& r, float tmin, float tmax, hit_record & rec) const
{
    if(r.direction().x()==0 && r.direction().z()==0)
    {
            return false;
    }

    float a,b,c;
    a=r.direction().x()*r.direction().x()+r.direction().z()*r.direction().z();
    b=r.direction().x()*r.origin().x()+r.direction().z()*r.origin().z();
    c=r.origin().x()*r.origin().x()+r.origin().z()*r.origin().z()-radius*radius;

    float det=b*b-a*c;
    if(det < 0)
        return false;
    float t1 = (-b-sqrt(det))/a;
    float y1 = r.origin().y() + t1 * r.direction().y();
    if(t1 >= tmin && t1 <= tmax && y1 >= ymin && y1 <= ymax)
    {
        rec.t=t1;
    }
	else
    {
        float t2 = (-b+sqrt(det))/a;
        float y2 = r.origin().y() + t2 * r.direction().y();
        if(t2 >= tmin && t2 <= tmax && y2 >= ymin && y2 <= ymax)
        {
         rec.t=t2;
        }
        else
            return false;
    }
	
	rec.p = r.point_at_parameter(rec.t);

    rec.normal = rec.p/radius;
    rec.normal.e[1] = 0;
    //Checking whether the intersection is from within or without
    if(dot(rec.normal, r.direction()) > 0)
        rec.normal = -rec.normal;

    rec.mat_ptr = mat;

    float phi=atan2(rec.p.x(),rec.p.z());
    rec.u = 1-(phi + M_PI)/(2*M_PI);
    rec.v = (rec.p.y()-ymin)/(ymax-ymin);

    return true;
}

void solid_cylinder::free()
{
    if(node)
        delete node;
}

bool solid_cylinder::hit(const ray& r, float tmin, float tmax, hit_record & rec) const
{
    return node->hit(r, tmin, tmax, rec);
}

