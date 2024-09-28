#include "test_header.h"
#include "headset_measure_3d.h"

namespace HSM_3D_TEST {
    void Simple_Test() {
        string path = "/home/pi/Desktop/HeadSet3DMeasure/1/2/";
        string ply_name = path + "1_3D_pointcloud.ply";
        string gray_name = path + "1_2D_gray.jpg";
        string depth_name = path + "1_2D_height.jpg";
        int res = begin_hsm_3d(ply_name, gray_name, depth_name);

        return;
    }
    void test_multi_median() {
        string path = "/home/pi/Desktop/HeadSet3DMeasure/1/2/";
        string ply_name = path + "2_3D_pointcloud.ply";
        string gray_name = path + "2_2D_gray.jpg";
        string depth_name = path + "2_2D_height.jpg";
        
        Mat image = cv::imread(depth_name, 0);
        int rows = image.rows;
        int cols = image.cols;
        uchar* ip = image.ptr();

        Mat fil_img(rows, cols, CV_8UC1);
        Mat mul_img(rows, cols, CV_8UC1);

        time_t s = clock();
        ali_mid_filter(ip, fil_img.ptr(), rows, cols, 11);
        cout << clock() - s << endl;;
        s = clock();
        // ali_mid_filter_mul(ip, mul_img.ptr(), rows, cols, 11);
        cout << clock() - s << endl;
        
        return;

    }


}












