#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <sstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <random>
#include <atomic>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>

#include "camera.h"
#include "scene.h"
#include "buffer.h"
#define RAYS 10000

class RayTracer
{
public:

    RayTracer( Camera &camera,
               const Scene &scene,
               const glm::vec3 background_color,
               Buffer &buffer, const unsigned int &rays = 1000);

    void integrate(const int numberThreads = 4);

private:
    unsigned int rays_;

    std::vector<std::thread*> threads; 

    const Camera &camera_;

    const Scene &scene_;

    glm::dvec3 background_color_;

    Buffer &buffer_;

    std::atomic<std::size_t> atomicBlock{0};


    std::size_t numBlocksV;
    std::size_t numBlocksH;
    std::size_t numBlocks;

    const std::size_t blockSizeV = 32;
    const std::size_t blockSizeH = 32;

    int *progress;

    glm::vec3 L(const Ray& r, int depth);

    void thread_integrate(const int threadId);
    void print_progress(void);

};

#endif /* RAYTRACER_H_ */

