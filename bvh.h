#ifndef BVH_H_
#define BVH_H_

#include "boundingbox.h"
#include <vector>
#include <algorithm>



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
    static BVH* BVHBuild(PrimitiveVector &primitivesReferenceIn);
    bool intersect(const Ray &ray, IntersectionRecord &intersection_record);
};

class Compare{
public:
    int axis;
    PrimitiveVector *primitivesReference;
    Compare(PrimitiveVector *pReferenceIn,int axisIn): axis(axisIn), primitivesReference(pReferenceIn){}
    bool operator() (int i, int j){
        return (*primitivesReference)[i]->centroid[axis] < (*primitivesReference)[j]->centroid[axis]; 
    }
};









#endif /* BVH_H_ */