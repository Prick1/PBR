#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <sstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <random>

#include "camera.h"
#include "scene.h"
#include "buffer.h"
#define RAYS 30

class RayTracer
{
public:

    RayTracer( Camera &camera,
               const Scene &scene,
               const glm::vec3 background_color,
               Buffer &buffer );

    void integrate( void );

private:
    std::uniform_real_distribution<float> dist_x;
    std::uniform_real_distribution<float> dist_y;
    std::uniform_real_distribution<float> dist_theta;
    std::uniform_real_distribution<float> dist_phi;
    std::mt19937 generator;


    const Camera &camera_;

    const Scene &scene_;

    glm::dvec3 background_color_;

    Buffer &buffer_;
    glm::vec3 L(const Ray& r, int depth);

};

#endif /* RAYTRACER_H_ */

