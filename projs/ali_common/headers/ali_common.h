#ifndef ALI_COMMON_HEADER
#define ALI_COMMON_HEADER
#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <opencv4/opencv2/opencv.hpp>

#pragma region Usings
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::round;
using cv::Mat;

#pragma endregion


#pragma region Function Declaration

#pragma endregion


#pragma region Templates
class ALIPointF;
class ALIPoint;
class ALIPoint : public cv::Point {
public:
    ALIPoint();
    ~ALIPoint();
    ALIPoint(int x, int y);
    ALIPoint(float xx, float yy);
    ALIPoint(double xx, double yy);
    ALIPoint(const ALIPointF& pointF);
    ALIPoint round() const;
    ALIPoint operator+(const ALIPoint& other) const;
    ALIPoint operator+(const ALIPointF& other) const;
    ALIPoint operator-(const ALIPoint& other) const;
    ALIPoint operator-(const ALIPointF& other) const;
    ALIPoint operator/(int scalar) const;
    ALIPoint operator/(float scalar) const;
    ALIPoint operator/(double scalar) const;
    ALIPoint operator*(int scalar) const;
    ALIPoint operator*(float scalar) const;
    ALIPoint operator*(double scalar) const;
    bool operator==(const ALIPoint& other);
    bool operator==(const ALIPointF& other);
};
class ALIPointF : public cv::Point2f {
public:
    ALIPointF();
    ~ALIPointF();
    ALIPointF(int x, int y);
    ALIPointF(float x, float y);
    ALIPointF(double xx, double yy);   
    ALIPointF(const ALIPoint& point);
    ALIPoint round() const;
    ALIPointF operator+(const ALIPointF& other) const;
    ALIPointF operator+(const ALIPoint& other) const;
    ALIPointF operator-(const ALIPointF& other) const;
    ALIPointF operator-(const ALIPoint& other) const;
    ALIPointF operator/(int scalar) const;
    ALIPointF operator/(float scalar) const;
    ALIPointF operator/(double scalar) const;
    ALIPointF operator*(int scalar) const;
    ALIPointF operator*(float scalar) const;
    ALIPointF operator*(double scalar) const;
    bool operator==(const ALIPointF& other);
    bool operator==(const ALIPoint& other);
};
class ALILine;
class ALILineF;
class ALILine {
public:
    ALIPoint p0, p1;
public:
    float length() const;
    ALIPointF get_normal_vec() const;
public:
    ALILine();
    ALILine(ALIPoint p0, ALIPoint p1);
    ALILine(const ALILineF& linef);
    ~ALILine();
};
class ALILineF {
public:
    ALIPointF p0, p1;
public:
    float length() const;
    ALIPointF get_normal_vec() const;
public:
    ALILineF();
    ALILineF(ALIPointF p0, ALIPointF p1);
    ALILineF(const ALILine& linef);
    ~ALILineF();
};

// calculate length of a line
template<typename T>
float ali_get_line_length(const T& line) {
    return sqrt(pow(line.p1.x - line.p0.x, 2) + pow(line.p1.y - line.p0.y, 2));
}
template<typename T>
float ali_get_line_length(const T& p0, const T& p1) {
    return sqrt(pow(p1.x - p0.x, 2) + pow(p1.y - p0.y, 2));
}
// Template function for dot product of 2D vectors
template <typename T>
float ali_dot_product(const T& a, const T& b) {
    return a.x * b.x + a.y * b.y;
}
// Template function for cross product of 2D vectors (returns float)
template <typename T>
float ali_cross_product(const T& a, const T& b) {
    return a.x * b.y - a.y * b.x;
}
// Function to compute the magnitude of a vector
template <typename T>
float ali_get_magnitude(const T& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}
// radis to degree, degree to radia
template<typename T>
float ali_degree2radias(T degree) {
    return degree / 180.0 * M_PI;
}
template<typename T>
float ali_radias2degree(T radias) {
    return radias / M_PI * 180;
}
// get normal vector of vector or two point
template<typename T, typename S>
void ali_get_normal_vector(const T& vec, S& res) {
    float len = ali_get_line_length(vec);
    res = S(vec.x / len, vec.y / len);
}
template<typename T, typename S>
void ali_get_normal_vector(const T& p0, const T& p1, S& res) {
    float len = ali_get_line_length(p0, p1);
    res = S((p1.x - p0.x) / len, (p1.y - p0.y) / len);
}

// get angle of a vector or line 
template<typename T>
float ali_get_angle(const T& vec) {
    return std::atan2(vec.x, vec.y);
}
template<typename T>
float ali_get_angle(const T& p0, const T& p1) {
    return std::atan2(p1.x - p0.x, p1.y - p0.y);
}
// get angle of two vector
template <typename T>
float ali_get_angle_of_two_vec(const T& vec1, const T& vec2) {
    float dot = ali_dot_product(vec1, vec2);
    float magA = ali_get_magnitude(vec1);
    float magB = ali_get_magnitude(vec2);
    float cosTheta = dot / (magA * magB);
    // Clamp the value to the range [-1, 1] to avoid NaN due to floating point precision issues
    if (cosTheta > 1.0) cosTheta = 1.0;
    if (cosTheta < -1.0) cosTheta = -1.0;
    return std::acos(cosTheta);
}
// judge is two vector same direction
template<typename T>
bool ali_is_two_vec_same_dir(const T& vec1, const T& vec2) {
    float dot = ali_dot_product(vec1, vec2);
    return dot > 0 ? true : false;
}

// binarize any array or image based on a threash val
// inverse means if val < threash, it equals to non-zero
template<typename T>
void ali_binarize(T* pointer, int size, T* res, float thresh, T non_zero, bool inverse) {
    for (int i = 0; i < size; i++) {
        *(res + i) = 0;
        auto cur = *(pointer + i);
        if (cur >= thresh && !inverse) {
            *(res + i) = non_zero;
        }
        else if (cur <= thresh && inverse) {
            *(res + i) = non_zero;
        }
    }
}
// find the UP corner, and Down corner from binarize image
template<typename T, typename S>
void find_UP_DOWN_corner_from_bin_image(T* img, int rows, int cols, S& UP, S& DOWN) {
    UP = { 0, 0 };
    DOWN = { cols - 1, rows - 1 };
    bool up_find = false, down_find = false;
    int index_up, index_down;
    for (int i = 0; i < rows; i++) { // i is y
        index_up = i * cols;
        index_down = (rows - i - 1) * cols;
        for (int j = 0; j < cols; j++) { // j is x
            auto& cur_up = *(img + index_up + j);
            auto& cur_down = *(img + index_down + (cols - j - 1));
            if (cur_up > 0 && !up_find) {
                UP.y = i;
                up_find = true;
            }
            if (cur_down > 0 && !down_find) {
                DOWN.y = (rows - i - 1);
                down_find = true;
            }
        }
        if (up_find && down_find)
            break;
    }
    up_find = false, down_find = false;
    int index_left, index_right;
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            index_left = i * cols + j;
            index_right = (rows - i - 1) * cols + (cols - j - 1);
            auto& cur_left = *(img + index_left);
            auto& cur_right = *(img + index_right);
            if (cur_left > 0 && !up_find) {
                UP.x = j;
                up_find = true;
            }
            if (cur_right > 0 && !down_find) {
                DOWN.x = (cols - j - 1);
                down_find = true;
            }
        }
        if (up_find && down_find)
            break;
    }
}
// resize rectangle
// rows, cols is the size of the image
template<typename T, typename S>
void ali_resize_rectangle(const T& UL, const T& DR, T& res_UL, T& res_DR, int rows, int cols, S resize_size, bool make_bigger) {
    if (make_bigger) {
        res_UL.x = (UL.x > resize_size) ? UL.x - resize_size : 0;
        res_UL.y = (UL.y > resize_size) ? UL.y - resize_size : 0;
        res_DR.x = ((cols - DR.x) > resize_size) ? DR.x + resize_size : cols - 1;
        res_DR.y = ((rows - DR.y) > resize_size) ? DR.y + resize_size : rows - 1;
    }
    else {
        res_UL.x = UL.x + resize_size;
        res_UL.y = UL.y + resize_size;
        res_DR.x = DR.x - resize_size;
        res_DR.y = DR.y - resize_size;
    }
}
// draw rectangle on a opencv Mat image
template<typename T>
void ali_draw_rectangle(Mat& img, const T& UL, const T& DR, int color) {
    vector<T> corners;
    corners.push_back(UL);
    corners.push_back({ UL.x, DR.y });
    corners.push_back(DR);
    corners.push_back({ DR.x, UL.y });
    for (int i = 0; i < 4; i++) {
        cv::Point a = cv::Point(round(corners[i].x), round(corners[i].y));
        cv::Point b = cv::Point(round(corners[(i + 1) % 4].x), round(corners[(i + 1) % 4].y));
        cv::line(img, a, b, color);
    }
}
// draw line
template<typename T>
void ali_draw_line(Mat& img, const T& p0, const T& p1, int color) {
    cv::Point a = cv::Point(round(p0.x), round(p0.y));
    cv::Point b = cv::Point(round(p1.x), round(p1.y));
    cv::line(img, a, b, color);
}
// judge if a dot inside a rectangle or not
template<typename T, typename S>
bool ali_is_dot_inside_rect(T dot, const S& UL, const S& DR) {
    if (
        dot.x >= UL.x && dot.y >= UL.y
        && dot.x <= DR.x && dot.y <= DR.y
        )
        return true;
    return false;
}
// judge if a dot between two rectangle
template<typename T, typename S>
bool ali_is_dot_between_two_rect(T dot, const S& big_UL, const S& big_DR, const S& sma_UL, const S& sma_DR) {
    if (
        ali_is_dot_inside_rect(dot, big_UL, big_DR)
        && !ali_is_dot_inside_rect(dot, sma_UL, sma_DR)
        )
        return true;
    return false;
}
// find the all white pixels position between two rectabgle from a image
template<typename T, typename S, typename H>
void ali_find_all_white_dots_between_two_rect(T* img, int rows, int cols,
    S& big_UL, const S& big_DR, const S& sma_UL, const S& sma_DR, vector<H>& white_dots, int step = 1) {
    int index;
    for (int i = big_UL.y; i < big_DR.y; i += step) {
        index = i * cols;
        for (int j = big_UL.x; j < big_DR.x; j += step) {
            if (
                j >= sma_UL.x && i >= sma_UL.y
                && j <= sma_DR.x && i <= sma_DR.y
                ) continue;
            auto& cur = *(img + index + j);
            if (cur > 0)
                white_dots.push_back(H(j, i));
        }
    }
}
// draw dot on the image
template<typename T>
void ali_draw_dot(uchar* img, int rows, int cols, const T& dot, int color) {
    *(img + dot.y * cols + dot.x) = 255;
}
// draw dots on the image
template<typename T>
void ali_draw_dots(uchar* img, int rows, int cols, vector<T>& dots, int color) {
    for (auto& dot : dots) {
        ali_draw_dot(img, rows, cols, dot, color);
    }
}
// draw countor , connect the countor or vector<points> using line
template<typename T>
void ali_draw_countor(Mat& img, vector<T>& points, int color) {
    for (int i = 0; i < points.size(); i++) {
        cv::Point a = cv::Point(round(points[i].x), round(points[i].y));
        cv::Point b = cv::Point(round(points[(i + 1) % 4].x), round(points[(i + 1) % 4].y));
        cv::line(img, a, b, color);
    }
}






#pragma endregion














#endif



