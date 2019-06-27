// Copyright MakeShape. 2019, All rights reserved.

#include "intersections.hh"

#include "aabb.hh"
#include "bsphere.hh"
#include "ray.hh"
#include "triangle.hh"
#include "plane.hh"

namespace makeshape {
namespace spatial {

bool intersects(const AABB &a1, const AABB &a2) {
    return true;
}

bool intersects(const BSphere &b1, const AABB &b2) {
    return false;
}

// test between solid box and solid sphere | borrowed from: 
// https://github.com/erich666/GraphicsGems/blob/master/gems/BoxSphere.c
bool intersects(const AABB &a, const BSphere &b) {
    auto sqr = [](const double x){ return (x*x); };
    constexpr size_t DIM = 3;
    const Eigen::Vector3d min_pt = a.min_pt();
    const Eigen::Vector3d max_pt = a.max_pt();
    const Eigen::Vector3d &c = b.const_center();
    double dist = 0.0;
    for (size_t i = 0; i < DIM; ++i) {
        if (c(i) < min_pt(i)) {
            dist += sqr(c(i) - min_pt(i));
        } else if (c(i) > max_pt(i)) {
            dist += sqr(c(i) - max_pt(i));
        } else {
            // do nothing
        }
    }
    return (dist <= b.radius2());
}


} // spatial 
} // makeshape
