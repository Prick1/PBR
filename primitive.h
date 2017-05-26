#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include <memory>
#include "lightsource.h"
#include "diffuse.h"
#include "specular.h"
#include "dielectric.h"

#include "ray.h"
#include "intersection_record.h"
#include "bbox.h"

class Primitive
{
public:
    //glm::vec3 center_;
    //glm::vec3 positiveCorner;
    //glm::vec3 negativeCorner;

    typedef std::unique_ptr< Primitive > PrimitiveUniquePtr;

    Material* material_;

    Primitive( void ){}

    Primitive(Material* material);

    virtual ~Primitive( void );

    virtual bool intersect( const Ray &ray,
                            IntersectionRecord &intersection_record ) const = 0;

    virtual BBox getAABB( void ) const = 0;
};

#endif /* PRIMITIVE_H_ */

