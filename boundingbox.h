#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_

#include <glm/glm.hpp>
#include "primitive.h"
#include "intersection_record.h"
#include "ray.h"

class BoundingBox: public Primitive
{
    bool planIntersection(const Ray &ray, const glm::vec3 &normal, float distance) const;
public:

    BoundingBox( void );

    BoundingBox( const glm::vec3 &negative_corner, const glm::vec3 &positive_corner);

    bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

    glm::vec3 negativeCorner;
    glm::vec3 positiveCorner;


};

#endif /* BOUNDINGBOX_H_ */