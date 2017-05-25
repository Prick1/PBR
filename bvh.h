#ifndef BVH_H_
#define BVH_H_

#include "boundingbox.h"
#include <algorithm>
#include <climits>



typedef std::vector< Primitive::PrimitiveUniquePtr > PrimitiveVector;

class BVH{
private:
    glm::vec3 max_components(const glm::vec3 &vecA, const glm::vec3 &vecB);
    glm::vec3 min_components(const glm::vec3 &vecA, const glm::vec3 &vecB);
    void BVHBuildNode(BoundingBox *node, std::vector<int> &primitivesIndex);
public:
    BVH(PrimitiveVector &primitivesReferenceIn);
    BoundingBox* root;
    PrimitiveVector &primitives;
    void BVHBuild();
};








#endif /* BVH_H_ */