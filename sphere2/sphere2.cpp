#include <iostream>
#include "ray.h"
#include "utils.h"
using namespace std;


vec3 color (const ray& r)
{
	vec3 center = vec3(0,0,-1);
	float radius = 0.5;
	float t = hit_sphere(center,radius,r);
	if (t>=0)
	{
		vec3 hit_point = r.point_at_parameter(t);
		vec3 N = unit_vector(hit_point - center);
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
	cout << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-2.0,-1.0,-1.0);
	vec3 horizontal(4.0,0.0,0.0);
	vec3 vertical(0.0,2.0,0.0);
	vec3 origin(0.0,0.0,0.0);
	
	for (int j=ny-1;j>=0;j--)
		for (int i=0;i<nx;i++)
		{
			float u=float(i)/float(nx);
			float v=float(j)/float(ny);
			vec3 pt = lower_left_corner + u*horizontal+v*vertical;
			ray r(origin, pt);
			vec3 col=color(r);
			int ir=int(255.99*col.r());
			int ig=int(255.99*col.g());
			int ib=int(255.99*col.b());
			cout << ir<<" " << ig<<" " << ib<<"\n";
			
		}	
	return 0;
}
