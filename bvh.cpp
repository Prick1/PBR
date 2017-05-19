#include "bvh.h"

glm::vec3 max_components2(const glm::vec3 &vecA, const glm::vec3 &vecB){

	glm::vec3 max;

	for(int i = 0; i < 3; i++)
		if(vecA[i] > vecB[i])
			max[i] = vecA[i];
		else
			max[i] = vecB[i];

	return max;
}

glm::vec3 min_components2(const glm::vec3 &vecA, const glm::vec3 &vecB){

	glm::vec3 min;

	for(int i = 0; i < 3; i++)
		if(vecA[i] < vecB[i])
			min[i] = vecA[i];
		else
			min[i] = vecB[i];

	return min;
}

BVH* BVH::BVHBuild(PrimitiveVector &primitivesReferenceIn){
    std::vector<int>* primitiveIndex = new std::vector<int>;
    for(unsigned int i = 0; i < primitivesReferenceIn.size(); i++)
        primitiveIndex->push_back(i);
    std::ofstream logfile;
    logfile.open("log.txt");
    return new BVH(primitivesReferenceIn, primitiveIndex, logfile);
    logfile.close();
}

glm::vec3 module(glm::vec3 size){
    for(int i = 0; i < 3; i++)
        size[i] = size[i] >= 0.0f ? size[i]: -size[i];
    return size;
}

BVH::BVH(PrimitiveVector &primitivesReferenceIn, std::vector<int> *primitiveIndexesIn, std::ofstream& logfile) : primitivesReference(primitivesReferenceIn), primitiveIndexes(primitiveIndexesIn){
    glm::vec3 min(std::numeric_limits<float>::max());
    glm::vec3 max(-std::numeric_limits<float>::max());
    //glm::vec3 centroid(0.0f);
    for(unsigned int i = 0; i < primitiveIndexesIn->size(); i++){
            max = max_components2(max, primitivesReferenceIn[(*primitiveIndexesIn)[i]]->maxPoint);
            min = min_components2(min, primitivesReferenceIn[(*primitiveIndexesIn)[i]]->minPoint);
    }
    BBox = BoundingBox(min, max);
    if(primitiveIndexesIn->size() > 3){
        glm::vec3 size = module(max - min);
        int axis = 0;
        for (int i = 1; i < 3; i++){
            if(size[i] >= size[axis]){
                axis = i;
            }
        }
        Compare comp(&primitivesReferenceIn, axis);

        std::sort(primitiveIndexesIn->begin(), primitiveIndexesIn->end(), comp);
        std::vector<int> *leftPrimitivesIndexes = new std::vector<int>;
        std::vector<int> *rightPrimitivesIndexes = new std::vector<int>;
        for(unsigned int i = 0; i < primitiveIndexesIn->size()/2 ; i++){
            leftPrimitivesIndexes->push_back((*primitiveIndexesIn)[i]);
        }
        for(unsigned int i = primitiveIndexesIn->size()/2; i < primitiveIndexesIn->size() ; i++){
            rightPrimitivesIndexes->push_back((*primitiveIndexesIn)[i]);
        }
                        
        leftChild = new BVH(primitivesReferenceIn, leftPrimitivesIndexes, logfile);
        rightChild = new BVH(primitivesReferenceIn, rightPrimitivesIndexes, logfile);
    }
    else{
        leftChild = NULL;
        rightChild = NULL;
    }
     logfile << "Bounding Box Dimensions: " << std::endl <<
        "Negative Corner: (" << BBox.negativeCorner.x << ", " << BBox.negativeCorner.y << ", " << BBox.negativeCorner.z << ")" << std::endl <<
        "Positive Corner: (" << BBox.positiveCorner.x << ", " << BBox.positiveCorner.y << ", " << BBox.positiveCorner.z << ")" << std::endl << std::endl <<
        "Primitive Centroids: " << std::endl;
        for(unsigned int i = 0; i < primitiveIndexesIn->size(); i++){
            logfile << "[" << (*primitiveIndexesIn)[i] << "]" << "(" << primitivesReferenceIn[(*primitiveIndexesIn)[i]]->centroid.x << ", " 
            << primitivesReferenceIn[(*primitiveIndexesIn)[i]]->centroid.y << ", " 
            << primitivesReferenceIn[(*primitiveIndexesIn)[i]]->centroid.z << ")" << std::endl << std::endl;
        } 
        logfile << "Primitive Maximums: " << std::endl;
        for(unsigned int i = 0; i < primitiveIndexesIn->size(); i++){
            logfile << "[" << (*primitiveIndexesIn)[i] << "]" << "(" << primitivesReferenceIn[(*primitiveIndexesIn)[i]]->maxPoint.x << ", " 
            << primitivesReferenceIn[(*primitiveIndexesIn)[i]]->maxPoint.y << ", " 
            << primitivesReferenceIn[(*primitiveIndexesIn)[i]]->maxPoint.z << ")" << std::endl << std::endl;
        } 
         logfile << "Primitive Minimums: " << std::endl;
        for(unsigned int i = 0; i < primitiveIndexesIn->size(); i++){
            logfile << "[" << (*primitiveIndexesIn)[i] << "]" << "(" << primitivesReferenceIn[(*primitiveIndexesIn)[i]]->minPoint.x << ", " 
            << primitivesReferenceIn[(*primitiveIndexesIn)[i]]->minPoint.y << ", " 
            << primitivesReferenceIn[(*primitiveIndexesIn)[i]]->minPoint.z << ")" << std::endl << std::endl;
        } 
        logfile << "--------------------------------------------------------------------------------" << std::endl; 
} 


bool BVH::intersect(const Ray &ray, IntersectionRecord &intersection_record){
    if(BBox.intersect(ray)){
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
                if(primitivesReference[(*primitiveIndexes)[i]]->intersect(ray, tmp_intersection_record)){
                    if ( ( tmp_intersection_record.t_ < intersection_record.t_ ) && ( tmp_intersection_record.t_ > 0.0 ) ){
                            intersection_record = tmp_intersection_record;
                             intersection_result = true; // the ray intersects a primitive!
                    }
                }
            }
            return intersection_result;
        }
    }
    else{
        return false;
    }
}

