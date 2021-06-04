#include "TerrainMap.h"

#define THEIGHT  60
#define TWIDTH  60
#define TTEX 4 //every unit is divided into ten smaller tex units

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
        cout<<"sum1 "<<sum<<endl;
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