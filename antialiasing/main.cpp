#include <iostream>
#include <stdlib.h>
#include "ray.h"
#include "hitable_list.h"
#include "hitable.h"
#include "camera.h"
using namespace std;


vec3 color (const ray& r, hitable *world)
{
	hit_record rec;
	bool hit = world->hit(r, 0, MAXFLOAT, rec);
	if (hit)
	{
		vec3 N = rec.normal;
		return 0.5 *(N + vec3(1.0,1.0,1.0));
	}
	vec3 unit_direction = unit_vector(r.direction());
	float s = 0.5*(unit_direction.y() + 1.0);
	return lerp(vec3(1.0,1.0,1.0), vec3(0.5,0.7,1.0),s);
}

int main()
{
	int nx=800;
	int ny=400;
	int ns= 100;
	cout << "P3\n" << nx << " " << ny << "\n255\n";

	camera cam;
	hitable *list[2];
	list[0]= new sphere(vec3(0,0,-1),0.5);
	list[1]= new sphere(vec3(0,-100.5,-1),100);
	hitable *world=new hitable_list(list,2);
	
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
			int ir=int(255.99*col.r());
			int ig=int(255.99*col.g());
			int ib=int(255.99*col.b());
			cout << ir<<" " << ig<<" " << ib<<"\n";
			
		}
	}	
	return 0;
}
