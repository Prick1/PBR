#ifndef BVH_H_
#define BVH_H_

#include "boundingbox.h"
#include <vector>



typedef std::vector< Primitive::PrimitiveUniquePtr > PrimitiveVector;

class BVH{
private:
    BVH(PrimitiveVector &primitivesReferenceIn, std::vector<int> *primitiveIndexesIn);
public:
    BoundingBox BBox;
    BVH* leftChild;
    BVH* rightChild;
    std::vector<int> *primitiveIndexes;
    PrimitiveVector &primitivesReference;
    BVH(PrimitiveVector &primitivesReferenceIn);
    bool intersect(const Ray &ray, IntersectionRecord &intersection_record);
};










#endif /* BVH_H_ */