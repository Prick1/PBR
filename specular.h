#ifndef SPECULAR_H_
#define SPECULAR_H_

#include "material.h"


class Specular: public Material{
public:
    inline Ray getReflectedRay(Ray intersectionRay, glm::vec3 normal, glm::vec3 position);
    inline glm::vec3 getBSDF();
    Specular(void);
};

#endif /* SPECULAR_H_ */