// Copyright MakeShape. 2019, All rights reserved.

#include "aabb.hh"

namespace makeshape {
namespace spatial {

AABB::AABB(const Eigen::Vector3d &c, const Eigen::Vector3d &e) {
    center_ = c;
    extents_ = e;
}

AABB::AABB(const AABB &other) {
    center_ = other.const_center();
    extents_ = other.const_extents();
}

AABB& AABB::operator=(const AABB &other) {
    if (this != &other) {
        center_ = other.const_center();
        extents_ = other.const_extents();
    }
    return *this;
}

bool AABB::include(const Eigen::Vector3d &p) {
    //TODO(mayank): finish this.
    return false;
}

} // spatial 
} // makeshape
