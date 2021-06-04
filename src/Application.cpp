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
        lightTrans += 0.5;
    }
    if (key == GLFW_KEY_E && action == GLFW_PRESS){
        lightTrans -= 0.5;
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
        write_to_obj(car, TOshapesC);
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

void Application::updateView(){
    float sign = 1.0f;
    if(g_phi <= glm::pi<float>()/2 || g_phi >= 3*glm::pi<float>()/2){
        sign = -1.0f;
    }
    look_dir=normalize(vec3(2.0*cos(g_phi)*cos(g_theta), 2.0*sin(g_phi), 2.0*cos(g_phi)*cos((glm::pi<double>()/2)-g_theta)));
    g_lookAt = g_eye + look_dir;
    if(mv_forward && !mv_back)
        g_eye += 0.02f * look_dir;
    else if(mv_back && !mv_forward)
        g_eye -= 0.02f * look_dir;
    if(mv_right && !mv_left)
        g_eye += 0.02f * normalize(cross(look_dir, vec3(0, 1, 0)));
    else if(mv_left && !mv_right)
        g_eye -= 0.02f * normalize(cross(look_dir, vec3(0, 1, 0)));
}

/* camera controls - do not change */
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
        updateView();
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
    
    vec3 light_eye = vec3(-3, 5, -10);
    vec3 light_lookat = vec3(0.0,0.0,0.0);
    vec3 direction_light = light_lookat-light_eye; //uniform directional light (sun/moon light)
    mat4 lightProjection = ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 15.0f);
    mat4 lightView = lookAt(
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
    
    Model->pushMatrix();
    Model->translate(vec3(0,9.0,2));
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


    //car
    Model->pushMatrix();
        Model->translate(vec3(0.0, 1.0, 0.0));
        // Model->rotate(0.78, vec3(0,1,0));
        Model->scale(vec3(0.7,0.7,0.7));
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



    Model->popMatrix();
    // Pop matrix stacks.
    Projection->popMatrix();

}


#define THEIGHT  60
#define TWIDTH  60
#define TTEX 4 //every unit is divided into ten smaller tex units
void add_vert_to_terrain(const int &x,const int &z, const float &v_x, const float &v_z, const float &v_y, 
    float*terrain_map, float *terrain_map_density, char* terrain_map_set){
    int index = (z+THEIGHT*TTEX/2)*TWIDTH*TTEX + (x+TWIDTH*TTEX/2);
    float weight = 1 / ( distance(vec2((float) x, (float) z), vec2(v_x, v_z)) + 0.01);
    
    terrain_map[index] += weight * v_y;
    float prev_w = terrain_map_density[index];
    terrain_map_density[index] += weight;
    terrain_map_set[index] = 1;
    if(isnan(abs(terrain_map_density[index]))){
        cout<<'\t'<<"weight is nan"<<weight<<' '<<prev_w<<endl;
    }
}

void average_surrounding(float*terrain_map, int i, int j){
    int w_min = std::max(0, i-1);
    int w_max = std::min(THEIGHT*TTEX, i+2);
    int h_min = std::max(0, j-1);
    int h_max = std::min(TWIDTH*TTEX, j+2);
    float sum = 0.0;
    sum += terrain_map[i*TWIDTH*TTEX + j];
    float count = 0.0f;
    if(sum != 0.0){
        count+=1.0;
    }
    for(int u=w_min; u<w_max; u++){
        for(int v=h_min; v<h_max; v++){
            if(u==i && v==j)
                continue;
            // cout<<"suming "<<terrain_map[u*TWIDTH*TTEX + v]<<endl;
            sum+=terrain_map[u*TWIDTH*TTEX + v];
            count += 1.0f;
        }
    }
    // if(count<1.0)
    //     cout<<"count "<<count<<endl;
    // if(sum>100.0)
        cout<<"sum1 "<<sum<<endl;
    terrain_map[i*TWIDTH*TTEX+j] = (sum/count);
}

void Application::obj_to_terrain_map(){
    bool rc;
    string errStr;
    vector<tinyobj::shape_t> terrainV;
    vector<tinyobj::material_t> terrainMaterialV;
    // load in the mesh and make the shape(s)
    string resourceDirectory = "../resources";
    rc = tinyobj::LoadObj(terrainV, terrainMaterialV, errStr, 
        (resourceDirectory + "/Desert" + "/Dune_LOD1.obj").c_str(), (resourceDirectory+"/Desert/").c_str());
    

    tinyobj::shape_t terrain = terrainV.at(0);
    float* terrain_map = new float[THEIGHT*TTEX*TWIDTH*TTEX];
    float* terrain_map_density = new float[THEIGHT*TTEX*TWIDTH*TTEX];
    char* terrain_map_set = new char[THEIGHT*TTEX*TWIDTH*TTEX];


    for(int i=0; i<THEIGHT*TTEX*TWIDTH*TTEX; i++){
        terrain_map[i] = 0.0f;
        terrain_map_density[i] = 0.0001f;
        terrain_map_set[i] = 0;
    }
    for(auto iter=terrain.mesh.positions.begin(); iter!=terrain.mesh.positions.end(); iter+=3){
        int l_x = (int)((*iter)*TTEX);
        int l_z = (int)((*(iter+2))*TTEX);
        if(l_x > - TWIDTH*TTEX/2 && l_x < (TWIDTH*TTEX/2-1) && l_z >= - THEIGHT*TTEX/2 && l_z < (THEIGHT*TTEX/2-1)){
            // cout<<l_x<<' '<<l_z<<endl;
            add_vert_to_terrain(l_x, l_z, *iter, *(iter+2), *(iter+1), terrain_map, terrain_map_density, terrain_map_set);
            add_vert_to_terrain(l_x+1, l_z, *iter, *(iter+2), *(iter+1), terrain_map, terrain_map_density, terrain_map_set);
            add_vert_to_terrain(l_x, l_z+1, *iter, *(iter+2), *(iter+1), terrain_map, terrain_map_density, terrain_map_set);
            add_vert_to_terrain(l_x+1, l_z+1, *iter, *(iter+2), *(iter+1), terrain_map, terrain_map_density, terrain_map_set);
        }
    }
    ofstream terrain_map_file, terrain_map_ppm;
    terrain_map_file.open(resourceDirectory+"/Desert/Dune_hmap.txt");
    terrain_map_ppm.open(resourceDirectory+"/Desert/Dune_hmap.ppm");
    terrain_map_ppm<<"P3"<<endl;
    terrain_map_ppm<<TWIDTH*TTEX<<' '<<THEIGHT*TTEX<<endl;

    terrain_map_file<<THEIGHT<<' '<<TWIDTH<<endl;
    terrain_map_file<<TTEX<<endl;
    float min = 0;
    float max = -10;
    
    for(int i=0; i<THEIGHT*TTEX*TWIDTH*TTEX; i++){
        float prv = terrain_map[i];
        int prv_w = terrain_map_density[i];
        terrain_map[i]/=terrain_map_density[i];
        if(isnan(terrain_map[i])){
            cout<<"nan occured "<<terrain_map[i]<<'\t'<<terrain_map_density[i]<<prv<<'\t'<<prv_w<<endl;
        }
        if(abs(terrain_map[i])>100){
            cout<<"big h occured "<<i/(TWIDTH*TTEX)-THEIGHT*TTEX/2<<' '<<i%(TWIDTH*TTEX)-TWIDTH*TTEX/2<<'\t'<<terrain_map[i]<<'\t'<<prv<<'\t'<<terrain_map_density[i]<<endl;
        }
    }


    for(int k=0; k<3; k++){
        for(int i=0; i<THEIGHT*TTEX; i++){
            for(int j=0; j<TWIDTH*TTEX; j++){
                if(terrain_map[i*TWIDTH*TTEX + j] ==0.0){
                    terrain_map_set[i*TWIDTH*TTEX + j]==0;
                }
                if(terrain_map_set[i*TWIDTH*TTEX + j]==0){
                    cout<<i<<' '<<j<<endl;
                    average_surrounding(terrain_map, i, j);
                    cout<<"after average"<<terrain_map[i*TWIDTH*TTEX + j]<<endl;
                }
            }
        }
    }

    for(int i=0; i<THEIGHT*TTEX*TWIDTH*TTEX; i++){
        if(terrain_map[i]>max)
            max = terrain_map[i];
        if(terrain_map[i]<min)
            min = terrain_map[i];
        terrain_map_file<<terrain_map[i]<<endl;
    }

    cout<<"min "<<min<<" min "<<max<<endl;
    float range_k = 256/(max-min);
    cout<<"range_k"<<range_k<<endl;
    terrain_map_ppm<<255<<endl;
    for(int i=0; i<TWIDTH*TTEX; i++){
        for(int j=0; j<THEIGHT*TTEX; j++){
            int h_val = (int) ((terrain_map[i*TWIDTH*TTEX + j] - min)*range_k);
            terrain_map_ppm<<h_val<<' '<<h_val<<' '<<h_val<<'\t';
        }
        terrain_map_ppm<<endl;
    }

    delete[] terrain_map;
    delete[] terrain_map_density;
}