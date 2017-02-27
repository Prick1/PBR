#ifndef INTERSECTION_RECORD_H_
#define INTERSECTION_RECORD_H_

#include <glm/glm.hpp>

struct IntersectionRecord
{
    float t_;
    glm::vec3 position_;
    glm::vec3 normal_;
    glm::vec3 intersectionColor = glm::vec3(0.0f, 0.0f, 0.0f);
};

#endif /* INTERSECTION_RECORD_H_ */

