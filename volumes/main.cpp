#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "ray.h"
#include "hitable_list.h"
#include "bvh_node.h"
#include "hitable.h"
#include "camera.h"
#include "box.h"
#include "material.h"
#include "texture.h"
#include  <map>
#include <vector>
#include <thread>
#include "scenes.h"
using namespace std;

hitable *world;
int nx=1600;
int ny=1600;
int ns=100;

vec3 lookfrom(278, 278, -900);
vec3 lookat(278,278,0);
float dist_to_focus = 10.0;
float aperture = 0.0;
float vfov = 40.0;
camera cam(lookfrom, lookat, vec3(0,1,0),vfov, float(nx)/float(ny),aperture, dist_to_focus);
float *img;      

vec3 color (const ray& r, hitable *world, int depth=0)
{
	hit_record rec;
	bool hit = world->hit(r, 0.001, MAXFLOAT, rec);
	if (hit)
	{
		ray scattered;
		vec3 attenuation;
		vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
		if(depth <= 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return emitted + attenuation*(color(scattered, world, depth+1));
		}
		else
		{
			return emitted;
		}
			
	}
	return vec3(0,0,0);
}


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
	col=col.clamp();
	img[i*(ny*3)+j*3+0] = col.r();
	img[i*(ny*3)+j*3+1] = col.g();
	img[i*(ny*3)+j*3+2] = col.b();
}
                      
int main()
{
	world = cornell_smoke();
	srand48(time(NULL));
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
