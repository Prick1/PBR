#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <glm/glm.hpp>
#include <cmath>


class Material{
public:
    glm::vec3 emittance_;
    glm::vec3 reflectance_;
    Material(glm::vec3 emittance, glm::vec3 reflectance);
    Material(void){};
};

#endif /* MATERIAL_H_ */
