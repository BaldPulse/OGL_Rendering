#include "TerrainMap.h"

#define THEIGHT  70
#define TWIDTH  70
#define TTEX 1 //every unit is divided into ten smaller tex units

using namespace std;
using namespace glm;


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
        // cout<<"sum1 "<<sum<<endl;
    terrain_map[i*TWIDTH*TTEX+j] = (sum/count);
}

void obj_to_terrain_map(){
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
                    // cout<<i<<' '<<j<<endl;
                    average_surrounding(terrain_map, i, j);
                    // cout<<"after average"<<terrain_map[i*TWIDTH*TTEX + j]<<endl;
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


void SplitBySpace(string s, vector<string>* words){
    // cout<<"splitting"<<endl;
    size_t pos=0;
    string space_delimiter = " ";
    while ((pos = s.find(space_delimiter)) != string::npos) {
        words->push_back(s.substr(0, pos));
        s.erase(0, pos + space_delimiter.length());
    }
    // cout<<"last substring "<<s.substr(0, s.size())<<endl;
    words->push_back(s.substr(0, s.size()));
}

int TerrainHeightMap::LoadHeightMap(std::string path){
    ifstream tFile;
    tFile.open(path);
    string line;
    if(!tFile.is_open()){
        cerr<<"Unable to open file: "<<path<<endl;
        return 1;
    }
    vector<string> *words = new vector<string>;

    getline(tFile, line);
    SplitBySpace(line, words);
    this->tHeight = stoi(words->at(0));
    // cout<<"word size "<<words->size()<<endl;
    this->tWidth = stoi(words->at(1));

    getline(tFile, line);
    words->clear();
    SplitBySpace(line, words);
    this->tTex = stoi(words->at(0));

    int h_size = this->tHeight * this->tTex * this->tWidth * this->tTex;
    this->h_map = new float[h_size];
    int i=0;
    while(getline(tFile, line) && i<h_size){
        words->clear();
        SplitBySpace(line, words);
        this->h_map[i] = stof(words->at(0));
        i++;
    }
    if(i!=h_size){
        cerr<<"dimension mismatch, expected "<<h_size<<" read "<<i<<" lines"<<endl;
        return 1;
    }

    delete words;
    return 0;
}

float Barycentric(vec2 p, vec2 a, vec2 b, vec2 c, const float &ay, const float &by, const float &cy)
{
    vec2 v0 = b - a, v1 = c - a, v2 = p - a;
    float d00 = dot(v0, v0);
    float d01 = dot(v0, v1);
    float d11 = dot(v1, v1);
    float d20 = dot(v2, v0);
    float d21 = dot(v2, v1);
    float denom = d00 * d11 - d01 * d01;
    float u, v, w;
    v = (d11 * d20 - d01 * d21) / denom;
    w = (d00 * d21 - d01 * d20) / denom;
    u = 1.0f - v - w;
    return u*ay + v*by + w*cy;
}

float TerrainHeightMap::GetHeight(float x, float z){
    //check for out of range
    if(z < -(float)this->tHeight/2 || z>(float)this->tHeight/2
    || x < -(float)this->tWidth/2 || x>(float)this->tWidth/2){
        cerr<<"x "<<x<<" z "<<z<<" out of bound for " << this->tWidth<<' '<<this->tHeight<<endl;
        return 0.0;
    }
    //height averaging
    float x_h = (x+(float)(this->tWidth) /2)*(float)(this->tTex);
    float z_h = (z+(float)(this->tHeight)/2)*(float)(this->tTex);

    int ax = int(x_h);
    int az = int(z_h);
    float ay = this->h_map[(this->tWidth)*az + ax];

    int bx = int(x_h)+1;
    int bz = int(z_h);
    float by = this->h_map[(this->tWidth)*bz + bx];

    int cx = int(x_h);
    int cz = int(z_h)+1;
    float cy = this->h_map[(this->tWidth)*cz + cx];

    int dx = int(x_h)+1;
    int dz = int(z_h)+1;
    float dy = this->h_map[(this->tWidth)*dz + dx];

    float xr = x_h - (float)ax;
    float zr = z_h - (float)az;

    float height = 0.0;
    if(xr+zr>1.0){
        height = Barycentric(vec2(x_h, z_h), vec2(bx, bz), vec2(cx, cz), vec2(dx, dz),
            by, cy, dy);
    }
    else{
        height = Barycentric(vec2(x_h, z_h), vec2(bx, bz), vec2(cx, cz), vec2(ax, az),
            by, cy, ay);
    }

    return height;

    // float weight = 0.0;
    // float height = 0.0;
    // float total_weight = 0.0;

    // weight = 1/(distance(vec2(x_h, z_h), vec2((int)x_h, (int)z_h))+0.0001f);
    // height += weight * this->h_map[(this->tWidth)*(int)z_h + (int)x_h];
    // total_weight += weight;

    // weight = 1/(distance(vec2(x_h, z_h), vec2((int)x_h+1, (int)z_h))+0.0001f);
    // height += weight * this->h_map[(this->tWidth)*(int)z_h + (int)x_h+1];
    // total_weight += weight;

    // weight = 1/(distance(vec2(x_h, z_h), vec2((int)x_h, (int)z_h+1))+0.0001f);
    // height += weight * this->h_map[(this->tWidth)*(int)z_h+1 + (int)x_h];
    // total_weight += weight;

    // weight = 1/(distance(vec2(x_h, z_h), vec2((int)x_h+1, (int)z_h+1))+0.0001f);
    // height += weight * this->h_map[(this->tWidth)*(int)z_h+1 + (int)x_h+1];
    // total_weight += weight;

    // return height/total_weight;
}