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

class Scene
{
public:

    Scene( void );

    ~Scene( void );

    bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

    void load( void );
    void load_mesh(Mesh& mesh1,const glm::vec3 position);

    std::vector< Primitive::PrimitiveUniquePtr > primitives_;

};

#endif /* SCENE_H_ */

