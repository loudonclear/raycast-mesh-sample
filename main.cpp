
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream> 

#include "tracer.h"
#include "scene/scene.h"
#include "scene/basiccamera.h"

#include "util/common.h"

std::vector<std::string> split(std::string str, char delimiter) {
  std::vector<std::string> internal;
  std::stringstream ss(str); // Turn the string into a stream.
  std::string tok;
 
  while(std::getline(ss, tok, delimiter)) {
      internal.push_back(tok);
  }
  return internal;
}

int main(int argc, char *argv[])
{
    std::string meshfile, camfile, outfile;

    meshfile = std::string(argv[1]);
    camfile = std::string(argv[2]);
    outfile = std::string(argv[3]);


    Mesh *mesh;
    if(!(mesh = Scene::loadMesh(meshfile))) {
        std::cerr << "Error parsing mesh file " << meshfile << '\n';
        return 1;
    }

    std::ifstream input;
    input.open(camfile);

    std::vector<BasicCamera> cams;

    glm::vec3 pos, look, look_at, up;
    float fov = 45.f;
    float ar = static_cast<float>(IMAGE_WIDTH) / IMAGE_HEIGHT;

    std::string spos, slook_at, sup;
    while (std::getline(input, spos))
    {
        std::getline(input, slook_at);
        std::getline(input, sup);

        std::vector<std::string> sspos = split(spos, ' '); 
        std::vector<std::string> sslook_at = split(slook_at, ' '); 
        std::vector<std::string> ssup = split(sup, ' '); 

        pos = glm::vec3(stof(sspos[0]), stof(sspos[2]), stof(sspos[1]));
        look_at = glm::vec3(stof(sslook_at[0]), stof(sslook_at[1]), stof(sslook_at[2]));
        up = glm::vec3(stof(ssup[0]), stof(ssup[1]), stof(ssup[2]));

        cams.push_back(BasicCamera(pos, look_at - pos, up, fov, ar));
    }
    input.close();
    std::cout << "Read " + std::to_string(cams.size()) << " cameras" << '\n';

    std::vector<glm::vec3> hits;
    Tracer tracer(IMAGE_WIDTH, IMAGE_HEIGHT);
    tracer.traceScene(*mesh, cams, hits);
    delete mesh;

    std::ofstream output;
    output.open(outfile);
    for (const glm::vec3 &v : hits) {
        output << v.x << " " << v.y << " " << v.z << '\n';
    }
    output.close();
    
    return 0;
}
