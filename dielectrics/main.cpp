#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "ray.h"
#include "hitable_list.h"
#include "hitable.h"
#include "bvh_node.h"
#include "camera.h"
#include "material.h"
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
			return attenuation*(color_diffuse(scattered, world, depth+1));
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
	return lerp(color_diffuse(r, world), color_normal(r,world), 0.00);

}

int main()
{
	int nx=800;
	int ny=600;
	int ns=20;
	cout << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lookfrom = vec3(4,2,2);
	vec3 lookat = vec3(0,0,-1);
	float focus_dist = (lookfrom-lookat).length();
	float aperture=0.2;
	

	camera cam(lookfrom, lookat, vec3(0,1,0),90, float(nx)/float(ny),aperture, focus_dist);
	hitable *list[5];
	list[0]= new sphere(vec3(0,0,-1),0.5, new lambertian(vec3(0.8,0.3,0.3)));
	list[1]= new sphere(vec3(0,-100.5,-1),100, new lambertian(vec3(0.8,0.8,0.2)));
	list[2]= new sphere(vec3(1,0,-1),0.5,new metal(vec3(0.8,0.6,0.2),0.2));
	list[3]=new sphere(vec3(-1.3,0.2,-1),0.5,new dielectric(1.5));
	//list[4]=new sphere(vec3(0,0.3,-4),1.5,new dielectric(1.2));
	//hitable *world=new hitable_list(list,4);
	hitable *world=new bvh_node(&list[0],4,0,0);
	aabb box;
	world->bounding_box(0,0,box);
	box.print();	
	
	for (int j=ny-1;j>=0;j--)
	{
		for (int i=0;i<nx;i++)
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
			int ir=int(255.99*sqrt(col.r()));
			int ig=int(255.99*sqrt(col.g()));
			int ib=int(255.99*sqrt(col.b()));
			cout << ir<<" " << ig<<" " << ib<<"\n";
			
		}
	}	
	return 0;
}
