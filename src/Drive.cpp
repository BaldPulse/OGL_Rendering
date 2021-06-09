#include "Drive.h"

using namespace std;
using namespace glm;

Drive::Drive(glm::vec2 dir, glm::vec3 loc, TerrainHeightMap* tMap){
    glm::mat4 lf_transMatrix = glm::translate(glm::mat4(1.0), loc);
    glm::mat4 rf_transMatrix = glm::translate(glm::mat4(1.0), loc);
    glm::mat4 lb_transMatrix = glm::translate(glm::mat4(1.0), loc);
    glm::mat4 rb_transMatrix = glm::translate(glm::mat4(1.0), loc);
    vec2 n = vec2(0.0, 1.0); //natrual front
    float angle = acos(dot(n, normalize(dir)));
    // cout<<"\t angle "<<angle<<endl;
    lf_transMatrix = glm::rotate(lf_transMatrix, angle, vec3(0,1,0));
    rf_transMatrix = glm::rotate(rf_transMatrix, angle, vec3(0,1,0));
    lb_transMatrix = glm::rotate(lb_transMatrix, angle, vec3(0,1,0));
    rb_transMatrix = glm::rotate(rb_transMatrix, angle, vec3(0,1,0));
    // cout<<glm::to_string(lf_transMatrix)<<endl;
    lf_transMatrix = glm::translate(lf_transMatrix, lf);
    rf_transMatrix = glm::translate(rf_transMatrix, rf);
    lb_transMatrix = glm::translate(lb_transMatrix, lb);
    rb_transMatrix = glm::translate(rb_transMatrix, rb);
    // cout<<"tire relative "<<glm::to_string(lf)<<endl;
    // cout<<glm::to_string(lf_transMatrix)<<endl;
    h_lf = (lf_transMatrix * vec4(0.0,0.0,0.0,1.0));
    h_rf = (rf_transMatrix * vec4(0.0,0.0,0.0,1.0));
    h_lb = (lb_transMatrix * vec4(0.0,0.0,0.0,1.0));
    h_rb = (rb_transMatrix * vec4(0.0,0.0,0.0,1.0));
    // cout<<"tire absolute "<<glm::to_string(h_lf)<<endl;
    this->terrainHeightMap = tMap;
    h_lf.y = terrainHeightMap->GetHeight(h_lf.x, h_lf.z);
    h_rf.y = terrainHeightMap->GetHeight(h_rf.x, h_rf.z);
    h_lb.y = terrainHeightMap->GetHeight(h_lb.x, h_lb.z);
    h_rb.y = terrainHeightMap->GetHeight(h_rb.x, h_rb.z);
    // cout<<"tire terrain lf"<<glm::to_string(h_lf)<<endl;
    // cout<<"tire terrain rf"<<glm::to_string(h_rf)<<endl;
    this->location = loc;
    this->direction = normalize(vec3(dir.x, 0.0, dir.y));
    findOrientation();
}

void Drive::set(glm::vec2 dir, glm::vec3 loc){
    glm::mat4 lf_transMatrix = glm::translate(glm::mat4(1.0), loc);
    glm::mat4 rf_transMatrix = glm::translate(glm::mat4(1.0), loc);
    glm::mat4 lb_transMatrix = glm::translate(glm::mat4(1.0), loc);
    glm::mat4 rb_transMatrix = glm::translate(glm::mat4(1.0), loc);
    vec2 n = vec2(0.0, 1.0); //natrual front
    float angle = acos(dot(n, normalize(dir)));
    // cout<<"\t angle "<<angle<<endl;
    lf_transMatrix = glm::rotate(lf_transMatrix, angle, vec3(0,1,0));
    rf_transMatrix = glm::rotate(rf_transMatrix, angle, vec3(0,1,0));
    lb_transMatrix = glm::rotate(lb_transMatrix, angle, vec3(0,1,0));
    rb_transMatrix = glm::rotate(rb_transMatrix, angle, vec3(0,1,0));
    // cout<<glm::to_string(lf_transMatrix)<<endl;
    lf_transMatrix = glm::translate(lf_transMatrix, lf);
    rf_transMatrix = glm::translate(rf_transMatrix, rf);
    lb_transMatrix = glm::translate(lb_transMatrix, lb);
    rb_transMatrix = glm::translate(rb_transMatrix, rb);
    // cout<<"tire relative "<<glm::to_string(lf)<<endl;
    // cout<<glm::to_string(lf_transMatrix)<<endl;
    h_lf = (lf_transMatrix * vec4(0.0,0.0,0.0,1.0));
    h_rf = (rf_transMatrix * vec4(0.0,0.0,0.0,1.0));
    h_lb = (lb_transMatrix * vec4(0.0,0.0,0.0,1.0));
    h_rb = (rb_transMatrix * vec4(0.0,0.0,0.0,1.0));
    // cout<<"tire absolute "<<glm::to_string(h_lf)<<endl;
    h_lf.y = terrainHeightMap->GetHeight(h_lf.x, h_lf.z);
    h_rf.y = terrainHeightMap->GetHeight(h_rf.x, h_rf.z);
    h_lb.y = terrainHeightMap->GetHeight(h_lb.x, h_lb.z);
    h_rb.y = terrainHeightMap->GetHeight(h_rb.x, h_rb.z);
    cout<<"tire terrain lf"<<glm::to_string(h_lf)<<endl;
    cout<<"tire terrain rf"<<glm::to_string(h_rf)<<endl;
    this->location = loc;
    this->direction = normalize(vec3(dir.x, 0.0, dir.y));
    findOrientation();
}

void Drive::update(){


}

void Drive::findOrientation(){
    vec3 a = h_lf - h_rb;
    vec3 b = h_lb - h_rf;
    cout<<"a "<<glm::to_string(a)<<endl;
    cout<<"b "<<glm::to_string(b)<<endl;
    vec3 n = cross(a, b);
    cout<<"n "<<glm::to_string(n)<<endl;
    vec3 a_wheel = h_lf-h_lb;
    v = normalize(n);
    u = normalize( a_wheel - dot(a_wheel,v) * v);
    // w = normalize(cross(u, v));
    w = normalize(cross(u, v));
    direction = u;
    // cout<<"uvw\n"<<glm::to_string(u)<<endl<<glm::to_string(v)<<endl<<glm::to_string(w)<<endl;
}

void Drive::createModelMatrix(std::shared_ptr<MatrixStack> Model){
    vec3 translateMat = (h_lb+h_lf+h_rb+h_rf)*0.25f; //translate from wheel to middle
    cout<<"translateMat "<<glm::to_string(translateMat)<<endl;
    Model->translate(translateMat);
    vec3 default_u = vec3(0.0, 0.0, 1.0); //natural front
    vec3 axis = normalize(cross(default_u,u));
    float angle = acos(dot(default_u, u));
    Model->rotate(angle, axis);
    // cout<<"wheel terrain loc "<<glm::to_string(h_lf)<<endl;
}

