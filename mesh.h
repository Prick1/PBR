#ifndef MESH_H_
#define MESH_H_

#include "primitive.h"
#include "triangle.h"
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Mesh{
public:
    Mesh(void){}
    Mesh(const std::string &pFile);
    
    bool created = false;
    std::vector<Triangle*> triangles;
    std::vector<Material*> materials;
    void Translate(glm::vec3 position);
};

#endif /* MESH_H_ */
