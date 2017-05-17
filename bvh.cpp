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
        delete primitiveIndexesIn;
        leftChild = new BVH(primitivesReferenceIn, leftPrimitivesIndexes);
        rightChild = new BVH(primitivesReferenceIn, rightPrimitivesIndexes);
    }
} 


bool BVH::intersect(const Ray &ray, IntersectionRecord &intersection_record){
    if(BBox.intersect(ray, intersection_record)){
        if(leftChild != NULL || rightChild != NULL){
            bool intersection_result_left = false; 
            bool intersection_result_right = false;
            IntersectionRecord tmp_intersection_record_left;
            IntersectionRecord tmp_intersection_record_right;

            if(leftChild != NULL){
                intersection_result_left = leftChild->intersect(ray, tmp_intersection_record_left);
                if(intersection_result_left == true && tmp_intersection_record_left <= 0.0)
                    intersection_result_left = false;
            }
            if(rightChild != NULL){
                intersection_result_right = rightChild->intersect(ray, tmp_intersection_record_right);
                if(intersection_result_right == true && tmp_intersection_record_right <= 0.0)
                    intersection_result_right = false;
            }

            if(intersection_result_left || intersection_result_right){
                if(intersection_result_left && intersection_result_right)
                    intersection_record = tmp_intersection_record_left.t_ < tmp_intersection_record_right.t_ ? tmp_intersection_record_left : tmp_intersection_record_right;
                else if(intersection_result_left)
                    intersection_record = tmp_intersection_record_left;
                else
                    intersection_record = tmp_intersection_record_right;
            }
            return intersection_result_left || intersection_result_right;
        }

        else{
            bool intersection_result = false; 
            IntersectionRecord tmp_intersection_record;

            for(unsigned int i = 0; i < primitiveIndexes.size(); i++){
                if(primitivesReference[primitiveIndexes[i]].intersect(ray, tmp_intersection_record))
                    if ( ( tmp_intersection_record.t_ < intersection_record.t_ ) && ( tmp_intersection_record.t_ > 0.0 ) ){
                            intersection_record = tmp_intersection_record;
                             intersection_result = true; // the ray intersects a primitive!
                }
            }
            return intersection_result;
        }
    }
    return false;
}