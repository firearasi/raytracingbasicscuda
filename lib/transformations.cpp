#include "transformations.h"

void translate::free()
{
    if(obj)
        delete obj;
}

bool translate::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
    ray r_tl(r.origin()-offset, r.direction());
    bool bHit = obj->hit(r_tl, t_min, t_max, rec);
    if(bHit)
    {
        rec.p += offset;
    }
    return bHit;
}

bool translate::bounding_box(float t0, float t1, aabb& box) const
{
    bool bBound = obj->bounding_box(t0, t1, box);
    if(bBound)
    {
        box._min += offset;
        box._max += offset;
    }
    return bBound;
}

void linear::free()
{
    if(obj)
    {
        delete obj;
    }
}

bool linear::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
    ray r_inv=inv*r;
    bool bHit = obj->hit(r_inv, t_min, t_max, rec);
    if(bHit)
    {
        rec.p = m * rec.p;

        //  normal is in the cotangent space and is contravariant, tr(inv(m))
        rec.normal = unit_vector(invTranspose * rec.normal);
    }
    return bHit;
}
            
bool linear::bounding_box(float t0, float t1, aabb& box) const
{
    bool bBound = obj->bounding_box(t0, t1, box);
    if(bBound)
    {
        box=m*box;
    }
    return bBound;
}

