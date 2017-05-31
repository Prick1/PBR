#include <stdlib.h>

int main(){
    system("make");
    system("./swpathtracer");
    system("eog output_image.ppm&");
}
