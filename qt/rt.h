#ifndef RT_H
#define RT_H
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "ray.h"
#include "hitable_list.h"
#include "bvh_node.h"
#include "hitable.h"
#include "camera.h"
#include "material.h"
#include "texture.h"
#include  <map>
#include <vector>
#include <fstream>
#include <thread>
#include "scene.h"
#include <string.h>
#include <QImage>
#include <QDebug>

using namespace std;

vec3 color (const ray& r, hitable *world, int depth=0);

class Scene
{
public:
    int nx,ny,ns;
    hitable *world;
    camera* cam;
    float *img;
    QImage qimg;
    Scene(hitable *w,  camera* c, int _nx=1920, int _ny=1080,int _ns=20)
        :nx(_nx),ny(_ny),ns(_ns),world(w),cam(c),qimg(nx,ny,QImage::Format_RGB32)
    {
        qDebug() << "QImg Size" << qimg.size();
    }
    vec3 color (const ray& r, int depth=0);
    void render_ppm_pixel(int i, int j);
    int render_ppm(string filename="pic.ppm");

    void render_qimg_pixel(int i, int j);
    int render_qimg();

};

#endif // RT_H
