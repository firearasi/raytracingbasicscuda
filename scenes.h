#ifndef SCENESH
#define SCENESH
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "ray.h"
#include "hitable_list.h"
#include "box.h"
#include "transformations.h"
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
	hitable **list = new hitable*[30];
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
	list[i++] = new box(vec3(133,0,65),vec3(295,165,230),white);
	list[i++] = new box(vec3(265,0,295), vec3(430,330,460),white);
	list[i++] = new sphere(vec3(160, 100, 145), 50, new dielectric(1.5));
	
	return new bvh_node(list,i,0,0);
}

hitable *cornell_balls() {
    hitable **list = new hitable*[9];
    int i = 0;
    material *red = new lambertian_texture( new constant_texture(vec3(0.65, 0.05, 0.05)) );
    material *white = new lambertian_texture( new constant_texture(vec3(0.73, 0.73, 0.73)) );
    material *green = new lambertian_texture( new constant_texture(vec3(0.12, 0.45, 0.15)) );
    material *light = new diffuse_light( new constant_texture(vec3(6,6,6)) );
    list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, green));
    list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
    list[i++] = new xz_rect(113, 443, 127, 432, 554, light);
    list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
    list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
    list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));
    hitable *boundary = new sphere(vec3(160, 100, 145), 45, new dielectric(1.5));
    //list[i++] = boundary;
 	list[i++] = new translate(vec3(0,200,0), boundary);
    list[i++] = new box(vec3(133,0,65),vec3(295,165,230),white);
 	box *b = new box(vec3(265,0,295), vec3(430,330,460),white);
 	list[i++] = new orthogonal(mat3::rotate_y(10*M_PI/180.0), b);
 //   list[i++] = new constant_medium(boundary, 0.1, new constant_texture(vec3(1.0, 1.0, 1.0)));
  //  list[i++] = new translate(new rotate_y(new box(vec3(0, 0, 0), vec3(165, 330, 165), white),  15), vec3(265,0,295));
    return new hitable_list(list,i);
}
#endif
