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
	mat3 invTranspose() const;
	static mat3 rotate_y(float th);
	static mat3 scale_xyz(float a, float b, float c);
	float e[3][3];
	//mat3 *inv;
};


mat3::mat3()
{
	for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            e[i][j]=0;
    e[0][0]=1;
    e[1][1]=1;
    e[2][2]=1;
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

mat3 mat3::invTranspose() const
{
	float determinant = +e[0][0]*(e[1][1]*e[2][2]-e[2][1]*e[1][2])
                        -e[0][1]*(e[1][0]*e[2][2]-e[1][2]*e[2][0])
                        +e[0][2]*(e[1][0]*e[2][1]-e[1][1]*e[2][0]);
	float invdet = 1/determinant;
	mat3 result;
	result.e[0][0] =  (e[1][1]*e[2][2]-e[2][1]*e[1][2])*invdet;	
	result.e[1][0] = -(e[0][1]*e[2][2]-e[0][2]*e[2][1])*invdet;
	result.e[2][0] =  (e[0][1]*e[1][2]-e[0][2]*e[1][1])*invdet;
	result.e[0][1] = -(e[1][0]*e[2][2]-e[1][2]*e[2][0])*invdet;
	result.e[1][1] =  (e[0][0]*e[2][2]-e[0][2]*e[2][0])*invdet;
	result.e[2][1] = -(e[0][0]*e[1][2]-e[1][0]*e[0][2])*invdet;
	result.e[0][2] =  (e[1][0]*e[2][1]-e[2][0]*e[1][1])*invdet;
	result.e[1][2] = -(e[0][0]*e[2][1]-e[2][0]*e[0][1])*invdet;
	result.e[2][2] =  (e[0][0]*e[1][1]-e[1][0]*e[0][1])*invdet;
	return result;
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

mat3 mat3::scale_xyz(float a, float b, float c)
{
	mat3 m;
	m.e[0][0]=a;
	m.e[1][1]=b;
	m.e[2][2]=c;
	return m;
}

#endif
