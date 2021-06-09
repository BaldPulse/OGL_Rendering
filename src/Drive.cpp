#include "Drive.h"

using namespace std;
using namespace glm;

Drive::Drive(glm::vec2 dir, glm::vec3 loc, TerrainHeightMap* tMap){
    vec2 n = vec2(1.0, 0.0);
    float angle = acos(dot(n, normalize(dir)));
    glm::mat4 lf_transMatrix = glm::translate(glm::mat4(1.0), loc);
    glm::mat4 rf_transMatrix = glm::translate(glm::mat4(1.0), loc);
    glm::mat4 lb_transMatrix = glm::translate(glm::mat4(1.0), loc);
    glm::mat4 rb_transMatrix = glm::translate(glm::mat4(1.0), loc);
    lf_transMatrix = glm::rotate(lf_transMatrix, angle, vec3(0,1,0));
    rf_transMatrix = glm::rotate(rf_transMatrix, angle, vec3(0,1,0));
    lb_transMatrix = glm::rotate(lb_transMatrix, angle, vec3(0,1,0));
    rb_transMatrix = glm::rotate(rb_transMatrix, angle, vec3(0,1,0));
    lf_transMatrix = glm::translate(lf_transMatrix, lf);
    rf_transMatrix = glm::translate(rf_transMatrix, rf);
    lb_transMatrix = glm::translate(lb_transMatrix, lb);
    rb_transMatrix = glm::translate(rb_transMatrix, rb);
    h_lf = (vec4(0.0,0.0,0.0,1.0) * lf_transMatrix);
    h_rf = (vec4(0.0,0.0,0.0,1.0) * rf_transMatrix);
    h_lb = (vec4(0.0,0.0,0.0,1.0) * lb_transMatrix);
    h_rb = (vec4(0.0,0.0,0.0,1.0) * rb_transMatrix);
    this->terrainHeightMap = tMap;
    h_lf.y = terrainHeightMap->GetHeight(h_lf.x, h_lf.z);
    h_rf.y = terrainHeightMap->GetHeight(h_rf.x, h_rf.z);
    h_lb.y = terrainHeightMap->GetHeight(h_lb.x, h_lb.z);
    h_rb.y = terrainHeightMap->GetHeight(h_rb.x, h_rb.z);
    this->location = loc;
    this->direction = normalize(vec3(dir.x, 0.0, dir.y));
    findOrientation();
}

void Drive::update(){


}

void Drive::findOrientation(){
    vec3 a = h_lf - h_lb;
    vec3 b = h_lf - h_rf;
    vec3 n = cross(a, b);
    // u = normalize( direction - (float)(dot(direction,n)/pow(length(n), 2.0)) * n);
    u = normalize(a);
    v = normalize(n);
    // w = normalize(cross(u, v));
    w = normalize(b);
    direction = u;
}

void Drive::createModelMatrix(std::shared_ptr<MatrixStack> Model){
    vec3 translateMat = -h_lf.x * u - h_lf.y * v - h_lf.z * w; //translate from wheel to middle
    Model->translate(translateMat);
    vec3 default_u = vec3(1.0, 0.0, 0.0);
    vec3 axis = normalize(cross(default_u, u));
    float angle = acos(dot(default_u, u));
    Model->rotate(angle, axis);
}

