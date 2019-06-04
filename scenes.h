#ifndef SCENESH
#define SCENESH
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "ray.h"
#include "hitable_list.h"
#include "bvh_node.h"
#include "hitable.h"
#include "aarect.h"
#include "camera.h"
#include "material.h"
#include "texture.h"


hitable *random_scene()
{
	int n =500;
	hitable **list = new hitable*[n+1];
	texture *checker = new checker_texture(new constant_texture(vec3(0.2, 0.3,0.1)), 
		new constant_texture(vec3(0.9,0.9,0.9)));
	list[0]=new sphere(vec3(0, -1000,0),1000,new lambertian_texture(checker));
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
					list[i++]=new sphere(center, 0.2, new lambertian(vec3(drand48()*drand48(),drand48()*drand48(),drand48()*drand48())));
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

	list[i++]=new sphere(vec3(0,1,0),1.0,new dielectric(1.5));
	list[i++]=new sphere(vec3(-4,1,0),1.0, lambertian_texture::from_image("../img/earth.jpg"));
	list[i++]=new sphere(vec3(4,1,0),1.0, new metal(vec3(0.7,0.6,0.5),0.0));
	
	//return new hitable_list(list, i);
	return new bvh_node(list,i,0,0);
}

hitable *cornell_box()
{
	hitable **list = new hitable*[6];
	int i=0;
	material *red = new lambertian_texture(new constant_texture(vec3(0.65,0.05,0.05)));
	material *white = new lambertian_texture(new constant_texture(vec3(0.73,0.73,0.73)));
	material *green = new lambertian_texture(new constant_texture(vec3(0.12,0.45,0.15)));
	material *light = new diffuse_light(new constant_texture(vec3(15,15,15)));
	list[i++] = new flip_normals(new yz_rect(0,555,0,555,555,green));
	list[i++] = new yz_rect(0,555,0,555,0,red);
	list[i++] = new xz_rect(213,343,227,332,554,light);
	list[i++] = new flip_normals(new xz_rect(0,555,0,555,555,white));
	list[i++] = new xz_rect(0,555,0,555,0,white);
	list[i++] = new flip_normals(new xy_rect(0,555,0,555,555,white));
	return new bvh_node(list,i,0,0);
}
#endif
