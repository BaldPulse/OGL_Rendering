/*
 * Program 4 example with diffuse and spline camera PRESS 'g'
 * CPE 471 Cal Poly Z. Wood + S. Sueda + I. Dunn (spline D. McGirr)
 */

#include "Application.h"


using namespace std;
using namespace glm;


void Application::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_Q && action == GLFW_PRESS){
        testMovez += 0.005;
    }
    if (key == GLFW_KEY_E && action == GLFW_PRESS){
        testMovez -= 0.005;
    }
    if (key == GLFW_KEY_T && action == GLFW_PRESS){
        testMovey += 0.005;
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS){
        testMovey -= 0.005;
    }
    if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }
    if (key == GLFW_KEY_G && action == GLFW_RELEASE) {
        goCamera = !goCamera;
    }
    if (key == GLFW_KEY_W) {
        if(action == GLFW_PRESS){
            mv_forward = true;
        }
        else if(action == GLFW_RELEASE){
            mv_forward = false;
        }
    }
    if (key == GLFW_KEY_S) {
        if(action == GLFW_PRESS){
            mv_back = true;
        }
        else if(action == GLFW_RELEASE){
            mv_back = false;
        }
    }
    if (key == GLFW_KEY_A) {
        if(action == GLFW_PRESS){
            mv_left = true;
        }
        else if(action == GLFW_RELEASE){
            mv_left = false;
        }
    }
    if (key == GLFW_KEY_D) {
        if(action == GLFW_PRESS){
            mv_right = true;
        }
        else if(action == GLFW_RELEASE){
            mv_right = false;
        }
    }
}

void Application::mouseCallback(GLFWwindow *window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        lmb = true;
            glfwGetCursorPos(window, &posX, &posY);
            cout << "started adjusting camera" << endl;
        //  cout << "g_phi " << g_phi <<" cos "<<cos(g_phi) <<  "\ng_theta " << g_theta<<" cos "<<cos(g_theta) << endl;
    }
    if (action == GLFW_RELEASE)
    {
        lmb = false;
            glfwGetCursorPos(window, &posX, &posY);
            cout << "ended adjusting camera" << endl;
    }
}

void Application::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if(lmb == true){
        glfwGetCursorPos(window, &xpos, &ypos);
        // cout << "X " << xpos <<  " Y " << ypos << endl;
        g_theta += (xpos - posX)*0.02;
        g_phi -= (ypos - posY)*0.02;
        if(g_theta >= 2.0f*glm::pi<float>()){
            g_theta = 0.0f;
        }
        else if(g_theta <= 0.0f){
            g_theta = 2.0f*glm::pi<float>();
        }
        if(g_phi >= 0.5f*glm::pi<float>()-0.00001){
            g_phi = 0.5f*glm::pi<float>()-0.00001;
        }
        else if(g_phi <= -0.5f*glm::pi<float>()+0.00001){
            g_phi = -0.5f*glm::pi<float>()+0.00001;
        }
        posX = xpos;
        posY = ypos;
        // cout << "g_phi " << g_phi <<" cos p "<<cos(g_phi) <<  "\ng_theta " << g_theta<<" cos y "<<cos(g_theta) << endl;
    }
}

void Application::scrollCallback(GLFWwindow* window, double deltaX, double deltaY) {
    cout << "xDel + yDel " << deltaX << " " << deltaY << endl;
    //fill in for game camera
}

void Application::resizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Application::write_to_obj(shared_ptr<vector<Shape>> mesh, vector<tinyobj::shape_t>& shapes){
        cout<<"shape size "<<shapes.size()<<endl;
        for(int i=0; i<shapes.size(); i++){
            mesh->push_back(Shape());
            mesh->back().createShape(shapes[i]);
            mesh->back().measure();
            mesh->back().init();
        }
}

void Application::car_to_obj(std::shared_ptr<std::vector<Shape>> car,
		std::shared_ptr<std::vector<Shape>> lf_wheel,
		std::shared_ptr<std::vector<Shape>> rf_wheel,
		std::shared_ptr<std::vector<Shape>> lb_wheel,
		std::shared_ptr<std::vector<Shape>> rb_wheel,
		std::vector<tinyobj::shape_t>& shapes){

    vector<string> rb_names = { "Plane.097_091-0-91.001_black_of",
                                "Plane.079_012-0-12.001_black_bri.001",
                                "Plane.074_003-0-3.001_cromo.002",
                                "Plane.024_001-0-1.001_cromo_2.003",
                                "Plane.028_001-0-1-2_001-0-1.001_black_osfu.003"};
    vector<string> lb_names = { "Plane.125_091-0-91.003_black_of",
                                "Plane.131_012-0-12.003_black_bri.001",
                                "Plane.132_003-0-3.003_cromo.002",
                                "Plane.133_001-0-1.003_cromo_2.003",
                                "Plane.135_001-0-1-2_001-0-1.003_black_osfu.003"};
    vector<string> rf_names = { "Plane.096_091-0-91_black_of",
                                "Plane.081_045-0-45_cromo.002",
                                "Plane.078_012-0-12_black_bri",
                                "Plane.023_001-0-1_cromo_2.003",
                                "Plane.121_001-0-1-2_001-0-1.005_black_osfu.003"};
    vector<string> lf_names = { "Plane.117_091-0-91.002_black_of",
                                "Plane.122_012-0-12.002_black_bri.001",
                                "Plane.123_003-0-3.002_cromo.002",
                                "Plane.124_001-0-1.002_cromo_2.003",
                                "Plane.134_001-0-1-2_001-0-1.002_black_osfu.003"};
    cout<<"shape size "<<shapes.size()<<endl;
    for(int i=0; i<shapes.size(); i++){
        string name = shapes[i].name;
        auto iter = find(rb_names.begin(), rb_names.end(), name);
        if(iter != rb_names.end()){
            rb_wheel->push_back(Shape());
            rb_wheel->back().createShape(shapes[i]);
            rb_wheel->back().measure();
            rb_wheel->back().init();
            continue;
        }
        iter = find(lb_names.begin(), lb_names.end(), name);
        if(iter != lb_names.end()){
            lb_wheel->push_back(Shape());
            lb_wheel->back().createShape(shapes[i]);
            lb_wheel->back().measure();
            lb_wheel->back().init();
            continue;
        }
        iter = find(rf_names.begin(), rf_names.end(), name);
        if(iter != rf_names.end()){
            rf_wheel->push_back(Shape());
            rf_wheel->back().createShape(shapes[i]);
            rf_wheel->back().measure();
            rf_wheel->back().init();
            continue;
        }
        iter = find(lf_names.begin(), lf_names.end(), name);
        if(iter != lf_names.end()){
            lf_wheel->push_back(Shape());
            lf_wheel->back().createShape(shapes[i]);
            lf_wheel->back().measure();
            lf_wheel->back().init();
            continue;
        }

        car->push_back(Shape());
        car->back().createShape(shapes[i]);
        car->back().measure();
        car->back().init();
    }
}

void Application::draw_wheels(std::shared_ptr<MatrixStack> Model, std::shared_ptr<MatrixStack> Projection){
    wheel_pos = -gas * renderTime;
    Model->pushMatrix();
    Model->translate(vec3(0.0-rbMovex,0.0-rbMovey,0.0-rbMovez));
    Model->rotate(wheel_pos, vec3(1.0, 0.0, 0.0));
    Model->translate(vec3(0.0+rbMovex,0.0+rbMovey,0.0+rbMovez));
    for(auto iter=rb_wheel->begin(); iter!=rb_wheel->end(); iter++){
        DrawParam thisParam= {
            glm::lookAt(g_eye, g_lookAt, vec3(0, 1, 0)),
            Model->topMatrix(),
            Projection->topMatrix(),
            0.1,
            prog,
            iter,
            &(car_material->at(iter->mtlBuf[0])),
            NULL
        };
        render_queue->push(thisParam);
        DrawParam shadowParam={
                lightView,
                Model->topMatrix(),
                lightProjection,
                0.0,
                shadowProg,
                iter,
                NULL,
                NULL
            };
        shadow_queue->push(shadowParam);
    }
    Model->popMatrix();
    
    Model->pushMatrix();
    Model->translate(vec3(0.0-lbMovex,0.0-lbMovey,0.0-lbMovez));
    Model->rotate(wheel_pos, vec3(1.0, 0.0, 0.0));
    Model->translate(vec3(0.0+lbMovex,0.0+lbMovey,0.0+lbMovez));
    for(auto iter=lb_wheel->begin(); iter!=lb_wheel->end(); iter++){
        DrawParam thisParam= {
            glm::lookAt(g_eye, g_lookAt, vec3(0, 1, 0)),
            Model->topMatrix(),
            Projection->topMatrix(),
            0.1,
            prog,
            iter,
            &(car_material->at(iter->mtlBuf[0])),
            NULL
        };
        render_queue->push(thisParam);
        DrawParam shadowParam={
                lightView,
                Model->topMatrix(),
                lightProjection,
                0.0,
                shadowProg,
                iter,
                NULL,
                NULL
            };
        shadow_queue->push(shadowParam);
    }
    Model->popMatrix();

    Model->pushMatrix();
    Model->translate(vec3(0.0-rfMovex,0.0-rfMovey,0.0-rfMovez));
    Model->rotate(turn*MAX_TURN, vec3(0.0, 1.0, 0.0));
    Model->rotate(wheel_pos, vec3(1.0, 0.0, 0.0));
    Model->translate(vec3(0.0+rfMovex,0.0+rfMovey,0.0+rfMovez));
    for(auto iter=rf_wheel->begin(); iter!=rf_wheel->end(); iter++){
        DrawParam thisParam= {
            glm::lookAt(g_eye, g_lookAt, vec3(0, 1, 0)),
            Model->topMatrix(),
            Projection->topMatrix(),
            0.1,
            prog,
            iter,
            &(car_material->at(iter->mtlBuf[0])),
            NULL
        };
        render_queue->push(thisParam);
        DrawParam shadowParam={
                lightView,
                Model->topMatrix(),
                lightProjection,
                0.0,
                shadowProg,
                iter,
                NULL,
                NULL
            };
        shadow_queue->push(shadowParam);
    }
    Model->popMatrix();

    Model->pushMatrix();
    Model->translate(vec3(0.0-lfMovex,0.0-lfMovey,0.0-lfMovez));
    Model->rotate(turn*MAX_TURN, vec3(0.0, 1.0, 0.0));
    Model->rotate(wheel_pos, vec3(1.0, 0.0, 0.0));
    Model->translate(vec3(0.0+lfMovex,0.0+lfMovey,0.0+lfMovez));
    for(auto iter=lf_wheel->begin(); iter!=lf_wheel->end(); iter++){
        DrawParam thisParam= {
            glm::lookAt(g_eye, g_lookAt, vec3(0, 1, 0)),
            Model->topMatrix(),
            Projection->topMatrix(),
            0.1,
            prog,
            iter,
            &(car_material->at(iter->mtlBuf[0])),
            NULL
        };
        render_queue->push(thisParam);
        DrawParam shadowParam={
                lightView,
                Model->topMatrix(),
                lightProjection,
                0.0,
                shadowProg,
                iter,
                NULL,
                NULL
            };
        shadow_queue->push(shadowParam);
    }
    Model->popMatrix();
}

unsigned int Application::createSky(string dir, vector<string> faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(false);
    for(GLuint i = 0; i < faces.size(); i++) {
        unsigned char *data =
            stbi_load((dir+faces[i]).c_str(), &width, &height, &nrChannels, 0);
        if (data) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
        0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else {
        cout << "failed to load: " << (dir+faces[i]).c_str() << endl;
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    cout << " creating cube map any errors : " << glGetError() << endl;
    return textureID;
}

void Application::init(const std::string& resourceDirectory)
{
    GLSL::checkVersion();

    srand(time(NULL));
    cactusX = (float)rand()/RAND_MAX*40.0 - 20.0;
    cactusY = (float)rand()/RAND_MAX*40.0 - 20.0;

    // Set background color.
    glClearColor(.72f, .84f, 1.06f, 1.0f);
    // Enable z-buffer test.
    glEnable(GL_DEPTH_TEST);
    // Enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

    g_theta = 3.0*PI/2.0;

    // Initialize the GLSL program that we will use for local shading
    prog = make_shared<Program>();
    simple_shader_init_uniforms_attributes(prog, resourceDirectory + "/simple_vert.glsl", resourceDirectory + "/simple_frag.glsl");


    // Initialize the GLSL program that we will use for texture mapping
    texProg = make_shared<Program>();
    texture_shader_init_uniforms_attributes(texProg, resourceDirectory + "/tex_vert.glsl", resourceDirectory + "/tex_frag0.glsl");

    // Initialize the GLSL program that we will use for skybox shading
    cubeProg = make_shared<Program>();
    cube_shader_init_uniforms_attributes(cubeProg, resourceDirectory + "/cube_vert.glsl", resourceDirectory + "/cube_frag.glsl");

    shadowProg = make_shared<Program>();
    shadow_shader_init_uniforms_attributes(shadowProg, resourceDirectory + "/shadow_vert.glsl", resourceDirectory + "/shadow_frag.glsl");

    // init splines up and down
    splinepath[0] = Spline(glm::vec3(0,1,3), glm::vec3(-1,1,1), glm::vec3(3, 1, 3), glm::vec3(2,1,0), 5);
    splinepath[1] = Spline(glm::vec3(2,1,0), glm::vec3(1.5,0,1), glm::vec3(1, 2, 2), glm::vec3(3,2,-3), 5);

    depthMap = create_depthMap(1024, 1024);
    depthMapFBO = bind_depthMap_to_framebuffer(depthMap);

    terrainHeightMap = new TerrainHeightMap;
    terrainHeightMap->LoadHeightMap("../resources/Desert/Dune_hmap.txt");
    carDrive = make_shared<Drive>(vec2(1.0,0.0), vec3(0.0, 0.0, 0.0), terrainHeightMap);
}

void Application::initGeom(const std::string& resourceDirectory)
{

    bool rc;
    string errStr;
    // Initialize ground mesh.
    vector<tinyobj::shape_t> TOshapesB;
    desert_material = make_shared<vector<tinyobj::material_t>>();
    // load in the mesh and make the shape(s)
    rc = tinyobj::LoadObj(TOshapesB, *desert_material, errStr, 
        (resourceDirectory + "/Desert" + "/Dune_LOD1.obj").c_str(), (resourceDirectory+"/Desert/").c_str());
    if (!rc) {
        cerr << errStr << endl;
    } else {
        desert = make_shared<vector<Shape>>();
        write_to_obj(desert, TOshapesB);
    }
    // setup ground material
    desert_texture = make_shared<TexMap>();
    load_texture(desert_texture, resourceDirectory+"/Desert/", desert_material->at(0));

    // Initialize car mesh.
    vector<tinyobj::shape_t> TOshapesC;
    // load in the mesh and make the shape(s)
    car_material = make_shared<vector<tinyobj::material_t>>();
    rc = tinyobj::LoadObj(TOshapesC, *car_material, errStr, 
        (resourceDirectory + "/Toyota_Tacoma" + "/Toyota_Tacoma_2020.obj").c_str(), (resourceDirectory+"/Toyota_Tacoma/").c_str());
    if (!rc) {
        cerr << errStr << endl;
    } else {
        car = make_shared<vector<Shape>>();
        lf_wheel = make_shared<vector<Shape>>();
        rf_wheel = make_shared<vector<Shape>>();
        lb_wheel = make_shared<vector<Shape>>();
        rb_wheel = make_shared<vector<Shape>>();
        car_to_obj(car, lf_wheel, rf_wheel, lb_wheel, rb_wheel, TOshapesC);
    }
    cout<<"car mat size "<<car_material->size()<<endl;
    //To ensure transparency works with z-buffer testing, sort obj vector in terms of alpha value
    alpha_compare comp;
    comp.material_list = car_material;
    std::sort(car->begin(), car->end(), comp);



    vector<tinyobj::shape_t> TOshapesD;
    vector<tinyobj::material_t> objMaterialsD;
    //load in the mesh and make the shape(s)
    rc = tinyobj::LoadObj(TOshapesD, objMaterialsD, errStr, (resourceDirectory + "/cube.obj").c_str());
    if (!rc) {
        cerr << errStr << endl;
    } else {
        
        cube = make_shared<Shape>();
        cube->createShape(TOshapesD[0]);
        cube->measure();
        cube->init();
    }
    vector<std::string> sky_faces {
        "TropicalSunnyDay_px.jpg",
        "TropicalSunnyDay_nx.jpg",
        "TropicalSunnyDay_py.jpg",
        "TropicalSunnyDay_ny.jpg",
        "TropicalSunnyDay_pz.jpg",
        "TropicalSunnyDay_nz.jpg"
    };

    skyMapTexture = createSky(resourceDirectory+"/sky/", sky_faces);

    vector<tinyobj::shape_t> TOshapesE;
    vector<tinyobj::material_t> objMaterialsE;
    //load in the mesh and make the shape(s)
    rc = tinyobj::LoadObj(TOshapesE, objMaterialsE, errStr, (resourceDirectory + "/bunny.obj").c_str());
		if (!rc) {
			cerr << errStr << endl;
		} else {
			theBunny = make_shared<vector<Shape>>();
            write_to_obj(theBunny, TOshapesE);
		}

    vector<tinyobj::shape_t> TOshapesT;
    vector<tinyobj::material_t> objMaterialsT;
    //load in the mesh and make the shape(s)
    rc = tinyobj::LoadObj(TOshapesT, objMaterialsT, errStr, (resourceDirectory + "/cactus/cactus.obj").c_str());
		if (!rc) {
			cerr << errStr << endl;
		} else {
			cactus = make_shared<vector<Shape>>();
            write_to_obj(cactus, TOshapesT);
		}
    
    cactus_texture = make_shared<TexMap>();
    cactus_texture->map_kd= new Texture;
    cactus_texture->map_kd->setFilename(resourceDirectory+"/cactus/texture/diffuse.png");
    cactus_texture->map_kd->init();
    cactus_texture->map_kd->setUnit(0);
    cactus_texture->map_kd->setWrapModes(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    cactus_texture->map_ka = NULL;
    cactus_texture->map_ks = NULL;
    

    rc = tinyobj::LoadObj(TOshapesE, objMaterialsE, errStr, (resourceDirectory + "/cube_texture.obj").c_str());
		if (!rc) {
			cerr << errStr << endl;
		} else {
			theCube = make_shared<vector<Shape>>();
            write_to_obj(theCube, TOshapesE);
		}
}

//helper function to pass material data to the GPU
void SetMaterial(shared_ptr<Program> curS, const tinyobj::material_t &material, float ka) {
    glUniform3f(curS->getUniform("MatAmb"), ka*material.ambient[0], ka*material.ambient[1], ka*material.ambient[2]);
    glUniform3f(curS->getUniform("MatDif"), material.diffuse[0], material.diffuse[1], material.diffuse[2]);
    glUniform3f(curS->getUniform("MatSpec"), material.specular[0], material.specular[1], material.specular[2]);
    glUniform1f(curS->getUniform("MatShine"), material.shininess);
    glUniform3f(curS->getUniform("MatEmit"), material.emission[0], material.emission[1], material.emission[2]);
    glUniform1f(curS->getUniform("Alpha"), material.dissolve);    	
}

//helper function to pass texture data to the GPU
void SetTexture(shared_ptr<Program> curS, const TexMap &texMap) {
    if(texMap.map_ka){
        texMap.map_ka->bind(curS->getUniform("map_ka"));
        glUniform1i(curS->getUniform("use_map_ka"), 1);
    }
    else{
        glUniform1i(curS->getUniform("use_map_ka"), 0);
    }
    if(texMap.map_kd){
        texMap.map_kd->bind(curS->getUniform("map_kd"));
        glUniform1i(curS->getUniform("use_map_kd"), 1);
    }
    else{
        glUniform1i(curS->getUniform("use_map_kd"), 0);
    }
    if(texMap.map_ks){
        texMap.map_ks->bind(curS->getUniform("map_ks"));
        glUniform1i(curS->getUniform("use_map_ks"), 1);
    }
    else{
        glUniform1i(curS->getUniform("use_map_ks"), 0);
    }
}

void Application::DrawParam::operator()(){
    //set parameters
    prog->bind();
    // glUniform3f(prog->getUniform("lightDir"), -2.0, 1.0, 0.0);
    glUniformMatrix4fv(prog->getUniform("V"), 1, GL_FALSE, value_ptr(V));
    glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(M));
    glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, value_ptr(P));
    if(material)
        SetMaterial(prog, *material,f);
    if(texture)
        SetTexture(prog, *texture);
    //draw
    shape->draw(prog);
    prog->unbind();
}

/* helper function to set model trasnforms */
void Application::SetModel(vec3 trans, float rotY, float rotX, float sc, shared_ptr<Program> curS) {
    mat4 Trans = glm::translate( glm::mat4(1.0f), trans);
    mat4 RotX = glm::rotate( glm::mat4(1.0f), rotX, vec3(1, 0, 0));
    mat4 RotY = glm::rotate( glm::mat4(1.0f), rotY, vec3(0, 1, 0));
    mat4 ScaleS = glm::scale(glm::mat4(1.0f), vec3(sc));
    mat4 ctm = Trans*RotX*RotY*ScaleS;
    glUniformMatrix4fv(curS->getUniform("M"), 1, GL_FALSE, value_ptr(ctm));
}

void Application::setModel(std::shared_ptr<Program> prog, std::shared_ptr<MatrixStack>M) {
    glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, value_ptr(M->topMatrix()));
}

void Application::updateView(float frametime){
    float sign = 1.0f;
    if(g_phi <= glm::pi<float>()/2 || g_phi >= 3*glm::pi<float>()/2){
        sign = -1.0f;
    }
    vec3 carDir;
    carDrive->getLocationDirection(car_loc, carDir);
    g_eye = car_loc+vec3(0.0,9.8,0.0) - 5.0f* normalize(vec3(2.0*cos(g_phi)*cos(g_theta), 2.0*sin(g_phi), 2.0*cos(g_phi)*cos((glm::pi<double>()/2)-g_theta)));
    // cout<<"g eye "<<glm::to_string(g_eye)<<endl;
    g_lookAt = car_loc+vec3(0.0,9.8,0.0);
    if(g_eye.y < (terrainHeightMap->GetHeight(g_eye.x, g_eye.y)+9.1)){
        g_eye.y = terrainHeightMap->GetHeight(g_eye.x, g_eye.y)+9.1;
    }


    if(mv_forward){
        gas = -1.0;
    }
    else if(mv_back){
        gas = 1.0;
    }
    else{
        gas = 0.0;
    }
    if(mv_left){
        turn += frametime * 2.5;
        turn = std::min(turn, 1.0f);
    }
    else if(mv_right){
        turn -= frametime * 2.5;
        turn = std::max(turn, -1.0f);
    }
    else{
        if(turn < -0.01)
            turn += frametime* 2.5;
        else if(turn > 0.01)
            turn -= frametime* 2.5;
        else{
            turn = 0.0;
        }
    }

    carDrive->update(frametime, turn, gas);

    // cout<<"turn "<<turn<<endl;
}


void Application::SetView(shared_ptr<Program>  shader) {
    glm::mat4 Cam = glm::lookAt(g_eye, g_lookAt, vec3(0, 1, 0));
    glUniformMatrix4fv(shader->getUniform("V"), 1, GL_FALSE, value_ptr(Cam));
}


void Application::updateUsingCameraPath(float frametime)  {
    
    if (goCamera) {
        if(!splinepath[0].isDone()){
            splinepath[0].update(frametime);
            g_eye = splinepath[0].getPosition();
        } else {
            splinepath[1].update(frametime);
            g_eye = splinepath[1].getPosition();
        }
    }
}

void Application::renderQueue(std::shared_ptr<std::queue<DrawParam>> renderQueue){
    //useful since shadow map has to be rendered before 
    //main scene is rendered
    while(!renderQueue->empty()){
        renderQueue->front()();
        renderQueue->pop();
    }
}


void Application::render(float frametime) {
    // Get current frame buffer size.
    int width, height;
    glfwGetFramebufferSize(windowManager->getHandle(), &width, &height);

    // Clear framebuffer.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Use the matrix queue for Lab 6
    float aspect = width/(float)height;

    // Create Render Queues
    shadow_queue = make_shared<std::queue<DrawParam>>();
    render_queue = make_shared<std::queue<DrawParam>>();

    // Create the matrix stacks - please leave these alone for now
    auto Projection = make_shared<MatrixStack>();
    auto View = make_shared<MatrixStack>();
    auto Model = make_shared<MatrixStack>();
    

    //update the camera position
    updateUsingCameraPath(frametime);

    // Apply perspective projection.
    Projection->pushMatrix();
    Projection->perspective(45.0f, aspect, 0.01f, 100.0f);

    View->pushMatrix();
    if(!goCamera)
        updateView(frametime);
    else
        g_lookAt = vec3(0,1,0);
    
    Model->pushMatrix();

    cubeProg->bind();
        Model->pushMatrix();
        Model->scale(vec3(100.0,100.0,100.0));
        glUniformMatrix4fv(cubeProg->getUniform("P"), 1, GL_FALSE, value_ptr(Projection->topMatrix()));
        glDepthFunc(GL_LEQUAL);
        SetView(cubeProg);
        glUniformMatrix4fv(cubeProg->getUniform("M"), 1,GL_FALSE,value_ptr(Model->topMatrix()));
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyMapTexture);
        cube->draw(cubeProg);
        glDepthFunc(GL_LESS);
        Model->popMatrix();
    cubeProg->unbind();
    
    vec3 light_eye = vec3(car_loc.x-3.0, 5, car_loc.y-10.0);
    vec3 light_lookat = vec3(car_loc.x,0.0,car_loc.y);
    direction_light = light_lookat-light_eye; //uniform directional light (sun/moon light)
    lightProjection = ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 15.0f);
    lightView = lookAt(
                    light_eye,
                    light_lookat,
                    vec3(0.0, 1.0, 0.0)
                    );
    prog->bind();
        glUniform3f(prog->getUniform("lightDir"), direction_light.x, direction_light.y, direction_light.z);
    prog->unbind();
    
    texProg->bind();
        glUniform3f(texProg->getUniform("lightDir"), direction_light.x, direction_light.y, direction_light.z);
        glUniform1i(texProg->getUniform("flip"), 1);
    texProg->unbind();

    DrawParam thisParam;
    DrawParam shadowParam;
    
    Model->translate(vec3(0,9.0,0.0));
    Model->pushMatrix();
    // Model->scale(vec3(0.1,0.1,0.1));
    thisParam= {
                glm::lookAt(g_eye, g_lookAt, vec3(0, 1, 0)),
                Model->topMatrix(),
                Projection->topMatrix(),
                1.0,
                texProg,
                desert->begin(),
                &(desert_material->at(0)),
                desert_texture
            };
    render_queue->push(thisParam);
    shadowParam={
        lightView,
        Model->topMatrix(),
        lightProjection,
        0.0,
        shadowProg,
        desert->begin(),
        NULL,
        NULL
    };
    shadow_queue->push(shadowParam);

    Model->popMatrix();

    Model->pushMatrix();
    Model->translate(vec3(cactusX,terrainHeightMap->GetHeight(cactusX, cactusY)-0.3,cactusY));
    Model->scale(vec3(0.1, 0.1, 0.1));
    // Model->scale(vec3(0.1,0.1,0.1));
    for(int i=0; i<3; i++){
        cactus_material.diffuse[i] = 1.0;
        cactus_material.ambient[i] = 0.5;
        cactus_material.specular[i] = 0.1;
        cactus_material.emission[i] = 0.0;
    }
    cactus_material.diffuse[0] = 0.5;
    cactus_material.shininess = 40;

    for(auto iter=cactus->begin(); iter!=cactus->end(); iter++){
        thisParam= {
                glm::lookAt(g_eye, g_lookAt, vec3(0, 1, 0)),
                Model->topMatrix(),
                Projection->topMatrix(),
                1.0,
                texProg,
                iter,
                &cactus_material,
                cactus_texture
            };
        render_queue->push(thisParam);
        shadowParam={
            lightView,
            Model->topMatrix(),
            lightProjection,
            0.0,
            shadowProg,
            iter,
            NULL,
            NULL
        };
    }
    
    shadow_queue->push(shadowParam);

    Model->popMatrix();

    float offset_height = 0.8;

    //car
    Model->pushMatrix();
        // Model->translate(vec3(g_eye.x,terrainHeightMap.GetHeight(g_eye.x, g_eye.z-2.0)+offset_height+0.5 ,g_eye.z-2.0));
        // Model->translate(vec3(0.0,terrainHeightMap->GetHeight(0.0, 0.0-2.0)+1.0 ,0.0-2.0));
        // carDrive->set(vec2(1.0, 0.0), vec3(g_eye.x, g_eye.y, g_eye.z-2.0));
        carDrive->createModelMatrix(Model);
        Model->translate(vec3(0.0, offset_height, 0.0));
        // Model->rotate(0.78, vec3(0,1,0));
        // Model->scale(vec3(0.7,0.7,0.7));
        Model->pushMatrix();
        prog->bind();
        glUniform3f(prog->getUniform("lightDir"), direction_light.x, direction_light.y, direction_light.z);
        prog->unbind();
        for(auto iter=car->begin(); iter!=car->end(); iter++){
            DrawParam thisParam= {
                glm::lookAt(g_eye, g_lookAt, vec3(0, 1, 0)),
                Model->topMatrix(),
                Projection->topMatrix(),
                0.1,
                prog,
                iter,
                &(car_material->at(iter->mtlBuf[0])),
                NULL
            };
            render_queue->push(thisParam);
            DrawParam shadowParam={
                lightView,
                Model->topMatrix(),
                lightProjection,
                0.0,
                shadowProg,
                iter,
                NULL,
                NULL
            };
            shadow_queue->push(shadowParam);
        }
        
        draw_wheels(Model, Projection);
        Model->popMatrix();
        
        
        
    Model->popMatrix();


    


    //render shadow map first
    glCullFace(GL_FRONT);
    shadowProg->bind();
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO); 
	glClear(GL_DEPTH_BUFFER_BIT);
    shadowProg->unbind();
    renderQueue(shadow_queue);

    //render actual scene next
    glCullFace(GL_BACK);
    glViewport(0, 0, width, height);
    prog->bind();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    bind_depthMap_to_shadowMap(prog, depthMap, 4);
    mat4 lightSpaceMatrix = lightProjection * lightView;
    glUniformMatrix4fv(prog->getUniform("lightSpaceMatrix"), 1, GL_FALSE, value_ptr(lightSpaceMatrix));
    prog->unbind();

    texProg->bind();
    bind_depthMap_to_shadowMap(texProg, depthMap, 5);
    glUniformMatrix4fv(texProg->getUniform("lightSpaceMatrix"), 1, GL_FALSE, value_ptr(lightSpaceMatrix));
    texProg->unbind();
    renderQueue(render_queue);

    // cout<<g_eye.x<<' '<< g_eye.z<<' '<<terrainHeightMap.GetHeight(g_eye.x, g_eye.z)+offset_height<<endl;
    Model->popMatrix();
    // Pop matrix stacks.
    Projection->popMatrix();
    renderTime += frametime;


}


