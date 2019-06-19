// Copyright MakeShape. 2019, All rights reserved.

#include "bsphere.hh"

namespace makeshape {
namespace spatial {

BSphere::BSphere(const Eigen::Vector3d &c, const double r) {
    center_ = c;
    radius_ = r;
}

BSphere::BSphere(const BSphere &other) {
    center_ = other.const_center();
    radius_ = other.const_radius();
}

BSphere& BSphere::operator=(const BSphere &other) {
    if (this != &other) {
        center_ = other.const_center();
        radius_ = other.const_radius();
    }
    return *this;
}

bool BSphere::include(const Eigen::Vector3d &p) {
    //TODO(mayank): finish this.
    return false;
}

} // spatial 
} // makeshape
