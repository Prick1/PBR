#include "bvh.h"

BVH::BVH(PrimitiveVector &primitivesReferenceIn): primitives(primitivesReferenceIn){}

glm::vec3 BVH::max_components(const glm::vec3 &vecA, const glm::vec3 &vecB){

	glm::vec3 max;

	for(int i = 0; i < 3; i++)
		if(vecA[i] > vecB[i])
			max[i] = vecA[i];
		else
			max[i] = vecB[i];

	return max;
}

glm::vec3 BVH::min_components(const glm::vec3 &vecA, const glm::vec3 &vecB){

	glm::vec3 min;

	for(int i = 0; i < 3; i++)
		if(vecA[i] < vecB[i])
			min[i] = vecA[i];
		else
			min[i] = vecB[i];

	return min;
}
void BVH::BVHBuild(){
    std::vector<int> primitivesIndex;
    for(unsigned int i = 0; i < primitives.size(); i++)
        primitivesIndex.push_back(i);
    root = new BoundingBox;
    BVHBuildNode(root, primitivesIndex);
}

glm::vec3 module(glm::vec3 size){
    for(int i = 0; i < 3; i++)
        size[i] = size[i] >= 0.0f ? size[i]: -size[i];
    return size;
}

void BVH::BVHBuildNode(BoundingBox *node, std::vector<int> &primitivesIndex){
    node->primitivesIndex = nullptr;
    node->negativeCorner = primitives[primitivesIndex[0]] -> negativeCorner;
    node->positiveCorner = primitives[primitivesIndex[0]] -> positiveCorner;
    
    for(int primId: primitivesIndex){
        node->negativeCorner = min_components(primitives[primId]->negativeCorner, node->negativeCorner);
        node->positiveCorner = max_components(primitives[primId]->positiveCorner, node->positiveCorner);
    }

    node->center = node->negativeCorner;


    glm::vec3 bSize = node->positiveCorner - node->negativeCorner;
    float aux = std::max(bSize.x, std::max(bSize.y, bSize.z));
    int axis;
    if (aux == bSize.x)
        axis = 0;
    else if (aux == bSize.y)
        axis = 1;
    else
        axis = 2;

    std::vector<int> leftPrim;
    std::vector<int> rightPrim;

    int trying = 0;
    int initAxis = axis;
    float minCost = FLT_MAX;
    glm::vec3 bestCenter;
    int bestAxis = initAxis;
    glm::vec3 auxSize;
	float leftArea, rightArea, totalArea;
	float leftCost, rightCost, totalCost, noDivCost;
	glm::vec3 currentNegativeCorner;
    glm::vec3 currentPositiveCorner; 
    totalArea = (bSize.x*bSize.y + bSize.y*bSize.z + bSize.x*bSize.z) * 2.0f;
    noDivCost = primitivesIndex.size();

    do{
        while(trying++ < 32){
            for(int primId: primitivesIndex){
                if(primitives[primId]->center_[axis] < node->center[axis])
                    leftPrim.push_back(primId);
                else
                    rightPrim.push_back(primId);
            }

            if(leftPrim.size() > 0){
                currentNegativeCorner = primitives[leftPrim[0]]->negativeCorner;
                currentPositiveCorner = primitives[rightPrim[0]]->positiveCorner;

                for(int primId: leftPrim){
                    currentNegativeCorner = min_components(primitives[primId]->negativeCorner, currentNegativeCorner);
                    currentPositiveCorner = max_components(primitives[primId]->positiveCorner, currentPositiveCorner);
                }

                auxSize = (currentPositiveCorner - currentNegativeCorner);
                leftArea = (auxSize.x*auxSize.y + auxSize.y*auxSize.z + auxSize.x*auxSize.z) * 2.0f;
                leftCost = (leftArea / totalArea) * leftPrim.size();
            }
            else{leftCost = 0.0f;}


            if(rightPrim.size() > 0){
                currentNegativeCorner = primitives[leftPrim[0]]->negativeCorner;
                currentPositiveCorner = primitives[rightPrim[0]]->positiveCorner;

                for(int primId: rightPrim){
                    currentNegativeCorner = min_components(primitives[primId]->negativeCorner, currentNegativeCorner);
                    currentPositiveCorner = max_components(primitives[primId]->positiveCorner, currentPositiveCorner);
                }

                auxSize = (currentPositiveCorner - currentNegativeCorner);
                rightArea = (auxSize.x*auxSize.y + auxSize.y*auxSize.z + auxSize.x*auxSize.z) * 2.0f;
                rightCost = (rightArea / totalArea) * rightPrim.size();
            }
            else{rightCost = 0.0f;}

            totalCost = 2 + leftCost + rightCost;

            if(minCost > totalCost){
                minCost = totalCost;
                bestCenter = node->center;
                bestAxis = axis;
            }

            node->center[axis] = node->negativeCorner[axis] + bSize[axis] * (trying / 32.0f);

            leftPrim.clear();
            rightPrim.clear();
        }

        axis = (axis+1)%3;
        trying = 0;

    }while(axis != initAxis);

    if(noDivCost < minCost){
        node->primitivesIndex = new std::vector<int>(primitivesIndex.size());
        *(node->primitivesIndex) = primitivesIndex;
        node->left = nullptr;
        node->right = nullptr;
        return;
    }

    node->center = bestCenter;
    axis = bestAxis;

    for(int primId : primitivesIndex){
        if(primitives[primId]->center_[axis] < node->center[axis])
            leftPrim.push_back(primId);
        else
            rightPrim.push_back(primId);
    }
    
    node->left = new BoundingBox;
    BVHBuildNode(node->left, leftPrim);

    node->right = new BoundingBox;
    BVHBuildNode(node->right, rightPrim);

} 




