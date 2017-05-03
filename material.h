#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <glm/glm.hpp>
#include "ray.h"
#include <cstdlib>
#include <cmath>
#include "onb.h"
typedef enum tMaterial{
    isDiffuse,
    isSpecular}tMaterial;
class Material{
public:
    tMaterial materialEnum;
    glm::vec3 emittance_;
    virtual Ray getReflectedRay(Ray intersectionRay, glm::vec3 normal, glm::vec3 position) = 0;
    virtual glm::vec3 getBSDF() = 0;
};

#endif /* MATERIAL_H_ */
