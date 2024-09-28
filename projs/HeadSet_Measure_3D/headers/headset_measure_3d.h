#ifndef HDM3D_HEADER
#define HDM3D_HEADER
#include <thread>
#include <chrono>
#include "ali_common.h"
#include "ali_common_3d.h"
#include "matplot/matplot.h"
#include "tinyply.h"


using namespace matplot;
using namespace tinyply;


struct PLYData{
    std::vector<ALIPoint3DF> vertices;
    ALIRangeF x_range;
    ALIRangeF y_range;
    ALIRangeF z_range;
};


int begin_hsm_3d(string ply_name, string gray_name, string depth_name);

bool read_ply_file(const std::string& file_path, PLYData& data);

int test_analysis_using_pcl(string ply_name, string gray_name, string depth_name);
int test_analyze_depth_image(string ply_name, string gray_name, string depth_name);





#endif //HDM3D_HEADER

