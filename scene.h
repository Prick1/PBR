#ifndef SCENE_H_
#define SCENE_H_

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include "primitive.h"
#include "sphere.h" 
#include "triangle.h"
#include "mesh.h"
#include "bvh.h"

class Scene
{
public:

    Scene( void );

    ~Scene( void );
    BVH* bvh = nullptr;

    bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

    void load( void );
    void load_mesh(Mesh& mesh1,const glm::vec3 position);

    std::vector< Primitive::PrimitiveUniquePtr > primitives_;

};

struct CheckIntersection{
    CheckIntersection(const Ray &ray, IntersectionRecord &intersection_record, const std::vector< Primitive::PrimitiveUniquePtr > &primitivesIn);
    void operator()(BoundingBox *node);
    
    bool intersection_result = false;
    IntersectionRecord tmp_intersection_record;
    IntersectionRecord intersection_record;
    const Ray ray;
    const std::vector< Primitive::PrimitiveUniquePtr > &primitives;
};

#endif /* SCENE_H_ */

