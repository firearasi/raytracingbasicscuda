#include "scene.h"
hitable *some_scene()
{
    int n =500;
    hitable **list = new hitable*[n+1];
    texture *checker = new checker_texture(new constant_texture(vec3(0.2, 0.3,0.1)),
        new constant_texture(vec3(0.9,0.9,0.9)));
    list[0]=new sphere(vec3(0, -1000,0),1000,new lambertian(checker));
//	list[0]=new sphere(vec3(0, -1000,0),1000, new dielectric(1.3));
    int i = 1;
    for(int a=-11;a<11;a++)
    {
        for(int b=-11;b<11;b++)
        {
            float choose_mat=drand48();
            vec3 center(a+0.9*(drand48()-0.5), 0.2, b+ 0.9*(drand48()-0.5));
            if((center-vec3(0, 1,0)).length()>1.2 && (center-vec3(-4, 1,0)).length()>1.2 && (center-vec3(4, 1,0)).length()>1.2)
            {
                if(choose_mat<0.333)
                {
                    list[i++]=new sphere(center, 0.2,
                        new lambertian(new constant_texture(vec3(drand48()*drand48(),drand48()*drand48(),drand48()*drand48()))));
                }
                else if(choose_mat<0.666)
                {
                    list[i++] =new sphere(center,0.2,
                    new metal(vec3(0.5*(1+drand48()), 0.5*(1+drand48()), 0.5*(1+drand48())), 0.5*drand48()));
                }
                else
                {
                    list[i++]=new sphere(center,0.2, new dielectric(1.5+ (drand48()-0.5)*0.2));
                }
            }
        }
    }

    list[i++]=new sphere(vec3(0,2.5,0),1.5,new dielectric(1.5));
    list[i++]=new translate(vec3(-4,2.5,0),new linear(mat3::scale_xyz(1.5,1.5,1.5),
        new sphere(vec3(0,0,0),1.0, lambertian::from_image("../img/earth.jpg"))));
    list[i++]=new sphere(vec3(4,1,0),1.0, new metal(vec3(0.7,0.6,0.5),0.0));
    //return new hitable_list(list, i);
    return new bvh_node(list,i,0,0);
}

