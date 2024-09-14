#include "demura.h"

#define RESIZE_RECT_SIZE 200

int begin_demura(uchar* img, int rows, int cols, demura_param para) {
    time_t s = clock();
    Mat shemm(rows, cols, CV_8UC1, img);


    double angle = 340;
    float scale = 0.7;
    cv::Point2f center_rotate(shemm.cols / 2.0, shemm.rows / 2.0);
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center_rotate, angle, scale);
    cv::Mat rotatedImage;
    cv::warpAffine(shemm, rotatedImage, rotationMatrix, shemm.size());
    shemm = rotatedImage;
    para.placed_angle = 360 - angle;


    Mat bin(rows, cols, CV_8UC1);
    ali_binarize(shemm.ptr(), rows * cols, bin.ptr(), 40, (uchar)255, false);
    int erode_size = 2;
    Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(erode_size, erode_size));
    Mat eroded, dilated;
    cv::erode(bin, eroded, element);
    cv::dilate(eroded, dilated, element);

    ALIPoint UP, DOWN;
    find_UP_DOWN_corner_from_bin_image(dilated.ptr(), rows, cols, UP, DOWN);

    shemm.at<uchar>(UP.y, UP.x) = 255;
    shemm.at<uchar>(DOWN.y, DOWN.x) = 255;

    ALIPoint UL, DR;
    if (UP.x > DOWN.x){
        UL = DOWN;
        DR = UP;
    }else{
        UL = UP;
        DR = DOWN;
    }
    ALIPoint big_UL, big_DR, sma_UL, sma_DR;
    ali_resize_rectangle(UL, DR, big_UL, big_DR, rows, cols, RESIZE_RECT_SIZE, true);
    ali_resize_rectangle(UL, DR, sma_UL, sma_DR, rows, cols, RESIZE_RECT_SIZE, false);
    // ali_draw_rectangle(shemm, UL, DR, 255);
    ali_draw_rectangle(shemm, big_UL, big_DR, 255);
    ali_draw_rectangle(shemm, sma_UL, sma_DR, 255);

    vector<cv::Point> white_dots;
    ali_find_all_white_dots_between_two_rect(dilated.ptr(), rows, cols, big_UL, big_DR,sma_UL, sma_DR, white_dots, 3);
    int dsfdfsdfs =white_dots.size();

    Mat test_white = Mat::zeros(rows, cols, CV_8UC1);
    ali_draw_dots(test_white.ptr(), rows, cols, white_dots, 255);

    cv::RotatedRect min_rect_area = cv::minAreaRect(white_dots);
    vector<cv::Point2f> min_rect_cv(4);
    min_rect_area.points(min_rect_cv.data());
    ali_draw_countor(shemm, min_rect_cv, 255);
    vector<ALIPointF> min_rect(4);
    for (int i = 0; i < 4; i++){
        min_rect[i] = ALIPointF(min_rect_cv[i]);
    }

    bool base_res = get_demura_base_based_on_angle(min_rect, ali_degree2radias(para.placed_angle));
    if (!base_res){ 
        cout << "Some Problem Occured\n";
        return -1;
    }

    ali_draw_line(shemm, min_rect[0], min_rect[1], 255);
    ali_draw_line(shemm, min_rect[1], min_rect[2], 255);
    cv::circle(shemm, min_rect[0].round(), 20, 255, -1);
    cv::circle(shemm, min_rect[2].round(), 20, 255, -1);

    ALIPointF center = (min_rect[0] + min_rect[2]) / 2.0;
    cv::circle(shemm, center.round(), 20, 255, -1);

    
    ALILineF line_x(min_rect[1], min_rect[2]), line_y(min_rect[1], min_rect[0]);
    ALIPointF vec_x = line_x.get_normal_vec(), vec_y = line_y.get_normal_vec();


    cout << __FUNCTION__ << " took: " << (clock() - s) * 1.0 / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}







