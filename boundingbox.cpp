#include "boundingbox.h"

BoundingBox::BoundingBox(void){}

BoundingBox::BoundingBox( const glm::vec3 &negative_corner, const glm::vec3 &positive_corner): negativeCorner(negative_corner), positiveCorner(positive_corner);
{}

bool BoundingBox::intersect( const Ray &ray,
                        IntersectionRecord &intersection_record ) const{
    if(planIntersection(ray, glm::ivec3 (0,1,0), negativeCorner.y,)){
        return true;
    }
    else if(planIntersection(ray, glm::ivec3 (0,0,1), negativeCorner.z )){
        return true;
    }
    else if(planIntersection(ray, glm::ivec3 (0,1,0), positiveCorner.y )){
        return true;
    }
    else if(planIntersection(ray, glm::ivec3 (1,0,0), negativeCorner.x )){
        return true;
    }
    else if(planIntersection(ray, glm::ivec3 (1,0,0), positiveCorner.x )){
        return true;
    }
    else
        return false;
}

bool BoundingBox::planIntersection(const Ray &ray, const glm::vec3 &normal,
     const float &distance){
    int j = 0;
    int i;
    for (i = 0; i < 3; i++)
        if(normal[i] > 0)
            break;
    float t = (distance - ray.origin_[i])/ray.direction_[i];
    glm::vec3 intersectionPoint(ray.origin_.x + t*ray.direction_.x, ray.origin_.y + t*ray.direction_.y, ray.origin_.z + t*ray.direction_.z);
    for(int k = o; k < 2; k++){
        if(k == i)
            continue;
        if(intersectionPoint[k] < negativeCorner[k] || intersectionPoint[k] > positiveCorner[k])
            return false;
    }
    return true;

}