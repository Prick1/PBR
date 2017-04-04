#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <glm/glm.hpp>
#include "ray.h"
#include <cstdlib>
#include <cmath>
#include "onb.h"

class Material{
public:
    glm::vec3 emittance_;
    virtual Ray getRefflectedRay(glm::vec3 normal, glm::vec3 point) = 0;
    virtual glm::vec3 getBRDF() = 0;
};

#endif /* MATERIAL_H_ */
