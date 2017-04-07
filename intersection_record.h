#ifndef INTERSECTION_RECORD_H_
#define INTERSECTION_RECORD_H_

#include <glm/glm.hpp>
#include "material.h"

class IntersectionRecord
{
public:
    float t_;
    glm::vec3 position_;
    glm::vec3 normal_;
    Material *intersectionMaterial;
};

#endif /* INTERSECTION_RECORD_H_ */

