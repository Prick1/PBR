#ifndef BVH_H_
#define BVH_H_

#include "boundingbox.h"
#include <vector>


class BVH{
private:
    BVH(const std::vector< Primitive::PrimitiveUniquePtr > &primitivesReference, std::vector<int> *primitiveIndexes);
public:
    BoundingBox BBox;
    BVH* leftChild = NULL;
    BVH* rightChild = NULL;
    std::vector<int> *primitiveIndexes;
    std::vector< Primitive::PrimitiveUniquePtr > &primitivesReference;
    BVH(const std::vector< Primitive::PrimitiveUniquePtr > &primitivesReference);

}










#endif /* BVH_H_ */