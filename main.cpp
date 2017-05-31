#include "main.h"

/* Execute: ./swpathtracer <rays> <threads> <outputname>*/
int main( int argc, char * argv[])
{
    unsigned int x_resolution = 512;
    unsigned int y_resolution = 512;

    PerspectiveCamera camera{ -1.25f, 
                                1.25f, 
                               -1.25f, 
                                1.25f,
                                glm::ivec2{ x_resolution, y_resolution }, 
                                glm::vec3{ 0.0f, 1.0f,  2.50f },     // position
                                glm::vec3{ 0.0f, 10.0f,  0.0f },     // up
                                glm::vec3{ 0.0f, 1.0f,  -1.0f } };   // look at
    Scene scene{};
    
    scene.load();

    //scene.acceleration_structure_ = scene.BVH_SAH;
    //scene.buildAccelerationStructure();

    Buffer rendering_buffer{ x_resolution, y_resolution };
    glm::vec3 background_color{ 0.0f, 0.0f, 0.0f };
    if(argc == 4){
        RayTracer rt( camera,
                  scene,
                  background_color,
                  rendering_buffer,
                  std::stoi(std::string(argv[1])));

        rt.integrate(std::stoi(std::string(argv[2]))); // Renders the final image.

        // Save the rendered image to a .ppm file.
        std::string saveFile(argv[3]);
        rendering_buffer.save(saveFile + ".ppm");
        int waitReturn;

        std::string command("convert " + saveFile + ".ppm " + saveFile + ".png");
        waitReturn = system(command.c_str());

        command = "mkdir -p images_ppm";
        waitReturn = system(command.c_str());

        command = "mv " + saveFile + ".ppm" + " images_ppm";
        waitReturn = system(command.c_str());

        command = "mkdir -p images_png";
        waitReturn = system(command.c_str());

        command = "mv " + saveFile + ".png" + " images_png";
        waitReturn = system(command.c_str());
    }
    else{
    // Set up the renderer.
        RayTracer rt( camera,
                  scene,
                  background_color,
                  rendering_buffer );

        rt.integrate(); // Renders the final image.

        // Save the rendered image to a .ppm file.
        rendering_buffer.save( "output_image.ppm" );
    }
    return EXIT_SUCCESS;
}

