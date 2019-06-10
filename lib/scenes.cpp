#include "scenes.h"

hitable *random_scene()
{
	int n =500;
	hitable **list = new hitable*[n+1];
	texture *checker = new checker_texture(new constant_texture(vec3(0.2, 0.3,0.1)), 
		new constant_texture(vec3(0.9,0.9,0.9)));
	list[0]=new sphere(vec3(0, -1000,0),1000,new lambertian(checker));
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
					list[i++]=new sphere(center, 0.2, 
						new lambertian(new constant_texture(vec3(drand48()*drand48(),drand48()*drand48(),drand48()*drand48()))));
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

	list[i++]=new sphere(vec3(0,2.5,0),1.5,new dielectric(1.5));
	list[i++]=new translate(vec3(-4,2.5,0),new linear(mat3::scale_xyz(1.5,1.5,1.5),
		new sphere(vec3(0,0,0),1.0, lambertian::from_image("../img/earth.jpg"))));
	list[i++]=new sphere(vec3(4,1,0),1.0, new metal(vec3(0.7,0.6,0.5),0.0));
	//return new hitable_list(list, i);
	return new bvh_node(list,i,0,0);
}

hitable *box_scene()
{
	int n=11;
    material *red = new lambertian(new constant_texture(vec3(0.65,0.05,0.05)));
    hitable **list = new hitable*[n+1];
    texture *checker = new checker_texture(new constant_texture(vec3(0.2, 0.3,0.1)),
        new constant_texture(vec3(0.9,0.9,0.9)));
    int i=0;
    //list[i++]=new sphere(vec3(0, -1000,0),1000,new lambertian(checker));
	material *skybox=lambertian::from_image("../img/skybox1.jpg");

	hitable *b=new box(vec3(-1.2,-1.2,-1.2), vec3(1.2,1.2,1.2), skybox);
	list[i++]=new linear(mat3::rotate_x(-4*M_PI/180), b);

	hitable *s=new sphere(vec3(1.5,1.1,-1.5),0.7, new dielectric(1.4));
	list[i++]=s;

	list[i++]=new triangle(vec3(0,3,0),vec3(-1.2,2,0), vec3(1.2,2,0), lambertian::from_image("../img/earth.jpg"));

	return new bvh_node(list,i);	
}	
hitable *simple_scene()
{
	int n =500;
	material *red = new lambertian(new constant_texture(vec3(0.65,0.05,0.05)));
    hitable **list = new hitable*[n+1];
    texture *checker = new checker_texture(new constant_texture(vec3(0.2, 0.3,0.1)),
        new constant_texture(vec3(0.9,0.9,0.9)));
	int i=0;
    list[i++]=new sphere(vec3(0, -1000,0),1000,new lambertian(checker));
	list[i++]=new cylinder(0.5,0,1,new metal(vec3(0.8,0.85,0.88),0.0));
	list[i++]=new translate(vec3(-1.5,1.0,2),  new linear(mat3::rotate_y(20*M_PI/180) * mat3::rotate_x(20*M_PI/180),
		new solid_cylinder(0.5,-0.5,0.5,new dielectric(1.3))));
	list[i++]=new translate(vec3(1.5,1,2), new linear(mat3::rotate_z(-30*M_PI/180), 
		new solid_cylinder(0.5,-0.5,0.5,new dielectric(1.3))));
	list[i++]= new box(vec3(-0.5,0,-0.5), vec3(0.5,6,0.5),red);
	return new bvh_node(list,i);
}

hitable *random_scene2(float loc)
{
	int n =500;
	hitable **list = new hitable*[n+1];
	texture *checker = new checker_texture(new constant_texture(vec3(0.2, 0.3,0.1)), 
		new constant_texture(vec3(0.9,0.9,0.9)));
	list[0]=new sphere(vec3(0, -1000,0),1000,new lambertian(checker));
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
					list[i++]=new sphere(center, 0.2, 
						new lambertian(new constant_texture(vec3(drand48()*drand48(),drand48()*drand48(),drand48()*drand48()))));
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

	list[i++]=new translate(vec3(0,2.5,0),new linear(mat3::scale_xyz(1.5,1.5,1.5), new sphere(vec3(0,0,0),1.0,new dielectric(1.5))));
		
	//list[i++]=new translate(vec3(0,0,4),new cylinder(1.3,0,4,new dielectric(1.5)));
	
	list[i++]=new translate(vec3(-4,2.5,0),new linear(mat3::scale_xyz(1.5,1.5,1.5),
		new sphere(vec3(0,0,0),1.0, lambertian::from_image("../img/earth.jpg"))));
	list[i++]=new sphere(vec3(4,1,0),1.0, new metal(vec3(0.7,0.6,0.5),0.2));
	list[i++]=new sphere(vec3(loc,3,6),0.5,new dielectric(1.3));
		
	//return new hitable_list(list, i);
	return new bvh_node(list,i,0,0);
}

/*
hitable *cornell_box()
{
	hitable **list = new hitable*[30];
	int i=0;
	material *red = new lambertian(new constant_texture(vec3(0.65,0.05,0.05)));
	material *white = new lambertian(new constant_texture(vec3(0.73,0.73,0.73)));
	material *green = new lambertian(new constant_texture(vec3(0.12,0.45,0.15)));
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
    hitable **list = new hitable*[20];
    int i = 0;
    material *red = new lambertian( new constant_texture(vec3(0.65, 0.05, 0.05)) );
    material *white = new lambertian( new constant_texture(vec3(0.73, 0.73, 0.73)) );
    material *green = new lambertian( new constant_texture(vec3(0.12, 0.45, 0.15)) );
    material *light = new diffuse_light( new constant_texture(vec3(6,6,6)) );
	texture *checkert = new checkeruv_texture(new constant_texture(vec3(0.2, 0.3,0.1)),
	        new constant_texture(vec3(0.9,0.9,0.9)));
	material *checker = new lambertian(checkert);
	        
    list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, checker));
    list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
    list[i++] = new xz_rect(113, 443, 127, 432, 554, light);
    list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
    list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
    list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));
    hitable *boundary = new sphere(vec3(160, 100, 145), 45, new dielectric(1.5));
    //list[i++] = boundary;
 	list[i++] =  new translate(vec3(0,200,0), boundary);

	vec3 bmin=vec3(133,0,65);
    vec3 bmax=vec3(295,165,230);
    vec3 offset_xz = 0.5*(bmin+bmax);
    offset_xz.e[1]=0;
    box *b = new box(bmin,bmax,white);
	list[i++] = new translate(offset_xz, new linear(mat3::rotate_y(20*M_PI/180.0), new translate(-offset_xz,b)));
	bmin=vec3(265,0,295);
	bmax=vec3(430,330,460);
	offset_xz = 0.5*(bmin+bmax);
	offset_xz.e[1]=0;
	
 	b = new box(bmin, bmax,white);
 	list[i++] = new translate(offset_xz, new linear(mat3::rotate_y(-13*M_PI/180.0), new translate(-offset_xz,b)));

 //   list[i++] = new constant_medium(boundary, 0.1, new constant_texture(vec3(1.0, 1.0, 1.0)));
  //  list[i++] = new translate(new rotate_y(new box(vec3(0, 0, 0), vec3(165, 330, 165), white),  15), vec3(265,0,295));
    return new bvh_node(list,i,0,0);
}


hitable *cornell_smoke() {
    hitable **list = new hitable*[8];
    int i = 0;
    material *red = new lambertian( new constant_texture(vec3(0.65, 0.05, 0.05)) );
    material *white = new lambertian( new constant_texture(vec3(0.73, 0.73, 0.73)) );
    material *green = new lambertian( new constant_texture(vec3(0.12, 0.45, 0.15)) );
    material *light = new diffuse_light( new constant_texture(vec3(7, 7, 7)) );
    list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, green));
    list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
    list[i++] = new xz_rect(113, 443, 127, 432, 554, light);
    list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
    list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
    list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));
    hitable *b1 = new translate(vec3(130,0,65), new linear(mat3::rotate_y(-18*M_PI/180),
    	new box(vec3(0, 0, 0), vec3(165,165,165),white)));
    hitable *b2 = new translate(vec3(265,0,295), new linear(mat3::rotate_y(15*M_PI/180),
    	new box(vec3(0, 0, 0), vec3(165,330,165),white)));

    list[i++] = new constant_medium(b1, 0.01, new constant_texture(vec3(1.0, 1.0, 1.0)));
    list[i++] = new constant_medium(b2, 0.01, new constant_texture(vec3(0.0, 0.0, 0.0)));
    return new bvh_node(list,i,0,0);
}



hitable *final() {
    int nb = 20;
    hitable **list = new hitable*[30];
    hitable **boxlist = new hitable*[10000];
    hitable **boxlist2 = new hitable*[10000];
    material *white = new lambertian( new constant_texture(vec3(0.73, 0.73, 0.73)) );
    material *ground = new lambertian( new constant_texture(vec3(0.48, 0.83, 0.53)) );
    int b = 0;
    for (int i = 0; i < nb; i++) {
        for (int j = 0; j < nb; j++) {
            float w = 100;
            float x0 = -1000 + i*w;
            float z0 = -1000 + j*w;
            float y0 = 0;
            float x1 = x0 + w;
            float y1 = 100*(drand48()+0.01);
            float z1 = z0 + w;
            boxlist[b++] = new box(vec3(x0,y0,z0), vec3(x1,y1,z1), ground);
        }
    }
    int l = 0;
    list[l++] = new bvh_node(boxlist, b, 0, 1);
    material *light = new diffuse_light( new constant_texture(vec3(7, 7, 7)) );
    list[l++] = new xz_rect(123, 423, 147, 412, 554, light);
    vec3 center(400, 400, 200);
  //  list[l++] = new moving_sphere(center, center+vec3(30, 0, 0), 0, 1, 50, new lambertian(new constant_texture(vec3(0.7, 0.3, 0.1))));
    list[l++] = new sphere(vec3(260, 150, 45), 50, new dielectric(1.5));
    list[l++] = new sphere(vec3(0, 150, 145), 50, new metal(vec3(0.8, 0.8, 0.9), 10.0));
    hitable *boundary = new sphere(vec3(360, 150, 145), 70, new dielectric(1.5));
    list[l++] = boundary;
    list[l++] = new constant_medium(boundary, 0.2, new constant_texture(vec3(0.2, 0.4, 0.9)));
    boundary = new sphere(vec3(0, 0, 0), 5000, new dielectric(1.5));
    list[l++] = new constant_medium(boundary, 0.0001, new constant_texture(vec3(1.0, 1.0, 1.0)));
    int nx, ny, nn;

    material *emat =  lambertian::from_image("../img/earthmap.jpg");
    list[l++] = new sphere(vec3(400,200, 400), 100, emat);
    texture *pertext = new noise_texture(0.1);
    list[l++] =  new sphere(vec3(220,280, 300), 80, new lambertian( pertext ));
    int ns = 1000;
    for (int j = 0; j < ns; j++) {
        boxlist2[j] = new sphere(vec3(165*drand48(), 165*drand48(), 165*drand48()), 10, white);
    }
	list[l++] = new translate(vec3(-100,270,395),
		new linear(mat3::rotate_y(15*M_PI/180), new bvh_node(boxlist2,ns)));
    return new bvh_node(list,l,0,0);
}
*/

