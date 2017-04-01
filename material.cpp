#include "material.h"

Material::Material(glm::vec3 emittance, glm::vec3 reflectance):
emittance_(emittance / (float)M_PI), reflectance_(reflectance / (float)M_PI){}