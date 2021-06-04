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
    prog->addUniform("lightDir");
    prog->addUniform("lightSpaceMatrix");
    prog->addUniform("shadowMap");
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
    prog->addUniform("map_ks");
    prog->addUniform("use_map_ks");
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
    prog->addUniform("lightDir");
    prog->addUniform("lightSpaceMatrix");
    prog->addUniform("shadowMap");
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
void shadow_shader_init_uniforms_attributes(std::shared_ptr<Program> prog, std::string vert_shader_path, std::string frag_shader_path){
    /*
    init and add uniform variables and attributes for shadow shaders
    */
    prog->setVerbose(false);//shut up 
    prog->setShaderNames(vert_shader_path, frag_shader_path);
    prog->init();
    prog->addUniform("P");
    prog->addUniform("V");
    prog->addUniform("M");
    prog->addAttribute("vertPos");
}
void load_texture(std::shared_ptr<TexMap> texMap, std::string texDir, tinyobj::material_t material){

    /*
    read and store different textures from material in texMap
    */
    if(material.diffuse_texname!=""){
        texMap->map_kd = new Texture();
        texMap->map_kd->setFilename((texDir+material.diffuse_texname).c_str());
        texMap->map_kd->init();
        texMap->map_kd->setUnit(0);
        texMap->map_kd->setWrapModes(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    }
    else
        texMap->map_kd = NULL;
    
    if(material.ambient_texname!=""){
        texMap->map_ka = new Texture();
        texMap->map_ka->setFilename((texDir+material.ambient_texname).c_str());
        texMap->map_ka->init();
        texMap->map_ka->setUnit(1);
        texMap->map_ka->setWrapModes(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    }
    else
        texMap->map_ka = NULL;

    if(material.specular_texname!=""){
        texMap->map_ks = new Texture();
        texMap->map_ks->setFilename((texDir+material.ambient_texname).c_str());
        texMap->map_ks->init();
        texMap->map_ks->setUnit(2);
        texMap->map_ks->setWrapModes(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    }
    else
        texMap->map_ks = NULL;

}
unsigned int create_depthMap(unsigned int shadow_width, unsigned int shadow_height){
    /*
    creates and returns a depthMap texture
    */
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
                shadow_width, shadow_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    return depthMap;
}
unsigned int bind_depthMap_to_framebuffer(unsigned int depthMap){
    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);  
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    return depthMapFBO;
}
void bind_depthMap_to_shadowMap(std::shared_ptr<Program> prog, unsigned int depthMap, int unit){
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glUniform1i(prog->getUniform("shadowMap"), unit);
}