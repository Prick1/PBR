#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_

#include "material.h"

class LightSource: public Material{
    glm::vec3 emittance_;
public:
    inline Ray getReflectedRay(Ray intersectionRay, glm::vec3 normal, glm::vec3 position);
    inline glm::vec3 getBSDF(Ray incidentRay, Ray outGoingRay, glm::vec3 normal);
    LightSource(glm::vec3 emittance);
    //LightSource(void);
    
};



#endif /* LIGHTSOURCE_H_ */