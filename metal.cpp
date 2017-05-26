#include "metal.h"


Metal::Metal(float roughnessFactor, glm::vec3 reflectance_) : roughnessFactor(roughnessFactor), reflectance(reflectance_){
    materialEnum = isMetal;
}

float Metal::abs(float in){
    return in < 0.0f? -in : in;
}

glm::vec3 Metal::getBSDF(Ray incidentRay, Ray outGoingRay, glm::vec3 normal){
    glm::vec3 incidentVector = outGoingRay.direction_;
    glm::vec3 outGoingVector = incidentRay.direction_;

    glm::vec3 h{ glm::normalize( (incidentVector + outGoingVector) / 2.0f )};
    float nh = abs(glm::dot(normal, h));
    float nwo = abs(glm::dot(normal, outGoingVector));
    float nwi = abs(glm::dot(normal, incidentVector));
    float hwo = abs(glm::dot(h, outGoingVector));
    float hwi = abs(glm::dot(h, incidentVector));
    
    //beckmann
    float nh2 = nh * nh;
    float m2 = roughnessFactor * roughnessFactor;
    float d1 = 1/((float)M_PI * m2 * nh2 * nh2);
    float d2 = (nh2 - 1) / (m2 * nh2);
    float D = d1 * glm::exp(d2);

    //Geometric term

    float g1 = 2 * nh / hwo;
    float G1 = 1 < (g1 * nwo)? 1 : (g1 * nwo);
    float G = G1 < (g1 * nwi)? G1 : (g1 * nwi);

    //fresnel term
    float powbase = 1 - hwi;
    glm::vec3 F =  reflectance + (glm::vec3(1.0f) - reflectance) * powbase * powbase * powbase * powbase * powbase;

    glm::vec3 ct = D * F * G / (4 * nwo * nwi);

    //std::cout << ct.x << " " << ct.y << " " <<  ct.z << " " << " " << D << " " << G << std::endl;
    return ct;
    
}

Ray Metal::getReflectedRay(Ray intersectionRay, glm::vec3 normal, glm::vec3 position){
    float theta, phi, r1, r2;
    ONB onb;
    r1 = rand() / (float)RAND_MAX;
    r2 = rand() / (float)RAND_MAX;
    
    
    phi = glm::acos(1 - r1);
    theta = 2.0f * float(M_PI) * r2;

    glm::vec3 newRayDirection( sin(phi)*cos(theta), cos(phi), sin(phi) * sin(theta));
    
    onb.setFromV(normal);
    newRayDirection = glm::normalize(onb.getBasisMatrix() * newRayDirection);
	    

    return Ray(position + (normal * 0.001f), newRayDirection);
}

