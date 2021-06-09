/*
 * Program 4 example with diffuse and spline camera PRESS 'g'
 * CPE 471 Cal Poly Z. Wood + S. Sueda + I. Dunn (spline D. McGirr)
 */
#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <chrono> 
#include <algorithm>
#include <queue>
#include <math.h>
#include <stdlib.h> 
#include <time.h>       /* time */

#include "GLSL.h"
#include "Program.h"
#include "Shape.h"
#include "MatrixStack.h"
#include "WindowManager.h"
#include "Texture.h"
#include "stb_image.h"
#include "Bezier.h"
#include "Spline.h"
#include "Application_Helpers.h"
#include "TerrainMap.h"
#include "Drive.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader/tiny_obj_loader.h>
#define PI 3.1415927
#define MAX_TURN 0.55
// value_ptr for glm
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Application : public EventCallbacks
{

public:

	WindowManager * windowManager = nullptr;

	// Our shader program - use this one for Blinn-Phong has diffuse
	std::shared_ptr<Program> prog;

	//Our shader program for textures
	std::shared_ptr<Program> texProg;

	//Our shader program for skybox
	std::shared_ptr<Program> cubeProg;

	//Shader for shadow mapping
	std::shared_ptr<Program> shadowProg;

	TerrainHeightMap* terrainHeightMap;

	//our geometry
	std::shared_ptr<Shape> cube;
	std::shared_ptr<std::vector<Shape>> car;
	std::shared_ptr<std::vector<Shape>> lf_wheel;
	std::shared_ptr<std::vector<Shape>> rf_wheel;
	std::shared_ptr<std::vector<Shape>> lb_wheel;
	std::shared_ptr<std::vector<Shape>> rb_wheel;

	std::shared_ptr<std::vector<Shape>> cactus;
	tinyobj::material_t cactus_material;
	float cactusX, cactusY;
	std::shared_ptr<std::vector<Shape>> theBunny;
	std::shared_ptr<std::vector<Shape>> theCube;
	std::shared_ptr<std::vector<tinyobj::material_t>> car_material;
	std::shared_ptr<std::vector<Shape>> desert;
	std::shared_ptr<std::vector<tinyobj::material_t>> desert_material;

	std::shared_ptr<Drive> carDrive;

	struct alpha_compare{
		std::shared_ptr<std::vector<tinyobj::material_t>> material_list;
		bool operator()(Shape a, Shape b){
			return material_list->at(a.mtlBuf[0]).dissolve > material_list->at(b.mtlBuf[0]).dissolve;
		}
	};


    //render queue struct for each shape
    struct DrawParam{
        glm::mat4 V;
        glm::mat4 M;
        glm::mat4 P;
		float f;
        std::shared_ptr<Program> prog;
        std::vector<Shape>::iterator shape;
        tinyobj::material_t* material;
        std::shared_ptr<TexMap> texture;
        void operator()();
    };

    std::shared_ptr<std::queue<DrawParam>> shadow_queue; //shadow mapping
    std::shared_ptr<std::queue<DrawParam>> render_queue; //actual scene
	std::shared_ptr<TexMap> desert_texture;
	std::shared_ptr<TexMap> cactus_texture;
	unsigned int oceanMapTexture;
	unsigned int skyMapTexture;

	//animation data
	float lightTrans = 0;

	unsigned int SHADOW_WIDTH=1024, SHADOW_HEIGHT=1024; //shadow map size
	unsigned int depthMap;
    unsigned int depthMapFBO;

	//camera
	double posX, posY;
	bool lmb = false;
	bool mv_forward = false, mv_back = false, mv_left = false, mv_right = false;
	double g_phi=0.0, g_theta=0.0;
	glm::vec3 view = glm::vec3(0, 0, 1);
	glm::vec3 strafe = glm::vec3(1, 0, 0);
	glm::vec3 g_eye = glm::vec3(0, 1, 3);
	glm::vec3 car_loc;
	glm::vec3 g_lookAt ;//= glm::vec3(0, 1, -4);
	glm::vec3 g_usereye = g_eye;

	float framDistanceTraveled = 0.0;
	float wheel_pos = 0.0;

	float gas = 0.0;
    float turn = 0.0;

	glm::mat4 lightView;
	glm::mat4 lightProjection;
	glm::vec3 direction_light;

	float renderTime = 0.0;
	float testMovex = -0.74;
	float testMovey = 0.53;
	float testMovez = -1.64;
	const float rbMovex = 0.74;
	const float rbMovey = 0.525;
	const float rbMovez = 1.355;
	const float lbMovex = -0.74;
	const float lbMovey = 0.525;
	const float lbMovez = 1.355;
	
	const float rfMovex = 0.74;
	const float rfMovey = 0.520;
	const float rfMovez = -1.65;
	const float lfMovex = -0.74;
	const float lfMovey = 0.520;
	const float lfMovez = -1.65;

	Spline splinepath[2];
	bool goCamera = false;

	void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	
	void mouseCallback(GLFWwindow *window, int button, int action, int mods);

	void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

	void scrollCallback(GLFWwindow* window, double deltaX, double deltaY);

	void resizeCallback(GLFWwindow *window, int width, int height);

	void write_to_obj(std::shared_ptr<std::vector<Shape>> mesh, std::vector<tinyobj::shape_t>& shapes);

	void car_to_obj(std::shared_ptr<std::vector<Shape>> car,
		std::shared_ptr<std::vector<Shape>> lf_wheel,
		std::shared_ptr<std::vector<Shape>> rf_wheel,
		std::shared_ptr<std::vector<Shape>> lb_wheel,
		std::shared_ptr<std::vector<Shape>> rb_wheel,
		std::vector<tinyobj::shape_t>& shapes);

	void draw_wheels(std::shared_ptr<MatrixStack> Model, std::shared_ptr<MatrixStack> Projection);

	unsigned int createSky(std::string dir, std::vector<std::string> faces);

	void init(const std::string& resourceDirectory);

	void initGeom(const std::string& resourceDirectory);

    //helper function to pass material data to the GPU
	friend void SetMaterial(std::shared_ptr<Program> curS, const tinyobj::material_t &material, float ka=1.0f);

	//helper function to pass texture data to the GPU
	friend void SetTexture(std::shared_ptr<Program> curS, const TexMap &texMap);

	/* helper function to set model trasnforms */
  	void SetModel(glm::vec3 trans, float rotY, float rotX, float sc, std::shared_ptr<Program> curS);

	void setModel(std::shared_ptr<Program> prog, std::shared_ptr<MatrixStack>M);

	void updateView(float frametime);

   	/* camera controls - do not change */
	void SetView(std::shared_ptr<Program>  shader);

   	void updateUsingCameraPath(float frametime);

    void renderQueue(std::shared_ptr<std::queue<DrawParam>> renderQueue);

	void render(float frametime);

	void obj_to_terrain_map();
};


#endif