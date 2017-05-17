#include "bvh.h"


BVH::BVH(PrimitiveVector &primitivesReferenceIn) : primitivesReference(primitivesReferenceIn){
    glm::vec3 min(std::numeric_limits<float>::infinity());
    glm::vec3 max(-std::numeric_limits<float>::infinity());
    glm::vec3 centroid(0.0f);
    for(unsigned int i = 0; i < primitivesReferenceIn.size(); i++){
        for(int j = 0; j < 3; j++){
            if(primitivesReferenceIn[i]->minPoint[j] < min[j])
                min[j] = primitivesReferenceIn[i]->minPoint[j];
            if(primitivesReferenceIn[i]->maxPoint[j] > max[j])
                max[j] = primitivesReferenceIn[i]->maxPoint[j];
        }
        centroid += primitivesReferenceIn[i]->centroid;
    }
    centroid /= primitivesReferenceIn.size();
    BBox = BoundingBox(min, max);
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
        if(primitivesReferenceIn[i]->centroid[axis] < centroid[axis])
            leftPrimitivesIndexes->push_back(i);
        else
            rightPrimitivesIndexes->push_back(i);
    }
    while(leftPrimitivesIndexes->size() > rightPrimitivesIndexes->size()){
            int leftMaxIndex = -1;
            float maxF = -std::numeric_limits<float>::infinity();
            for(unsigned int i = 0; i < leftPrimitivesIndexes->size() ; i++){
                if (primitivesReferenceIn[(*leftPrimitivesIndexes)[i]]->centroid[axis] > maxF){
                    maxF = primitivesReferenceIn[(*leftPrimitivesIndexes)[i]]->centroid[axis];
                    leftMaxIndex = i;
                }
            }
            rightPrimitivesIndexes->push_back((*leftPrimitivesIndexes)[leftMaxIndex]);
            leftPrimitivesIndexes->erase(leftPrimitivesIndexes->begin() + leftMaxIndex);
        }
    while(rightPrimitivesIndexes->size() > leftPrimitivesIndexes->size()){
            int rightMinIndex = -1;
            float minF = std::numeric_limits<float>::infinity();
            for(unsigned int i = 0; i < leftPrimitivesIndexes->size() ; i++){
                if (primitivesReferenceIn[(*leftPrimitivesIndexes)[i]]->centroid[axis] < minF){
                    minF = primitivesReferenceIn[(*leftPrimitivesIndexes)[i]]->centroid[axis];
                    rightMinIndex = i;
                }
            }
            leftPrimitivesIndexes->push_back((*rightPrimitivesIndexes)[rightMinIndex]);
            rightPrimitivesIndexes->erase(rightPrimitivesIndexes->begin() + rightMinIndex);
    }
    /*std::cout << primitivesReferenceIn.size() << std::endl;
    std::cout << leftPrimitivesIndexes->size() << std::endl;
    std::cout << rightPrimitivesIndexes->size() << std::endl;*/
    leftChild = new BVH(primitivesReferenceIn, leftPrimitivesIndexes);
    rightChild = new BVH(primitivesReferenceIn, rightPrimitivesIndexes);

}

BVH::BVH(PrimitiveVector &primitivesReferenceIn, std::vector<int> *primitiveIndexesIn) : primitivesReference(primitivesReferenceIn), primitiveIndexes(primitiveIndexesIn){
    glm::vec3 min(std::numeric_limits<float>::infinity());
    glm::vec3 max(-std::numeric_limits<float>::infinity());
    glm::vec3 centroid(0.0f);
    for(unsigned int i = 0; i < primitiveIndexesIn->size(); i++){
        for(int j = 0; j < 3; j++){
            if(primitivesReferenceIn[(*primitiveIndexesIn)[i]]->minPoint[j] < min[j])
                min[j] = primitivesReferenceIn[(*primitiveIndexesIn)[i]]->minPoint[j];
            if(primitivesReferenceIn[(*primitiveIndexesIn)[i]]->maxPoint[j] > max[j])
                max[j] = primitivesReferenceIn[(*primitiveIndexesIn)[i]]->maxPoint[j];
        }
        centroid += primitivesReferenceIn[(*primitiveIndexesIn)[i]]->centroid;
    }
    centroid /= primitiveIndexesIn->size();
    BBox = BoundingBox(min, max);
    if(primitiveIndexesIn->size() > 3){
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
        for (unsigned int i = 0; i < primitiveIndexesIn->size(); i++){
            if(primitivesReferenceIn[(*primitiveIndexesIn)[i]]->centroid[axis] < centroid[axis])
                leftPrimitivesIndexes->push_back((*primitiveIndexesIn)[i]);
            else
                rightPrimitivesIndexes->push_back((*primitiveIndexesIn)[i]);
        }
        while(leftPrimitivesIndexes->size() > rightPrimitivesIndexes->size()){
                int leftMaxIndex = -1;
                float maxF = -std::numeric_limits<float>::infinity();
                for(unsigned int i = 0; i < leftPrimitivesIndexes->size() ; i++){
                    if (primitivesReferenceIn[(*leftPrimitivesIndexes)[i]]->centroid[axis] > maxF){
                        maxF = primitivesReferenceIn[(*leftPrimitivesIndexes)[i]]->centroid[axis];
                        leftMaxIndex = i;
                    }
                }
                rightPrimitivesIndexes->push_back((*leftPrimitivesIndexes)[leftMaxIndex]);
                leftPrimitivesIndexes->erase(leftPrimitivesIndexes->begin() + leftMaxIndex);
        }
        while(rightPrimitivesIndexes->size() > leftPrimitivesIndexes->size()){
                int rightMinIndex = -1;
                float minF = std::numeric_limits<float>::infinity();
                for(unsigned int i = 0; i < leftPrimitivesIndexes->size() ; i++){
                    if (primitivesReferenceIn[(*leftPrimitivesIndexes)[i]]->centroid[axis] < minF){
                        minF = primitivesReferenceIn[(*leftPrimitivesIndexes)[i]]->centroid[axis];
                        rightMinIndex = i;
                    }
                }
                leftPrimitivesIndexes->push_back((*rightPrimitivesIndexes)[rightMinIndex]);
                rightPrimitivesIndexes->erase(rightPrimitivesIndexes->begin() + rightMinIndex);
        }
                        
        leftChild = new BVH(primitivesReferenceIn, leftPrimitivesIndexes);
        rightChild = new BVH(primitivesReferenceIn, rightPrimitivesIndexes);
    }
    else{
        leftChild = NULL;
        rightChild = NULL;
    }
} 


bool BVH::intersect(const Ray &ray, IntersectionRecord &intersection_record){
    if(BBox.intersect(ray, intersection_record)){
        if(leftChild != NULL || rightChild != NULL){
            bool intersection_result_left = false;
            bool intersection_result_right = false;
            if(leftChild != NULL)
                intersection_result_left = leftChild->intersect(ray, intersection_record);
            if(rightChild != NULL)
                intersection_result_right = rightChild->intersect(ray, intersection_record);
            return intersection_result_left || intersection_result_right;
        }

        else{
            bool intersection_result = false; 
            IntersectionRecord tmp_intersection_record;

            for(unsigned int i = 0; i < primitiveIndexes->size(); i++){
                if(primitivesReference[(*primitiveIndexes)[i]]->intersect(ray, tmp_intersection_record))
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