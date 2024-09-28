#ifndef ALI_COMMON_HEADER
#define ALI_COMMON_HEADER
#define _USE_MATH_DEFINES
#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#ifdef _WIN32
#include <opencv2/opencv.hpp>
#else
#include <opencv4/opencv2/opencv.hpp>
#endif

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
class ALILine;
class ALILineF;
// int point 
class ALIPoint {
public:
    int x = 0, y = 0;
public:
    ALIPoint();
    ~ALIPoint();
    template<typename T>
    ALIPoint(T xx, T yy) { x = int(std::round(xx)), y = int(std::round(yy)); }
    template<typename T>
    ALIPoint(const T& p) { x = int(std::round(p.x)), y = int(std::round(p.y)); }
public:
    ALIPoint round();
    float norm();
    // template<typename T>
    // operator T() { return T(x, y); }
    template<typename T>
    ALIPoint operator+(const T& other)const { return ALIPoint((this->x + other.x), (this->y + other.y)); }
    template<typename T>
    ALIPoint operator-(const T& other)const { return ALIPoint((this->x - other.x), (this->y - other.y)); }
    template<typename T>
    ALIPoint operator*(const T& scalar)const { return ALIPoint((this->x * scalar), (this->y * scalar)); }
    template<typename T>
    ALIPoint operator/(const T& scalar)const { return ALIPoint((this->x * 1.0 / scalar), (this->y * 1.0 / scalar)); }
    template<typename T>
    bool operator<(const T& other)const { if (x < other.x && y < other.y) return true; else return false; }
    template<typename T>
    bool operator<=(const T& other)const { if (x <= other.x && y <= other.y) return true; else return false; }
    template<typename T>
    bool operator>(const T& other)const { if (x > other.x && y > other.y) return true; else return false; }
    template<typename T>
    bool operator>=(const T& other)const { if (x >= other.x && y >= other.y) return true; else return false; }
    template<typename T>
    bool operator==(const T& p)const { if (x == int(std::round(p.x)) && y == int(std::round(p.y))) return true; else return false; }
    operator cv::Point() { return cv::Point(x, y); };
};
// float point
class ALIPointF {
public:
    float x = 0, y = 0;
public:
    ALIPointF();
    ~ALIPointF();
    template<typename T>
    ALIPointF(T xx, T yy) { x = float(xx), y = float(yy); }
    template<typename T>
    ALIPointF(const T& p) { x = float(p.x), y = float(p.y); }
public:
    ALIPoint round();
    float norm();
    // template<typename T>
    // operator T() { return T(x, y); }
    template<typename T>
    ALIPointF operator+(const T& other)const { return ALIPointF(float(this->x + other.x), float(this->y + other.y)); }
    template<typename T>
    ALIPointF operator-(const T& other)const { return ALIPointF(float(this->x - other.x), float(this->y - other.y)); }
    template<typename T>
    ALIPointF operator*(const T& scalar)const { return ALIPointF(float(this->x * scalar), float(this->y * scalar)); }
    template<typename T>
    ALIPointF operator/(const T& scalar)const { return ALIPointF(float(this->x / scalar), float(this->y / scalar)); }
    template<typename T>
    bool operator<(const T& other)const { if (x < other.x && y < other.y) return true; else return false; }
    template<typename T>
    bool operator<=(const T& other)const { if (x <= other.x && y <= other.y) return true; else return false; }
    template<typename T>
    bool operator>(const T& other)const { if (x > other.x && y > other.y) return true; else return false; }
    template<typename T>
    bool operator>=(const T& other)const { if (x >= other.x && y >= other.y) return true; else return false; }
    operator cv::Point2f() { return cv::Point2f(x, y); };
};
// int line
class ALILine {
public:
    ALIPoint p0, p1;
public:
    float length();
    ALIPointF get_normal_vec();
public:
    ALILine();
    ~ALILine();
    // template<typename T>
    // operator T() { return T(p0, p1); }
    template <typename T>
    ALILine(const T& pp0, const T& pp1) { p0 = ALIPoint(pp0), p1 = ALIPoint(pp1); }
    template <typename T>
    ALILine(T x0, T y0, T x1, T y1) { p0 = ALIPoint(x0, y0), p1 = ALIPoint(x1, y1); }
    // template <typename T>
    // ALILine(const T& line) { p0 = ALIPoint(line.p0), p1 = ALIPoint(line.p1); };
};
// float line
class ALILineF {
public:
    ALIPointF p0, p1;
public:
    float length();
    ALIPointF get_normal_vec();
public:
    ALILineF();
    ~ALILineF();
    // template<typename T>
    // operator T() { return T(p0, p1); }
    template <typename T>
    ALILineF(const T& pp0, const T& pp1) { p0 = ALIPointF(pp0), p1 = ALIPointF(pp1); }
    template <typename T>
    ALILineF(T x0, T y0, T x1, T y1) { p0 = ALIPointF(x0, y0), p1 = ALIPointF(x1, y1); }
    // template <typename T>
    // ALILineF(const T& line) { p0 = ALIPointF(line.p0), p1 = ALIPointF(line.p1); };
};

class ALIRange {
public:
    int min = 0, max = 0;
    ALIRange();
    ~ALIRange();
    template <typename T>
    ALIRange(T min_val, T max_val) { min = int(std::round(min_val)), max = int(std::round(max_val)); }
    int len();
};

class ALIRangeF {
public:
    float min = 0, max = 0;
    ALIRangeF();
    ~ALIRangeF();
    template <typename T>
    ALIRangeF(T min_val, T max_val) { min = min_val, max = max_val; }
    float len();
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

// for the border, I expand it to 0
template<typename T, typename S>
void ali_mid_filter(const T* data, S* res, const int rows, const int cols, const int win_size) {
    if (win_size % 2 == 0) {
        cout << "win_size must be odd" << endl;
        return;
    }
    int half_win = win_size / 2;
    int sqwin = win_size * win_size;;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            T sum = 0;
            for (int n = -half_win; n <= half_win; n++) {
                for (int m = -half_win; m <= half_win; m++) {
                    int x = n + i, y = m + j;
                    T temp;
                    if (
                        x < 0 || x >= rows ||
                        y < 0 || y >= cols
                        ) temp = 0;
                    else temp = *(data + x * cols + y);
                    sum += temp;
                }
            }
            *(res + i * cols + j) = sum * 1.0 / (sqwin);
        }
    }
}

// do diff on image or array, dir=1 is column wise, dir=2 is row wise
template <typename T>
void ali_diff(T* data, T* res, int rows, int cols, int dir) {
    if (dir == 1) {
        for (int i = 0; i < rows; i++) {
            int index = i * cols;
            for (int j = 0; j < cols - 1; j++) {
                if (j == 0) res[index + j] = data[index + j];
                else res[index + j] = data[index + j + 1] - data[index + j];
            }
        }
    }
    else if (dir == 2) {
        for (int j = 0; j < cols; j++) {
            for (int i = 0; i < rows - 1; i++) {
                int index = i * cols;
                int index_1 = (i + 1) * cols;
                if (i == 0) res[index + j] = data[index + j];
                else res[index + j] = data[index_1 + j] - data[index + j];
            }
        }
    }
    else {
        cout << "dir must be 1 or 2" << endl;
        return;
    }
}






#pragma endregion














#endif



