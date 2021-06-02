#ifndef APPLICATION_HELPER_H
#define APPLICATION_HELPER_H

#include <iostream>
#include <glad/glad.h>
#include <chrono> 
#include <algorithm>
#include <queue>

#include "GLSL.h"
#include "Program.h"
#include "Shape.h"
#include "MatrixStack.h"
#include "WindowManager.h"
#include "Texture.h"
#include "stb_image.h"
#include "Bezier.h"
#include "Spline.h"


struct TexMap{
    Texture *map_ka;
    Texture *map_kd;
    Texture *map_ks;
};

void simple_shader_init_uniforms_attributes(std::shared_ptr<Program> prog, std::string vert_shader_path, std::string frag_shader_path);
void texture_shader_init_uniforms_attributes(std::shared_ptr<Program> prog, std::string vert_shader_path, std::string frag_shader_path);
void cube_shader_init_uniforms_attributes(std::shared_ptr<Program> prog, std::string vert_shader_path, std::string frag_shader_path);
void shadow_shader_init_uniforms_attributes(std::shared_ptr<Program> prog, std::string vert_shader_path, std::string frag_shader_path);

void load_texture(std::shared_ptr<TexMap> texMap, std::string texDir, tinyobj::material_t material);

unsigned int create_depthMap(unsigned int shadow_width, unsigned int shadow_height);
unsigned int bind_depthMap_to_framebuffer(unsigned int depthMap);
#endif