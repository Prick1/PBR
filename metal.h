#ifndef METAL_H_
#define METAL_H_

#include "material.h"
#include <iostream>


class Metal: public Material{
    float roughnessFactor;
    glm::vec3 reflectance;
    inline glm::vec3 Reflect(glm::vec3 incident, glm::vec3 normal);
public:
    Ray getReflectedRay(Ray intersectionRay, glm::vec3 normal, glm::vec3 position);
    glm::vec3 getBSDF(Ray incidentRay, Ray outGoingRay, glm::vec3 normal);
    Metal(float roughnessFactor, glm::vec3 reflectance_);
};

#endif /* METAL_H_ */