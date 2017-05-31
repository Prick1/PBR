#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_

#include <glm/glm.hpp>
#include "primitive.h"
#include "intersection_record.h"
#include "ray.h"
#include <vector>

class BoundingBox
{
public:

    BoundingBox( void );

    BoundingBox( const glm::vec3 &negative_corner, const glm::vec3 &positive_corner);

    bool intersect(const Ray &ray);
    BoundingBox* left;
    BoundingBox* right; 
    std::vector<int> *primitivesIndex;
    glm::vec3 negativeCorner;
    glm::vec3 positiveCorner;
    glm::vec3 center;


};

#endif /* BOUNDINGBOX_H_ */