#ifndef TERRAINMAP_H
#define TERRAINMAP_H

#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <chrono> 
#include <algorithm>
#include <queue>
#include <math.h>


#include <tiny_obj_loader/tiny_obj_loader.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

void add_vert_to_terrain(const int &x,const int &z, const float &v_x, const float &v_z, const float &v_y, 
    float*terrain_map, float *terrain_map_density, char* terrain_map_set);

void average_surrounding(float*terrain_map, int i, int j);

void obj_to_terrain_map();

#endif