#include "ali_common.h"

// ALIPoint int
ALIPoint::ALIPoint() { x = 0, y = 0; }
ALIPoint::~ALIPoint() {}
ALIPoint ALIPoint::round() {
    return *this;
}
float ALIPoint::norm() {
    return float(sqrt(x * x + y * y));
}

// ALIPoint float
ALIPointF::ALIPointF() { x = 0; y = 0; }
ALIPointF::~ALIPointF() {}
ALIPoint ALIPointF::round() {
    return ALIPoint(int(std::round(this->x)), int(std::round(this->y)));
}
float ALIPointF::norm() {
    return float(sqrt(x * x + y * y));
}




// int line
ALILine::ALILine() {}
ALILine::~ALILine() {}
float ALILine::length() {
    return sqrt(pow(p1.x - p0.x, 2) + pow(p1.y - p0.y, 2));
}
ALIPointF ALILine::get_normal_vec() {
    float len = this->length();
    return ALIPointF((p1.x - p0.x) / len, (p1.y - p0.y) / len);
}
// float line
ALILineF::ALILineF() {}
ALILineF::~ALILineF() {}
float ALILineF::length() {
    return sqrt(pow(p1.x - p0.x, 2) + pow(p1.y - p0.y, 2));
}
ALIPointF ALILineF::get_normal_vec() {
    float len = this->length();
    return ALIPointF((p1.x - p0.x) / len, (p1.y - p0.y) / len);
}


// range
ALIRange::ALIRange(){}
ALIRange::~ALIRange(){}

ALIRangeF::ALIRangeF(){}
ALIRangeF::~ALIRangeF(){}





