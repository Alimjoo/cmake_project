#include "demura.h"


int main(){
#ifdef _WIN32
    string path = "C:/Users/PI/Desktop/project_cmake/assets/";
#else
    string path = "/home/pi/Desktop/CMake/project_cmake/assets/"
#endif
     Mat image = cv::imread(path + "b64.png", 0);
    int rows = image.rows, cols = image.cols;
    demura_param para;
    para.height = 2532;
    para.width = 1170;
    para.placed_angle = 0;
    para.color = CLR_BLUE;
    para.mode = Mode_Diamond;
    para.store_path = "/home/pi/Desktop/CMake/project_cmake/assets/";

    begin_demura(image.ptr(), rows, cols, para);

    return 0;
}
