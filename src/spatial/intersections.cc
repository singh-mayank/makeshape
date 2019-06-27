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
    using Vec3 = Eigen::Vector3d;
    const Vec3 min_a1 = a1.min_pt();
    const Vec3 max_a1 = a1.max_pt();
    const Vec3 min_a2 = a2.min_pt();
    const Vec3 max_a2 = a2.max_pt();
    return ((min_a1(0) <= max_a2(0) && max_a1(0) >= min_a2(0)) && 
            (min_a1(1) <= max_a2(1) && max_a1(1) >= min_a2(1)) && 
            (min_a1(2) <= max_a2(2) && max_a1(2) >= min_a2(2)));
}

bool intersects(const BSphere &b1, const BSphere &b2) {
    double distsq = (b2.center() - b1.center()).squaredNorm();
    double radSum = b1.radius() + b2.radius();
    return (distsq <= (radSum * radSum));
}

// test between solid box and solid sphere | borrowed from: 
// https://github.com/erich666/GraphicsGems/blob/master/gems/BoxSphere.c
bool intersects(const AABB &a, const BSphere &b) {
    auto sqr = [](const double x){ return (x*x); };
    constexpr size_t DIM = 3;
    const Eigen::Vector3d min_pt = a.min_pt();
    const Eigen::Vector3d max_pt = a.max_pt();
    const Eigen::Vector3d &c = b.center();
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

// Möller–Trumbore intersection algorithm
// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
std::pair<bool, Eigen::Vector3d> intersects(const Ray &r, const Triangle &t) {
    using Vec3 = Eigen::Vector3d;
    constexpr double EPSILON = 1e-9;
    const Vec3 edge1 = (t.v1 - t.v0);
    const Vec3 edge2 = (t.v2 - t.v0);
    const Vec3 h = r.dir.cross(edge2);
    const double a = edge1.dot(h);
    if (a > -EPSILON && a > EPSILON) {
        return std::make_pair(false, Vec3{0, 0, 0});
    }
    const double f = 1.0/a;
    const Vec3 s = r.origin - t.v0;
    const double u = f * s.dot(h);



    return std::make_pair(false, Vec3{0, 0, 0});
}

std::pair<bool, Eigen::Vector3d> intersects(const Ray &r, const Plane &p) {
    using Vec3 = Eigen::Vector3d;
    return std::make_pair(false, Vec3{0, 0, 0});
}

} // spatial 
} // makeshape
