#include "material.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float schlick(float cosine, float ref_idx)
{
    float r0 = (1-ref_idx)/(1+ref_idx);
    r0 = r0* r0;
    return r0 + (1-r0)*pow((1-cosine),5);
}

material* lambertian::from_image(std::string imgfile)
{
     int nx, ny, nn;
     unsigned char *tex_data=stbi_load(imgfile.c_str(), &nx,&ny,&nn,0);
     material *mat=new lambertian(new image_texture(tex_data,nx,ny));
     return mat;
}

bool isotropic::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
{
    scattered=ray(rec.p, random_in_unit_sphere());
    attenuation = albedo->value(rec.u,rec.v,rec.p);
    return true;
}
            
