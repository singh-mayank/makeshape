// Copyright MakeShape. 2019, All rights reserved.

#include "aabb.hh"

namespace makeshape {
namespace spatial {

AABB::AABB(const Eigen::Vector3d &c, const Eigen::Vector3d &e) {
    center_ = c;
    extents_ = e;
}

AABB::AABB(const AABB &other) {
    center_ = other.center();
    extents_ = other.extents();
}

AABB& AABB::operator=(const AABB &other) {
    if (this != &other) {
        center_ = other.center();
        extents_ = other.extents();
    }
    return *this;
}

bool AABB::inside(const Eigen::Vector3d &p) {
    using Vec3 = Eigen::Vector3d;
    const Vec3 minpt = min_pt();
    const Vec3 maxpt = max_pt();
    return ((p(0) >= minpt(0) && p(0) <= maxpt(0)) && 
            (p(1) >= minpt(1) && p(1) <= maxpt(1)) && 
            (p(2) >= minpt(2) && p(2) <= maxpt(2)));
}



} // spatial 
} // makeshape
