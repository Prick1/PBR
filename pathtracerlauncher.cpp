#include <cstdlib>
#include <string>
#include <thread>
#include <chrono>

int main(int argc, char * argv[]){
    int x = 999;
    //std::string command("./swpathtracer " + std::string(argv[1]) + " " + std::string(argv[2]) + " " + std::string(argv[3]));
    //x = system(command.c_str());
    //std::this_thread::sleep_for(std::chrono::seconds(2));

    std::string command("convert " + std::string(argv[3]) + ".ppm " + std::string(argv[3]) + ".png");
    x = system(command.c_str());
        
    command = "mkdir --parents images_ppm; mv "+ std::string(argv[3]) +".ppm $_";
    x = system(command.c_str());

    command = "mkdir --parents images_png; mv "+ std::string(argv[3]) +".png $_";
    x = system(command.c_str());


}
