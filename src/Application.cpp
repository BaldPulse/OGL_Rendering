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



    vector<std::string> sky_faces {
        "skybox_px.jpg",
        "skybox_nx.jpg",
        "skybox_py.jpg",
        "skybox_ny.jpg",
        "skybox_pz.jpg",
        "skybox_nz.jpg"
    };

    skyMapTexture = createSky(resourceDirectory+"/sky/", sky_faces);

    // init splines up and down
    splinepath[0] = Spline(glm::vec3(0,1,3), glm::vec3(-1,1,1), glm::vec3(3, 1, 3), glm::vec3(2,1,0), 5);
    splinepath[1] = Spline(glm::vec3(2,1,0), glm::vec3(1.5,0,1), glm::vec3(1, 2, 2), glm::vec3(3,2,-3), 5);

}

void Application::initGeom(const std::string& resourceDirectory)
{

    bool rc;
    string errStr;
    // Initialize ground mesh.
    vector<tinyobj::shape_t> TOshapesB;
    mossy_ground_material = make_shared<vector<tinyobj::material_t>>();
    // load in the mesh and make the shape(s)
    rc = tinyobj::LoadObj(TOshapesB, *mossy_ground_material, errStr, 
        (resourceDirectory + "/MossyGround" + "/mossy_ground_l.obj").c_str(), (resourceDirectory+"/MossyGround/").c_str());
    if (!rc) {
        cerr << errStr << endl;
    } else {
        mossy_ground = make_shared<vector<Shape>>();
        write_to_obj(mossy_ground, TOshapesB);
    }
    // setup ground material
    mossy_texture = make_shared<TexMap>();
    load_texture(mossy_texture, resourceDirectory+"/MossyGroundTexture/", mossy_ground_material->at(0));

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
    glUniform3f(prog->getUniform("lightPos"), -2.0, 1.0, 0.0);
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
    vec3 look_dir=normalize(vec3(2.0*cos(g_phi)*cos(g_theta), 2.0*sin(g_phi), 2.0*cos(g_phi)*cos((glm::pi<double>()/2)-g_theta)));
    g_lookAt = g_eye + look_dir;
    if(mv_forward && !mv_back)
        g_eye += 0.01f * look_dir;
    else if(mv_back && !mv_forward)
        g_eye -= 0.01f * look_dir;
    if(mv_right && !mv_left)
        g_eye += 0.01f * normalize(cross(look_dir, vec3(0, 1, 0)));
    else if(mv_left && !mv_right)
        g_eye -= 0.01f * normalize(cross(look_dir, vec3(0, 1, 0)));
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
    glViewport(0, 0, width, height);

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
        Model->scale(vec3(50.0,50.0,50.0));
        glUniformMatrix4fv(cubeProg->getUniform("P"), 1, GL_FALSE, value_ptr(Projection->topMatrix()));
        glDepthFunc(GL_LEQUAL);
        SetView(cubeProg);
        glUniformMatrix4fv(cubeProg->getUniform("M"), 1,GL_FALSE,value_ptr(Model->topMatrix()));
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyMapTexture);
        cube->draw(cubeProg);
        glDepthFunc(GL_LESS);
        Model->popMatrix();
    cubeProg->unbind();
    
    

    Model->pushMatrix();
    texProg->bind();
        glUniform3f(texProg->getUniform("lightPos"), -2.0, 1.0, 0.0);
        glUniform1i(texProg->getUniform("flip"), 1);
    texProg->unbind();
    // glUniformMatrix4fv(texProg->getUniform("P"), 1, GL_FALSE, value_ptr(Projection->topMatrix()));
    // glUniformMatrix4fv(texProg->getUniform("M"), 1, GL_FALSE, value_ptr(Model->topMatrix()));

    Model->scale(vec3(0.1,0.1,0.1));
    DrawParam thisParam= {
                glm::lookAt(g_eye, g_lookAt, vec3(0, 1, 0)),
                Model->topMatrix(),
                Projection->topMatrix(),
                1.0,
                texProg,
                mossy_ground->begin(),
                &(mossy_ground_material->at(0)),
                mossy_texture
            };
    render_queue->push(thisParam);
    Model->popMatrix();


    //car
    Model->pushMatrix();
        Model->translate(vec3(0.0, 1.0, 0.0));
        Model->rotate(0.78, vec3(0,1,0));
        Model->scale(vec3(0.7,0.7,0.7));
        prog->bind();
        glUniform3f(prog->getUniform("lightPos"), -2.0, 1.0, 0.0);
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
            thisParam.material = NULL;
            shadow_queue->push(thisParam);
        }
    Model->popMatrix();
    renderQueue(render_queue);



    Model->popMatrix();
    // Pop matrix stacks.
    Projection->popMatrix();

}

/*
 = {
            View->topMatrix(),
            Model->topMatrix(),
            Projection->topMatrix(),
            prog,
            iter,
            car_material->at(iter->mtlBuf[0])),
            NULL
        };
        shadow_queue->push();
*/