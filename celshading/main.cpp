#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "ray.h"
#include "hitable_list.h"
#include "hitable.h"
#include "camera.h"
#include "material.h"
#include "texture.h"
#include  <map>
#include <vector>
#include <thread>
using namespace std;

vec3 color_normal (const ray& r, hitable *world)
{
    hit_record rec;
    bool hit = world->hit(r, 0, MAXFLOAT, rec);
    if (hit)
    {
    	ray scattered;
    	vec3 attenation;
        vec3 N = rec.normal;
        return 0.5 *(N + vec3(1.0,1.0,1.0));
    }
    vec3 unit_direction = unit_vector(r.direction());
    float s = 0.5*(unit_direction.y() + 1.0);
    return lerp(vec3(1.0,1.0,1.0), vec3(0.5,0.7,1.0),s);
}


vec3 color_diffuse (const ray& r, hitable *world, int depth=0)
{
	hit_record rec;
	bool hit = world->hit(r, 0.001, MAXFLOAT, rec);
	if (hit)
	{
		ray scattered;
		vec3 attenuation;
		if(depth <= 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			vec3 basic_color = attenuation*(color_diffuse(scattered, world, depth+1));
			if(depth == 0)
			{
				vec3 light_dir = rec.p - vec3(0, 10, 10); 				
				
				float intensity = dot(unit_vector(-light_dir), unit_vector(rec.normal));
				vec3 cel_color;
				if (intensity > 0.95)      cel_color = vec3(1.0, 1.0, 1.0);
				else if (intensity > 0.75) cel_color = vec3(0.8, 0.8, 0.8);
				else if (intensity > 0.50) cel_color = vec3(0.6, 0.6, 0.6);
				else if (intensity > 0.25) cel_color = vec3(0.4, 0.4, 0.4);
				else                       cel_color = vec3(0.2, 0.2, 0.2);
				                
				return basic_color * cel_color;
			}
			else
			{
				return basic_color;
			}
		}
		else
		{
			return vec3(0,0,0);
		}
			
	}
	vec3 unit_direction = unit_vector(r.direction());
	float s = 0.5*(unit_direction.y() + 1.0);
	return lerp(vec3(1.0,1.0,1.0), vec3(0.5,0.7,1.0),s);
}

vec3 color(const ray& r, hitable *world)
{
	return color_diffuse(r, world);

}

hitable *random_scene()
{
	int n =500;
	hitable **list = new hitable*[n+1];
	texture *checker = new checker_texture(new constant_texture(vec3(0.2, 0.3,0.1)), 
		new constant_texture(vec3(0.9,0.9,0.9)));
	list[0]=new sphere(vec3(0, -1000,0),1000,new lambertian_texture(checker));
	int i = 1;
	for(int a=-11;a<11;a++)
	{
		for(int b=-11;b<11;b++)
		{
			float choose_mat=drand48();
			vec3 center(a+0.9*drand48(), 0.2, b+ 0.9*drand48());
			if((center-vec3(4, 0.2,0)).length()>0.9)
			{
				if(choose_mat<0.333)
				{
					list[i++]=new sphere(center, 0.2, new lambertian(vec3(drand48()*drand48(),drand48()*drand48(),drand48()*drand48())));
				}
				else if(choose_mat<0.666)
				{
					list[i++] =new sphere(center,0.2,
					new metal(vec3(0.5*(1+drand48()), 0.5*(1+drand48()), 0.5*(1+drand48())), 0.5*drand48(), 
						3+100*drand48()));
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
	
	return new hitable_list(list, i);
}

hitable *world=random_scene();
int nx=1200;
int ny=800;
int ns=20;

vec3 lookfrom(13,3,6);
vec3 lookat(0,0,0);
float dist_to_focus = 13;
float aperture = 0.03;
camera cam(lookfrom, lookat, vec3(0,1,0),20, float(nx)/float(ny),aperture, dist_to_focus);
float *img;      

void render(int i, int j)
{
	float u=float(i)/float(nx);
	float v=float(j)/float(ny);
	ray r = cam.get_ray(u,v);
	vec3 col(0,0,0);
	for(int s=0;s<ns;s++)
	{
		float u=float(i+ drand48()-0.5)/float(nx);
		float v=float(j+ drand48()-0.5)/float(ny);
		ray r = cam.get_ray(u,v);
		col+=color(r,world);
	}
	col/=float(ns);
	img[i*(ny*3)+j*3+0] = col.r();
	img[i*(ny*3)+j*3+1] = col.g();
	img[i*(ny*3)+j*3+2] = col.b();
}
                      
int main()
{
	img = new float[nx*ny*3];
	int parts=10;
	vector<thread*> thds;
	for (int i=0;i<parts;i++)
		for(int j=0;j<parts;j++)
		{
			thread* thd=new thread([i,j,parts](){
				for (int s=nx/parts*i;s<nx/parts*(i+1);s++)
					for (int t=ny/parts*j;t<ny/parts*(j+1);t++)
				    {
				    	render(s,t);
				    }                                    		
			});
			thds.push_back(thd);
		}

	for(auto thd:thds)
	{
		thd->join();
	}
	
	float r,g,b;
	int ir,ig,ib;
	cout << "P3\n" << nx << " " << ny << "\n255\n";	
	for(int j=ny-1;j>=0;j--)
		for(int i=0;i<nx;i++)
			{
				r=img[i*(ny*3)+j*3+0];
				g=img[i*(ny*3)+j*3+1];
				b=img[i*(ny*3)+j*3+2];
				ir=int(255.99*sqrt(r));
				ig=int(255.99*sqrt(g));
				ib=int(255.99*sqrt(b));
				cout << ir<<" " << ig<<" " << ib<<"\n";
				                                     
			}

		
	delete img;
	return 0;
}
