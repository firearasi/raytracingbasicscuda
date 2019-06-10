#include "rt.h"


vec3 Scene::color (const ray& r, int depth)
{
	hit_record rec;
	bool hit = world->hit(r, 0.001, MAXFLOAT, rec);
	if (hit)
	{
		ray scattered;
		vec3 attenuation;
		if(depth <= 30 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
            return attenuation*(color(scattered, depth+1));
		}
		else
		{
			return vec3(0,0,0);
		}
			
	}
	vec3 unit_direction = unit_vector(r.direction());
	float s = 0.5*(unit_direction.y() + 1.0);
    return lerp(vec3(0.86,0.86,0.86), vec3(0.5,0.7,1.0),s);
}

void Scene::render_ppm_pixel(int i, int j)
{
	vec3 col(0,0,0);
	for(int s=0;s<ns;s++)
	{
		float u=float(i+ drand48()-0.5)/float(nx);
		float v=float(j+ drand48()-0.5)/float(ny);
        ray r = cam->get_ray(u,v);
        col+=color(r);
	}
	col/=float(ns);
	img[i*(ny*3)+j*3+0] = col.r();
	img[i*(ny*3)+j*3+1] = col.g();
	img[i*(ny*3)+j*3+2] = col.b();
}
                      
int Scene::render_ppm(string filename)
{

	srand48(123);
    //float *img;
	img = new float[nx*ny*3];
	int parts=10;
	   
	vector<thread*> thds;
	for (int i=0;i<parts;i++)
		for(int j=0;j<parts;j++)
		{
            thread* thd=new thread([i,j,parts,this](){
				for (int s=nx/parts*i;s<nx/parts*(i+1);s++)
					for (int t=ny/parts*j;t<ny/parts*(j+1);t++)
				    {
                        render_ppm_pixel(s,t);
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

	ofstream file;
    file.open(filename.c_str());
	file << "P3\n" << nx << " " << ny << "\n255\n";	
	for(int j=ny-1;j>=0;j--)
		for(int i=0;i<nx;i++)
			{
				r=img[i*(ny*3)+j*3+0];
				g=img[i*(ny*3)+j*3+1];
				b=img[i*(ny*3)+j*3+2];
				ir=int(255.99*sqrt(r));
				ig=int(255.99*sqrt(g));
				ib=int(255.99*sqrt(b));
				file << ir<<" " << ig<<" " << ib<<"\n";
				                                     
			}
	file.close();
	delete img;
	return 0;
}
void Scene::render_qimg_pixel(int i, int j)
{
    vec3 col(0,0,0);
    for(int s=0;s<ns;s++)
    {
        float u=float(i+ drand48()-0.5)/float(nx);
        float v=float(j+ drand48()-0.5)/float(ny);
        ray r = cam->get_ray(u,v);
        col+=color(r);
    }


    col/=float(ns);
    //col=col.clamp();

    //int ir, ig, ib;
    //ir=int(255.99*sqrt(col.r()));
    //ig=int(255.99*sqrt(col.g()));
    //ib=int(255.99*sqrt(col.b()));
    QColor qc;
    qc.setRgbF(col.r(),col.g(),col.b());
    qimg.setPixelColor(i,ny-1-j,qc);
    //qDebug()<<QString("Set pixel: %1, %2 color: %3, %4, %5").arg(
    //              QString::number(i),QString::number(j),QString::number(ir),QString::number(ig),QString::number(ib));
}

int Scene::render_qimg()
{

    srand48(123);
    //float *img;
    img = new float[nx*ny*3];
    int parts=10;

    vector<thread*> thds;
    for (int i=0;i<parts;i++)
        for(int j=0;j<parts;j++)
        {
            thread* thd=new thread([i,j,parts,this](){
                for (int s=nx/parts*i;s<nx/parts*(i+1);s++)
                    for (int t=ny/parts*j;t<ny/parts*(j+1);t++)
                    {
                        render_qimg_pixel(s,t);
                    }
            });
            thds.push_back(thd);
        }

    for(auto thd:thds)
    {
        thd->join();
    }

    qimg.save("pic.png");
    return 0;
}
