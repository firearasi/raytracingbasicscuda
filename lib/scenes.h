#ifndef SCENESH
#define SCENESH
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "ray.h"
#include "hitable_list.h"
#include "box.h"
#include "triangle.h"
#include "transformations.h"
#include "bvh_node.h"
#include "hitable.h"
#include "aarect.h"
#include "camera.h"
#include "material.h"
#include "texture.h"
#include "constant_medium.h"
#include "cylinder.h"

hitable *random_scene();

hitable *box_scene();

hitable *simple_scene();

hitable *random_scene2(float loc);

/*
hitable *cornell_box();

hitable *cornell_balls();

hitable *cornell_smoke();

hitable *final();
*/
#endif
