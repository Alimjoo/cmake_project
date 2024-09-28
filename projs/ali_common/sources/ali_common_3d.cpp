#include "ali_common_3d.h"


ALIPoint3D::ALIPoint3D() {}
ALIPoint3D::~ALIPoint3D() {}
ALIPoint3D ALIPoint3D::round() {
    return *this;
}
float ALIPoint3D::norm() {
    return float(sqrt(x * x + y * y + z * z));
}

ALIPoint3DF::ALIPoint3DF() {}
ALIPoint3DF::~ALIPoint3DF() {}
ALIPoint3D ALIPoint3DF::round() {
    return ALIPoint3D(this->x, this->y, this->z);
}
float ALIPoint3DF::norm() {
    return float(sqrt(x * x + y * y + z * z));
}








