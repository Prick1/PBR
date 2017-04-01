#ifndef INTERSECTION_RECORD_H_
#define INTERSECTION_RECORD_H_

#include <glm/glm.hpp>
#include "material.h"
#include "onb.h"

struct IntersectionRecord
{
    float t_;
    glm::vec3 position_;
    glm::vec3 normal_;
    //ONB onb_;
    Material intersectionMaterial = Material(glm::vec3(0.0f), glm::vec3(0.0f));
};

#endif /* INTERSECTION_RECORD_H_ */

