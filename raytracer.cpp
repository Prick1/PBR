#include "raytracer.h"


RayTracer::RayTracer( Camera &camera,
                      const Scene &scene,
                      const glm::vec3 background_color,
                      Buffer &buffer, 
                      const unsigned int &rays ) :
        camera_( camera ),
        scene_( scene ),
        background_color_{ background_color },
        buffer_( buffer ),
        rays_( rays )
{}

void RayTracer::integrate(const int numberThreads)
{
    progress = new int[numberThreads];  

    numBlocksH = buffer_.h_resolution_/blockSizeH;
    numBlocksV = buffer_.h_resolution_/blockSizeV; 
    numBlocks = numBlocksH * numBlocksV;

    for(unsigned int i = 0; i < (unsigned int)numberThreads; i++){
        progress[i] = 0;
        threads.push_back(new std::thread(&RayTracer::thread_integrate, this, i));
    }

    print_progress();

    for(unsigned int i = 0; i < (unsigned int)numberThreads; i++){
        threads[i]->join();
        delete threads[i];
    }

    threads.clear();
}

void RayTracer::thread_integrate(const int threadId){
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    //std::uniform_real_distribution<float> dist_y(0.0f, 1.0f);
    std::mt19937 generator;
    
    std::size_t initX, initY, maxX, maxY, workingBlock;

    while(1){
        workingBlock = atomicBlock++;
        if(workingBlock >= numBlocks)
            break;
        
        initX = (workingBlock % numBlocksH) * blockSizeH;
        initY = (workingBlock / numBlocksH) * blockSizeV;

        maxX = initX + blockSizeH; 
        maxY = initY + blockSizeV;

        if(maxX > (std::size_t)buffer_.h_resolution_) 
            maxX = (std::size_t)buffer_.h_resolution_;
        if(maxY > (std::size_t)buffer_.v_resolution_)
            maxY = (std::size_t)buffer_.v_resolution_;

        for ( std::size_t y = initY; y < maxY; y++ ) {

            for ( std::size_t x = initX; x < maxX; x++ ){
            
                for(unsigned int i = 0; i < rays_; i++){

                    Ray ray{ camera_.getWorldSpaceRay( glm::vec2{ x + dist(generator), y + dist(generator) } ) };

                    buffer_.buffer_data_[x][y] += L(ray,1);
                }

            buffer_.buffer_data_[x][y] /= rays_;
            progress[threadId]++;
            }  
        }


    }

}

glm::vec3 RayTracer::L(const Ray& r, int depth){
    glm::vec3 Lo(0.0f);

    IntersectionRecord intersection_record;
    intersection_record.t_ = std::numeric_limits< double >::max();

    if(depth < 6){
        if(scene_.intersect(r, intersection_record)){
            float costheta;

            Ray reflect = intersection_record.intersectionMaterial->getReflectedRay(r, intersection_record.normal_, intersection_record.position_);
            
            switch(intersection_record.intersectionMaterial->materialEnum){
                
                case isLightSource:

                    Lo = intersection_record.intersectionMaterial->getBSDF(r, reflect, intersection_record.normal_);
                    break;

                case isDiffuse:

                    costheta = glm::dot (intersection_record.normal_, reflect.direction_);
                    Lo = 2.0f * float(M_PI) * intersection_record.intersectionMaterial->getBSDF(r, reflect, intersection_record.normal_) * L(reflect, ++depth) * costheta;
                    break;

                
                case isMetal:
                case isSpecular:
                case isDielectric:

                    Lo = intersection_record.intersectionMaterial->getBSDF(r, reflect, intersection_record.normal_)*L(reflect, ++depth);
                    break;

                

            }
            
        }
    }
    return Lo;
}

void RayTracer::print_progress(void){
    int workingBlock;
	int completedBlocks;
    
    unsigned long remainingTime = 0;
	unsigned long prevTotalTime = 0;
    std::time_t initialTime = time(NULL);
	
	int totalProgress;
    int numPixels = buffer_.h_resolution_ * buffer_.v_resolution_;

    while(1){
        workingBlock = atomicBlock;

        completedBlocks = workingBlock - threads.size();
        if (completedBlocks < 0)
            completedBlocks = 0;
        
        totalProgress = 0;
        for(unsigned int i = 0; i < threads.size(); i++)
            totalProgress += progress[i];

        std::stringstream progress_stream;
        progress_stream << "\r  progress .........................: "
                        << std::fixed << std::setw( 6 )
                        << std::setprecision( 2 )
                        << 100.0 * (float)totalProgress/numPixels 
                        << "% | " <<
                        completedBlocks << "/" << numBlocks;

        if(totalProgress){
            prevTotalTime = numPixels * difftime(time(NULL), initialTime) / totalProgress;
            remainingTime = prevTotalTime - difftime(time(NULL), initialTime);

            progress_stream << " | " << remainingTime/3600 << " h " 
			 				       << (remainingTime/60)%60 << " min "
                                   << remainingTime%60 << " s ";


        }

        std::clog << progress_stream.str();

        if((unsigned int)workingBlock >= numBlocks + threads.size())
            break;
        
        std::this_thread::sleep_for(std::chrono::seconds(2));

    }

    std::clog << std::endl; 
}
