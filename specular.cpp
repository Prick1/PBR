#include "specular.h"

Specular::Specular(void){
    emittance_ = glm::vec3(0.0f);
    materialEnum = isSpecular;
}

Ray Specular::getReflectedRay(Ray intersectionRay, glm::vec3 normal, glm::vec3 position){
    ONB onb;
    onb.setFromV(normal);
    glm::vec3 reflectedDirection = glm::transpose(onb.getBasisMatrix()) * intersectionRay.direction_;
    reflectedDirection.y = -reflectedDirection.y;
    reflectedDirection = glm::normalize(onb.getBasisMatrix() * reflectedDirection);
    return Ray(position + (normal*0.001f), reflectedDirection);
}

glm::vec3 Specular::getBSDF(){
    return glm::vec3(1.0f);
}