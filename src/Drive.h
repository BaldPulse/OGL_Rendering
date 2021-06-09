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

class Drive
{
public:
    void update();
    void findOrientation();
    
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
    const glm::vec2 lf = vec2(0.0, 0.0);
    const glm::vec2 rf = vec2(0.0, 0.0);
    const glm::vec2 lb = vec2(0.0, 0.0);
    const glm::vec2 rb = vec2(0.0, 0.0);


};


#endif