#ifndef DRIVE_H
#define DRIVE_H

#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <chrono> 
#include <algorithm>
#include <queue>
#include <math.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtx/string_cast.hpp"


#include "TerrainMap.h"
#include "MatrixStack.h"

class Drive
{
public:
    Drive(glm::vec2 dir, glm::vec3 loc, TerrainHeightMap* tMap);

    void update();
    void findOrientation();
    void createModelMatrix(std::shared_ptr<MatrixStack> Model);
    void set(glm::vec2 dir, glm::vec3 loc);
    
private:
    //ground beneath the car
    glm::vec3 h_lf;
    glm::vec3 h_rf;
    glm::vec3 h_middle;
    glm::vec3 h_lb;
    glm::vec3 h_rb;

    float spead;
    glm::vec3 direction;
    glm::vec3 u;
    glm::vec3 v;
    glm::vec3 w;
    glm::vec3 location;

    //relative location of the wheels with respect to the car
    const glm::vec3 lf = glm::vec3(0.74, 0.520, 1.65);
    const glm::vec3 rf = glm::vec3(-0.74, 0.520, 1.65);
    const glm::vec3 lb = glm::vec3(0.74, 0.525, -1.355);
    const glm::vec3 rb = glm::vec3(-0.74, 0.525, -1.355);

    TerrainHeightMap* terrainHeightMap;
};


#endif