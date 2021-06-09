#include "Drive.h"

using namespace std;
using namespace glm;

void Drive::update(){

}

void Drive::findOrientation(){
    vec3 a = h_lf - h_lb;
    vec3 b = h_lf - h_rf;
    vec3 n = cross(a, b);
    u = normalize( direction - (float)(dot(direction,n)/pow(length(n), 2.0)) * n);
    v = normalize(n);
    w = normalize(cross(u, v));
    direction = u;
}

