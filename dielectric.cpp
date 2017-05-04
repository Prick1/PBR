#include "dielectric.h"

Dielectric::Dielectric(float externalMedia,float internalMedia): 
    internalMedia_(internalMedia),
    externalMedia_(externalMedia){
    materialEnum = isDielectric;
}

float Dielectric::Schlick(glm::vec3 incident, glm::vec3 normal, float n1, float n2){

    float Ro = (n1 - n2)/(n1 + n2);
    Ro *= Ro;
    float cosX = -glm::dot(normal, incident);
    //cosX = cosX < 0.0f? -cosX : cosX;
    if(n1 > n2){
        float n = n1 / n2;
        float cosT2 = 1.0f - n * n * (1.0f - cosX * cosX);
        if(cosT2 < 0.0f)//TIR
            return 1.0f;
        cosX = sqrt(cosT2);
    }

    float x = 1.0f - cosX;
    return Ro + (1.0f - Ro)* x * x * x * x * x;
}
glm::vec3 Dielectric::Reflect(glm::vec3 incident, glm::vec3 normal){
    ONB onb;
    onb.setFromV(normal);
    glm::vec3 reflectedDirection = glm::transpose(onb.getBasisMatrix()) * incident;
    reflectedDirection.y = -reflectedDirection.y; 
    return onb.getBasisMatrix() * reflectedDirection;
}

glm::vec3 Dielectric::Refract(glm::vec3 incident, glm::vec3 normal,float n1, float n2){
    float n = n1 / n2;
    float cos1 = -glm::dot(normal, incident);
    //cos1 = cos1 < 0? cosI : -cosI;
    float cos2 = 1.0 - n * n * (1.0f - cos1 * cos1);

    if(cos2 < 0.0f)//TIR
        return glm::vec3(0.0f);
    
    cos2 = sqrt(cos2);
    return n * incident + (n * cos1 - cos2) * normal;
}

Ray Dielectric::getReflectedRay(Ray intersectionRay, glm::vec3 normal, glm::vec3 position){
    //ONB localSpaceToWorld;
   
    //glm::vec3 normal2(0,1,0);

    float cosX = glm::dot(intersectionRay.direction_, normal);
    float random = rand() / (float)RAND_MAX;
    //glm::vec3 invertedDirection = -incomingDirectionInLocalSpace;
    float n1, n2;

    if(cosX < 0.0f){//Ray is coming from the external media(n1) to internal media(n2)
        n1 = externalMedia_;
        n2 = internalMedia_;
    }

    else{//Ray is coming from the internal media(n1) to external media(n2)
        n1 = internalMedia_;
        n2 = externalMedia_;
        normal = - normal;
    }

    //localSpaceToWorld.setFromV(normal);
    glm::vec3 newRayDirection;
    //glm::vec3 incomingDirectionInLocalSpace = glm::transpose(localSpaceToWorld.getBasisMatrix()) * intersectionRay.direction_;
    //incomingDirectionInLocalSpace = -incomingDirectionInLocalSpace;

    float schlick = Schlick(intersectionRay.direction_, normal, n1, n2);
    if(random < schlick)
        newRayDirection = Reflect(intersectionRay.direction_, normal);
    else{
        newRayDirection = Refract(intersectionRay.direction_, normal, n1, n2);
        normal = -normal;
    }

    return Ray(position + (normal*0.001f),/*localSpaceToWorld.getBasisMatrix() **/glm::normalize(newRayDirection));

}

glm::vec3 Dielectric::getBSDF(){
    return glm::vec3(1.0f);
}