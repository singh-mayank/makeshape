// Copyright MakeShape. 2019, All rights reserved.

#include "aabb.hh"

namespace makeshape {
namespace spatial {

AABB::AABB() {
    center = Eigen::Vector3d{0, 0, 0};
    extents = Eigen::Vector3d{1, 1, 1};
}
AABB::AABB(const Eigen::Vector3d &c, const Eigen::Vector3d &e) {
    center = c;
    extents = e;
}

AABB::AABB(const AABB &other) {
    if (this != &other) {
        center = other.center;
        extents = other.extents;
    }
    return *this;
}

AABB::AABB(const AABB &&other) {
    center(std::move(other.center));
    extents(std::move(other.extents));
}

bool AABB::include(const Eigen::Vector3d &p) {
    //TODO(mayank): finish this.
    return false;
}

} // spatial 
} // makeshape
