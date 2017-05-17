#ifndef BVH_H_
#define BVH_H_

#include "boundingbox.h"
#include <vector>
#include <limits>

typedef std::vector< Primitive::PrimitiveUniquePtr > PrimitiveVector;

class BVH{
private:
    BVH(const std::vector< Primitive::PrimitiveUniquePtr > &primitivesReference, std::vector<int> *primitiveIndexes);
public:
    BoundingBox BBox;
    BVH* leftChild = NULL;
    BVH* rightChild = NULL;
    std::vector<int> *primitiveIndexes = NULL;
    PrimitiveVector &primitivesReference;
    BVH(const PrimitiveVector &primitivesReferenceIn);
    BVH(const PrimitiveVector &primitivesReferenceIn, std::vector<int> *primitiveIndexesIn);
}










#endif /* BVH_H_ */