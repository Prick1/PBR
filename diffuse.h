#ifndef DIFFUSE_H_
#define DIFFUSE_H_

#include "material.h"

class Diffuse: public Material{
    glm::vec3 reflectance_;
public:
    inline Ray getReflectedRay(Ray intersectionRay, glm::vec3 normal, glm::vec3 position);
    inline glm::vec3 getBSDF(Ray incidentRay, Ray outGoingRay, glm::vec3 normal);
    Diffuse(glm::vec3 reflectance);
    Diffuse(void);
    
};



#endif /* DIFFUSE_H_ */
