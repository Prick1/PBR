#include "lightsource.h"

LightSource::LightSource(glm::vec3 emittance): emittance_(emittance){
    materialEnum = isLightSource;
}




Ray LightSource::getReflectedRay(Ray intersectionRay, glm::vec3 normal, glm::vec3 position){
    return Ray(glm::vec3(0), glm::vec3(0));
}

glm::vec3 LightSource::getBSDF(){
	return emittance_;
}
