#include <iostream>
#include "ray.h"
#define TX 32
#define TY 32
using namespace std;

__device__ vec3 color (const ray& r)
{
	vec3 unit_direction = unit_vector(r.direction());
	float t=0.5*(unit_direction.y() + 1.0);
	float s=0.5*(unit_direction.x()+1.0);
	return lerp(vec3(1.0,0.3,0.9), lerp(vec3(1.0,1.0,1.0), vec3(0.5,0.7,1.0), t), s);
}

__global__ void renderKernel(vec3* d_pixels, int nx, int ny)
{
	int i = threadIdx.x+blockIdx.x*blockDim.x;
	int j = threadIdx.y+blockIdx.y*blockDim.y;
	if(i>=nx||j>=ny)
		return;
	vec3 lower_left_corner(-2.0,-1.0,-1.0);
	vec3 horizontal(4.0,0.0,0.0);
	vec3 vertical(0.0,2.0,0.0);
	vec3 origin(0.0,0.0,0.0);
	float u=float(i)/float(nx);
	float v=float(j)/float(ny);
	vec3 pt(lower_left_corner + u*horizontal+v*vertical);
	ray r(origin, pt);
	d_pixels[i+j*nx]=color(r);

}

int main()
{
	int nx=200;
	int ny=100;
	cout << "P3\n" << nx << " " << ny << "\n255\n";

	vec3* d_pixels;
	cudaMallocManaged(&d_pixels,nx*ny*sizeof(vec3));
	dim3 blockSize(TX,TY);
	dim3 gridSize((nx+TX-1)/TX,(ny+TY-1)/TY);
	renderKernel<<<gridSize,blockSize>>>(d_pixels,nx,ny);
	cudaDeviceSynchronize();
	for (int j=ny-1;j>=0;j--)
		for (int i=0;i<nx;i++)
		{
			int ir=int(255.99*d_pixels[i+j*nx].r());
			int ig=int(255.99*d_pixels[i+j*nx].g());
			int ib=int(255.99*d_pixels[i+j*nx].b());
			cout << ir<<" " << ig<<" " << ib<<"\n";
		}

	cudaFree(d_pixels);
	return 0;
}
