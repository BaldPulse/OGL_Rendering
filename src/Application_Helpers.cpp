#include "Application_Helpers.h"

using namespace std;

void simple_shader_init_uniforms_attributes(std::shared_ptr<Program> prog, std::string vert_shader_path, std::string frag_shader_path){
    /*
    init and add uniform variables and attributes for simple shaders
    */
    prog->setVerbose(true);
    prog->setShaderNames(vert_shader_path, frag_shader_path);
    prog->init();
    prog->addUniform("P");
    prog->addUniform("V");
    prog->addUniform("M");
    prog->addUniform("MatAmb");
    prog->addUniform("MatDif");
    prog->addUniform("MatSpec");
    prog->addUniform("MatShine");
    prog->addUniform("MatEmit");
    prog->addUniform("Alpha");
    prog->addUniform("lightPos");
    prog->addAttribute("vertPos");
    prog->addAttribute("vertNor");
    prog->addAttribute("vertTex"); 
}
void texture_shader_init_uniforms_attributes(std::shared_ptr<Program> prog, std::string vert_shader_path, std::string frag_shader_path){
    /*
    init and add uniform variables and attributes for texture shaders
    */
    prog->setVerbose(true);
    prog->setShaderNames(vert_shader_path, frag_shader_path);
    prog->init();
    prog->addUniform("P");
    prog->addUniform("V");
    prog->addUniform("M");
    prog->addUniform("flip");
    prog->addUniform("map_color");
    prog->addUniform("use_map_color");
    prog->addUniform("map_ka");
    prog->addUniform("use_map_ka");
    prog->addUniform("map_kd");
    prog->addUniform("use_map_kd");
    prog->addUniform("MatAmb");
    prog->addUniform("MatDif");
    prog->addUniform("MatSpec");
    prog->addUniform("MatShine");
    prog->addUniform("MatEmit");
    prog->addUniform("Alpha");
    prog->addUniform("lightPos");
    prog->addAttribute("vertPos");
    prog->addAttribute("vertNor");
    prog->addAttribute("vertTex");
}


void cube_shader_init_uniforms_attributes(std::shared_ptr<Program> prog, std::string vert_shader_path, std::string frag_shader_path){
    /*
    init and add uniform variables and attributes for skybox(cube) shaders
    */
    prog->setVerbose(true);
    prog->setShaderNames(vert_shader_path, frag_shader_path);
    prog->init();
    prog->addUniform("P");
    prog->addUniform("V");
    prog->addUniform("M");
    prog->addUniform("skybox");
    prog->addAttribute("vertPos");
    prog->addAttribute("vertNor");
}