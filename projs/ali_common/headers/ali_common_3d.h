#ifndef ALI_COMMON_3D_HEADER
#define ALI_COMMON_3D_HEADER
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


#pragma region Templates
class ALIPoint3D;
class ALIPoint3DF;

// int point 
class ALIPoint3D {
public:
    int x = 0, y = 0, z = 0;
public:
    ALIPoint3D();
    ~ALIPoint3D();
    template<typename T>
    ALIPoint3D(T xx, T yy, T zz) { x = int(std::round(xx)), y = int(std::round(yy)), z = int(std::round(zz)); }
    template<typename T>
    ALIPoint3D(const T& p) { x = int(std::round(p.x)), y = int(std::round(p.y)), z = int(std::round(p.z)); }
public:
    ALIPoint3D round();
    float norm();
    // template<typename T>
    // operator T() { return T(x, y); }
    template<typename T>
    ALIPoint3D operator+(const T& other)const { return ALIPoint3D(this->x + other.x, this->y + other.y, this->z + other.z); }
    template<typename T>
    ALIPoint3D operator-(const T& other)const { return ALIPoint3D(this->x - other.x, this->y - other.y, this->z - other.z); }
    ALIPoint3D operator-()const { return ALIPoint3D(-this->x, -this->y, -this->z); }
    template<typename T>
    ALIPoint3D operator*(const T& scalar)const { return ALIPoint3D(this->x * scalar, this->y * scalar, this->z * scalar); }
    template<typename T>
    ALIPoint3D operator/(const T& scalar)const { return ALIPoint3D(this->x * 1.0 / scalar, this->y * 1.0 / scalar, this->z * 1.0 / scalar); }
};
// float point 
class ALIPoint3DF {
public:
    int x = 0, y = 0, z = 0;
public:
    ALIPoint3DF();
    ~ALIPoint3DF();
    template<typename T>
    ALIPoint3DF(T xx, T yy, T zz) { x = xx, y = yy, z = zz; }
    template<typename T>
    ALIPoint3DF(const T& p) { x = p.x, y = p.y, z = p.z; }
public:
    ALIPoint3D round();
    float norm();
    // template<typename T>
    // operator T() { return T(x, y); }
    template<typename T>
    ALIPoint3DF operator+(const T& other)const { return ALIPoint3DF(this->x + other.x, this->y + other.y, this->z + other.z); }
    template<typename T>
    ALIPoint3DF operator-(const T& other)const { return ALIPoint3DF(this->x - other.x, this->y - other.y, this->z - other.z); }
    ALIPoint3DF operator-()const { return ALIPoint3DF(-this->x, -this->y, -this->z); }
    template<typename T>
    ALIPoint3DF operator*(const T& scalar)const { return ALIPoint3DF(this->x * scalar, this->y * scalar, this->z * scalar); }
    template<typename T>
    ALIPoint3DF operator/(const T& scalar)const { return ALIPoint3DF(this->x / scalar, this->y / scalar, this->z / scalar); }
};

#pragma endregion







#endif //ALI_COMMON_3D_HEADER

