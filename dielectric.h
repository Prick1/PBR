#ifndef DIELECTRIC_H_
#define DIELECTRIC_H_

#include "material.h"



class Dielectric: public Material{
    float internalMedia_;
    float externalMedia_;
    inline float Schlick(glm::vec3 incident, glm::vec3 normal,float n1, float n2);
    inline glm::vec3 Refract(glm::vec3 incident, glm::vec3 normal,float n1, float n2);
    inline glm::vec3 Reflect(glm::vec3 incident,glm::vec3 normal);
public:
    inline Ray getReflectedRay(Ray intersectionRay, glm::vec3 normal, glm::vec3 position);
    inline glm::vec3 getBSDF(Ray incidentRay, Ray outGoingRay, glm::vec3 normal);
    Dielectric(float externalMedia = 1.0f,float internalMedia = 1.1f);
};

#endif /* DIELECTRIC_H_ */