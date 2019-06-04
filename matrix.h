#ifndef MATRIXH
#define MATRIXH
#include "vec3.h"
#include "ray.h"
#include "aabb.h"
#include <math.h>
#include <float.h>

class mat3
{
public:
	mat3();
	mat3(const mat3& m);
	mat3(float *a);
	mat3(float **b);
	mat3 operator-() const;
	mat3 transpose() const;
	static mat3 rotate_y(float th);
	float e[3][3];
	//mat3 *inv;
};


mat3::mat3()
{
	for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            e[i][j]=0;
}

mat3::mat3(const mat3 &m)
{
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            e[i][j]=m.e[i][j];
}


mat3::mat3(float *a)
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			e[i][j]=a[i*3+j];
}

mat3::mat3(float **b)
{
	for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
			e[i][j]=b[i][j];
}

mat3 mat3::operator-() const
{
	mat3 temp;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			temp.e[i][j]=-e[i][j];
	return temp;
}

mat3 mat3::transpose() const 
{
    mat3 temp;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
		{
            temp.e[i][j]=e[j][i];
		}
    return temp;
}

inline mat3 operator+(const mat3 &l, const mat3 &r) {
    mat3 temp;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {   
			temp.e[i][j]=l.e[i][j]+r.e[i][j];
        }
    return temp;
}
  
inline mat3 operator-(const mat3 &l, const mat3 &r) {
    mat3 temp;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
			temp.e[i][j]=l.e[i][j]-r.e[i][j];
        }
    return temp;
}

inline mat3 operator*(const mat3 &l, const mat3 &r) {
    mat3 temp;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
		{
			temp.e[i][j]=0;
        	for(int k=0;k<3;k++)
			{
				temp.e[i][j]+=l.e[i][k]*r.e[k][j];
       	 	}
		}
    return temp;
}

inline vec3 operator*(const mat3 &l, const vec3 &r) {
    vec3 temp;
    for(int i=0;i<3;i++)
    {
    	temp.e[i]=0;
        for(int k=0;k<3;k++)
        {
                temp.e[i]+=l.e[i][k]*r.e[k];
        }
    }
    return temp;
}

inline ray operator*(const mat3 &l, const ray& r)
{
	ray temp;
	temp.A=l*r.A;
	temp.B=l*r.B;
	return temp;
}

inline aabb operator*(const mat3 &l, const aabb& bbox)
{
	vec3 min(FLT_MAX, FLT_MAX, FLT_MAX);
	vec3 max(-FLT_MAX, -FLT_MAX, -FLT_MAX);	

	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			for (int k=0;k<2;k++)
			{
				vec3 tester0= vec3(i,j,k)*bbox.max()+vec3(1-i,1-j,1-k)*bbox.min();
				vec3 tester=l*tester0;
				for(int c=0;c<3;c++)
				{
					if(tester[c]>max[c])
						max[c]=tester[c];
					if(tester[c]<min[c])
						min[c]=tester[c];
				}
			}
	
	return aabb(min,max);
}

mat3 mat3::rotate_y(float th)
{
	float a[9]={cos(th),	0,	-sin(th),
				0	 , 	1,		0	,
			  sin(th),	0,	cos(th)};
	return mat3(a);

}


#endif
