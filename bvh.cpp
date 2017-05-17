#include "bvh.h"

BVH::BVH(const PrimitiveVector &primitivesReferenceIn) : primitivesReference(primitivesReferenceIn){
    glm::vec3 min(std::numeric_limits<float>::infinity());
    glm::vec3 max(-std::numeric_limits<float>::infinity());
    for(unsigned int i = 0; i < primitivesReferenceIn.size(); i++){
        for(int j = 0; j < 3; j++){
            if(primitivesReferenceIn[i].minPoint[j] < min[j])
                min[j] = primitivesReferenceIn[i].minPoint[j];
            if(primitivesReferenceIn[i].maxPoint[j] > max[j])
                max[j] = primitivesReferenceIn[i].minPoint[j];
        }
    }

    BBox = BoundingBox(min, max);
    glm::vec3 centroid = (min + max)/2;
    glm::vec3 size = max - min;
    int axis;
    if(size.x > size.y){
        if(size.x > size.z)
            axis = 0;
        else 
            axis = 2;
    }
    else{
        if(size.y > size.z)
            axis = 1;
        else 
            axis = 2;
    }

    std::vector<int> *leftPrimitivesIndexes = new std::vector<int>;
    std::vector<int> *rightPrimitivesIndexes = new std::vector<int>;
    for (unsigned int i = 0; i < primitivesReferenceIn.size(); i++){
        if(primitivesReferenceIn[i].centroid[axis] < centroid[axis])
            leftPrimitivesIndexes->push_back(i);
        else
            rightPrimitivesIndexes->push_back(i);
    }
    leftChild = new BVH(primitivesReferenceIn, leftPrimitivesIndexes);
    rightChild = new BVH(primitivesReferenceIn, rightPrimitivesIndexes);

}

BVH::BVH(const PrimitiveVector &primitivesReferenceIn, std::vector<int> *primitiveIndexesIn) : primitivesReference(primitivesReferenceIn), primitiveIndexes(primitiveIndexesIn){
    glm::vec3 min(std::numeric_limits<float>::infinity());
    glm::vec3 max(-std::numeric_limits<float>::infinity());
    for(unsigned int i = 0; i < primitiveIndexesIn.size(); i++){
        for(int j = 0; j < 3; j++){
            if(primitivesReferenceIn[primitiveIndexesIn[i]].minPoint[j] < min[j])
                min[j] = primitivesReferenceIn[primitiveIndexesIn[i]].minPoint[j];
            if(primitivesReferenceIn[i].maxPoint[j] > max[j])
                max[j] = primitivesReferenceIn[primitiveIndexesIn[i]].minPoint[j];
        }
    }

    BBox = BoundingBox(min, max);
    if(primitiveIndexesIn > 3){
        glm::vec3 centroid = (min + max)/2;
        glm::vec3 size = max - min;
        int axis;
        if(size.x > size.y){
            if(size.x > size.z)
                axis = 0;
            else 
                axis = 2;
        }
        else{
            if(size.y > size.z)
                axis = 1;
            else 
                axis = 2;
        }


        std::vector<int> *leftPrimitivesIndexes = new std::vector<int>;
        std::vector<int> *rightPrimitivesIndexes = new std::vector<int>;
        for (unsigned int i = 0; i < primitiveIndexesIn.size(); i++){
            if(primitivesReferenceIn[primitiveIndexesIn[i]].centroid[axis] < centroid[axis])
                leftPrimitivesIndexes->push_back(primitiveIndexesIn[i]);
            else
                rightPrimitivesIndexes->push_back(primitiveIndexesIn[i]);
        }
        leftChild = new BVH(primitivesReferenceIn, leftPrimitivesIndexes);
        rightChild = new BVH(primitivesReferenceIn, rightPrimitivesIndexes);
    }
} 