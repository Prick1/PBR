#include "boundingbox.h"

BoundingBox::BoundingBox(void){}

BoundingBox::BoundingBox( const glm::vec3 &negative_corner, const glm::vec3 &positive_corner): negativeCorner(negative_corner), positiveCorner(positive_corner)
{}

bool BoundingBox::intersect( const Ray &ray){
	for(int i = 0; i < 3; i++){

		int j = (i+1)%3;
		int k = (i+2)%3;

		glm::vec3 intersect_point;
		float t = (positiveCorner[i] - ray.origin_[i]) / ray.direction_[i];

		intersect_point[i] = positiveCorner[i];
		intersect_point[j] = ray.origin_[j] + t*ray.direction_[j];
		intersect_point[k] = ray.origin_[k] + t*ray.direction_[k];

		if(intersect_point[j] <= positiveCorner[j] &&
		   intersect_point[j] >= negativeCorner[j] &&
		   intersect_point[k] <= positiveCorner[k] &&
		   intersect_point[k] >= negativeCorner[k] )
			return true;
	}

	for(int i = 0; i < 3; i++){

		int j = (i+1)%3;
		int k = (i+2)%3;

		glm::vec3 intersect_point;
		float t = (negativeCorner[i] - ray.origin_[i]) / ray.direction_[i];

		intersect_point[i] = negativeCorner[i];
		intersect_point[j] = ray.origin_[j] + t*ray.direction_[j];
		intersect_point[k] = ray.origin_[k] + t*ray.direction_[k];

		if(intersect_point[j] <= positiveCorner[j] &&
		   intersect_point[j] >= negativeCorner[j] &&
		   intersect_point[k] <= positiveCorner[k] &&
		   intersect_point[k] >= negativeCorner[k] )
			return true;
	}

	return false;
}

