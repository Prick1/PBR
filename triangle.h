#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <glm/glm.hpp>
#include "primitive.h"
#include "intersection_record.h"
#include "ray.h"

class Triangle : public Primitive
{
public:

    Triangle( void );

    Triangle( const glm::vec3 &point1, const glm::vec3 &point2, const glm::vec3 &point3);

    bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

    glm::vec3 point1_ = { -1.0f, 0.0f, 0.0f };
    
    glm::vec3 point2_ = { 1.0f, 0.0f, 0.0f };

    glm::vec3 point3_ = { 0.0f, 1.0f, 0.0f };


//private:

    //static const float kIntersectionTestEpsilon_;
};

#endif /* SPHERE_H_ */

