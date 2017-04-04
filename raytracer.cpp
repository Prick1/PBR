#include "raytracer.h"


RayTracer::RayTracer( Camera &camera,
                      const Scene &scene,
                      const glm::vec3 background_color,
                      Buffer &buffer ) :
        camera_( camera ),
        scene_( scene ),
        background_color_{ background_color },
        buffer_( buffer )
{
    std::uniform_real_distribution<float> dist_x(0.0f, 1.0f);
    std::uniform_real_distribution<float> dist_y(0.0f, 1.0f);
    //std::uniform_real_distribution<float> dist_theta(0.0f, 2.0f * float(M_PI)); 
    //std::uniform_real_distribution<float> dist_phi(0.0f, 1.0f);
}

void RayTracer::integrate( void )
{
    //IntersectionRecord intersection_record;

    // Image space origin (i.e. x = 0 and y = 0) at the top left corner.

    // Loops over image rows
    
    for ( std::size_t y = 0; y < buffer_.v_resolution_; y++ )
    {
        std::stringstream progress_stream;
        progress_stream << "\r  progress .........................: "
                        << std::fixed << std::setw( 6 )
                        << std::setprecision( 2 )
                        << 100.0 * y / ( buffer_.v_resolution_ - 1 )
                        << "%";

        std::clog << progress_stream.str();

        // Loops over image columns
        for ( std::size_t x = 0; x < buffer_.h_resolution_; x++ )
        {
            for(unsigned int i = 0; i < RAYS; i++){
                //intersection_record.t_ = std::numeric_limits< double >::max();

                Ray ray{ camera_.getWorldSpaceRay( glm::vec2{ x + dist_x(generator), y + dist_y(generator) } ) };

                //if ( scene_.intersect( ray, intersection_record ) )
                    //buffer_.buffer_data_[x][y] = glm::vec3{ 1.0f, 0.0f, 0.0f };
                    //buffer_.buffer_data_[x][y] = glm::vec3{ intersection_record.intersectionColor};
                     buffer_.buffer_data_[x][y] += L(ray,0);
            }
            buffer_.buffer_data_[x][y] /= RAYS;
	    glm::clamp(buffer_.buffer_data_[x][y], glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{1.0f, 1.0f, 1.0f});
        }
    }

    std::clog << std::endl;
}

glm::vec3 RayTracer::L(const Ray& r, int depth){
    glm::vec3 Lo(0.0f);

    IntersectionRecord intersection_record;
    intersection_record.t_ = std::numeric_limits< double >::max();

    if(depth < 5){
        if(scene_.intersect(r, intersection_record)){
            //phi = acos(1 - dist_phi(generator));
            //theta = dist_theta(generator);
            
	    /*if(costheta < 0.0f){
		costheta = -costheta;
		newRayDirection = - newRayDirection;
		}*/

            Ray reflect = intersection_record.intersectionMaterial->getRefflectedRay(intersection_record.normal_, intersection_record.position_);
	    float costheta = glm::dot (intersection_record.normal_, reflect.direction_);

            Lo = intersection_record.intersectionMaterial->emittance_ +
                 2.0f * float(M_PI) * intersection_record.intersectionMaterial->getBRDF()
                 * L(reflect, ++depth) * costheta;

        }
    }
    return Lo;
}

