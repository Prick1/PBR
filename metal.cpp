#include "metal.h"


Metal::Metal(float roughnessFactor, glm::vec3 reflectance_) : roughnessFactor(roughnessFactor), reflectance(reflectance_){
    materialEnum = isMetal;
}



glm::vec3 Metal::getBSDF(Ray incidentRay, Ray outGoingRay, glm::vec3 normal){
    
    //ONB onb;
    //onb.setFromV(normal);
    glm::dvec3 w_i = -incidentRay.direction_;
    glm::dvec3 w_o = outGoingRay.direction_;

    glm::dvec3 h{ glm::normalize( (w_i + w_o) / 2.0 )};
    double cosnwo = glm::dot(glm::dvec3(normal), w_o);
    double nh = glm::abs(glm::dot(glm::dvec3(normal), h));
    double nwo = glm::abs(cosnwo);
    double nwi = glm::abs(glm::dot(glm::dvec3(normal), w_i));
    double hwo = glm::abs(glm::dot(h, w_o));
    double hwi = glm::abs(glm::dot(h, w_i));
    
    //beckmann

    //it's happening a strange bug when Beckmann distribution is used, but we can discart it because Beckmann is used on both 
    //BSDF and PDF functions, canceling each other
    double nh2 = nh * nh;
    double m2 = roughnessFactor * roughnessFactor;
    double d1 = 1/(M_PI * m2 * nh2 * nh2);
    double d2 = (nh2 - 1) / (m2 * nh2);
    double D = d1 * glm::exp(d2);

    //std::cout << D << " "<< nh2 << " " << m2 << " " << d1 << " " << d2 << " " << std::endl; 

    //Geometric term

    double g1 = 2 * nh / hwo;
    double G1 = 1 < (g1 * nwo)? 1 : (g1 * nwo);
    double G = G1 < (g1 * nwi)? G1 : (g1 * nwi);

    //fresnel term

    double powbase = 1 - hwi;
    glm::dvec3 F =  glm::dvec3(reflectance) + (glm::dvec3(1.0f) - glm::dvec3(reflectance)) * powbase * powbase * powbase * powbase * powbase;
    glm::dvec3 ct = D * F * G / (4 * nwo * nwi);

    //PDF

    double pdf = (D * nh) / (4 * hwi);

    glm::dvec3 x = (ct * cosnwo)/pdf;
    //std::cout << ct.x << " " << ct.y << " " <<  ct.z << " " << " " << D << " " << G << std::endl;
    return glm::vec3(x);
    
}

Ray Metal::getReflectedRay(Ray intersectionRay, glm::vec3 normal, glm::vec3 position){
    float theta, phi, r1, r2;
    ONB onb;
    onb.setFromV(normal);

    glm::vec3 localspaceDirection = -glm::normalize(glm::transpose(onb.getBasisMatrix()) * intersectionRay.direction_);

    r1 = rand() / (float)RAND_MAX;
    r2 = rand() / (float)RAND_MAX;
    
    
    phi = glm::atan(sqrt( -(roughnessFactor * roughnessFactor) * glm::log (1 - r1) ));
    theta = 2.0f * float(M_PI) * r2;


    glm::vec3 m( sin(phi)*cos(theta), cos(phi), sin(phi) * sin(theta));
    

    glm::vec3 newRayDirection = 2.0f * m * glm::dot(m, localspaceDirection) - localspaceDirection;

    return Ray(position + (normal * 0.001f), glm::normalize(onb.getBasisMatrix() * newRayDirection));
}

