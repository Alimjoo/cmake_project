#include "ali_common.h"

// ALIPoint int
ALIPoint::ALIPoint() : cv::Point(0, 0) {}
ALIPoint::ALIPoint(int x, int y) : cv::Point(x, y) {}
ALIPoint::ALIPoint(float xx, float yy) {
    x = int(std::round(xx));
    y = int(std::round(yy));
}
ALIPoint::ALIPoint(double xx, double yy) {
    x = int(std::round(xx));
    y = int(std::round(yy));
}
ALIPoint::ALIPoint(const ALIPointF& pointF) {
    x = int(std::round(pointF.x));
    y = int(std::round(pointF.y));
}
ALIPoint ALIPoint::round() const {
    return ALIPoint(std::round(this->x), std::round(this->y));
}
ALIPoint::~ALIPoint() {}
ALIPoint ALIPoint::operator+(const ALIPoint& other) const {
    return ALIPoint(this->x + other.x, this->y + other.y);
}
ALIPoint ALIPoint::operator+(const ALIPointF& other) const {
    return ALIPoint(this->x + other.x, this->y + other.y);
}
ALIPoint ALIPoint::operator-(const ALIPoint& other) const {
    return ALIPoint(this->x - other.x, this->y - other.y);
}
ALIPoint ALIPoint::operator-(const ALIPointF& other) const {
    return ALIPoint(this->x - other.x, this->y - other.y);
}
ALIPoint ALIPoint::operator/(int scalar) const {
    return ALIPoint(this->x*1.0 / scalar, this->y *1.0 / scalar);
}
ALIPoint ALIPoint::operator/(float scalar) const {
    return ALIPoint(this->x / scalar, this->y / scalar);
}
ALIPoint ALIPoint::operator/(double scalar) const {
    return ALIPoint(this->x / scalar, this->y / scalar);
}
ALIPoint ALIPoint::operator*(int scalar) const {
    return ALIPoint(this->x * scalar, this->y * scalar);
}
ALIPoint ALIPoint::operator*(float scalar) const {
    return ALIPoint(this->x * scalar, this->y * scalar);
}
ALIPoint ALIPoint::operator*(double scalar) const {
    return ALIPoint(this->x * scalar, this->y * scalar);
}
bool ALIPoint::operator==(const ALIPoint& other){
    if (this->x == other.x && this->y == other.y) return true;
    return false;
}
bool ALIPoint::operator==(const ALIPointF& other){
    if (this->x == std::round(other.x) && this->y == std::round(other.y)) return true;
    return false;
}

// ALIPoint float
ALIPointF::ALIPointF() : cv::Point2f(0, 0) {}
ALIPointF::ALIPointF(int x, int y) : cv::Point2f(x, y) {}
ALIPointF::ALIPointF(float x, float y) : cv::Point2f(x, y) {}
ALIPointF::ALIPointF(double x, double y) : cv::Point2f(x, y) {}
ALIPointF::ALIPointF(const ALIPoint& point){
    x = point.x;
    y = point.y;
}

ALIPoint ALIPointF::round() const {
    return ALIPoint(std::round(this->x), std::round(this->y));
}
ALIPointF::~ALIPointF() {}
ALIPointF ALIPointF::operator+(const ALIPointF& other) const {
    return ALIPointF(this->x + other.x, this->y + other.y);
}
ALIPointF ALIPointF::operator+(const ALIPoint& other) const {
    return ALIPointF(this->x + other.x, this->y + other.y);
}
ALIPointF ALIPointF::operator-(const ALIPointF& other) const {
    return ALIPointF(this->x - other.x, this->y - other.y);
}
ALIPointF ALIPointF::operator-(const ALIPoint& other) const {
    return ALIPointF(this->x - other.x, this->y - other.y);
}
ALIPointF ALIPointF::operator/(int scalar) const {
    return ALIPointF(this->x / scalar, this->y / scalar);
}
ALIPointF ALIPointF::operator/(float scalar) const {
    return ALIPointF(this->x / scalar, this->y / scalar);
}
ALIPointF ALIPointF::operator/(double scalar) const {
    return ALIPointF(this->x / scalar, this->y / scalar);
}
ALIPointF ALIPointF::operator*(int scalar) const {
    return ALIPointF(this->x * scalar, this->y * scalar);
}
ALIPointF ALIPointF::operator*(float scalar) const {
    return ALIPointF(this->x * scalar, this->y * scalar);
}
ALIPointF ALIPointF::operator*(double scalar) const {
    return ALIPointF(this->x * scalar, this->y * scalar);
}
bool ALIPointF::operator==(const ALIPointF& other){
    if (std::round(this->x) == std::round(other.x) && std::round(this->y) == std::round(other.y)) return true;
    return false;
}
bool ALIPointF::operator==(const ALIPoint& other){
    if (std::round(this->x) == other.x && std::round(this->y) == other.y) return true;
    return false;
}




ALILine::ALILine() {}
ALILine::ALILine(ALIPoint p0, ALIPoint p1) :p0(p0), p1(p1) {}
ALILine::~ALILine() {}
ALILine::ALILine(const ALILineF& linef){
    this->p0 = linef.p0.round();
    this->p1 = linef.p1.round();
}
float ALILine::length() const{
    return sqrt(pow(p1.x - p0.x, 2) + pow(p1.y - p0.y, 2));
}
ALIPointF ALILine::get_normal_vec() const{
    float len = this->length();
    return ALIPointF((p1.x - p0.x) / len, (p1.y - p0.y) / len);
}

ALILineF::ALILineF() {}
ALILineF::ALILineF(ALIPointF p0, ALIPointF p1) :p0(p0), p1(p1) {}
ALILineF::~ALILineF() {}
ALILineF::ALILineF(const ALILine& line){
    this->p0 = line.p0;
    this->p1 = line.p1;
}
float ALILineF::length() const{
    return sqrt(pow(p1.x - p0.x, 2) + pow(p1.y - p0.y, 2));
}
ALIPointF ALILineF::get_normal_vec() const {
    float len = this->length();
    return ALIPointF((p1.x - p0.x) / len, (p1.y - p0.y) / len);
}





