#ifndef DIFFUSE_H_
#define DIFFUSE_H_

#include "material.h"

class Diffuse: public Material{
public:
    glm::vec3 reflectance_;
    Ray getRefflectedRay(glm::vec3 normal, glm::vec3 point);
    glm::vec3 getBRDF();
    Diffuse(glm::vec3 emittance, glm::vec3 reflectance);
    Diffuse(void);
    
};



#endif /* DIFFUSE_H_ */
