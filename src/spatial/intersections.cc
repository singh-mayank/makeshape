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
    return (a1.min_pt().all() <= a2.max_pt().all() && 
            a1.max_pt().all() >= a2.min_pt().all());
}

bool intersects(const BSphere &b1, const BSphere &b2) {
    auto sq = [](const double x){
        return ((x) * (x));
    };
    return ((b2.center() - b1.center()).squaredNorm() <= 
            sq(b1.radius() + b2.radius()));
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
    if (u < 0.0 || u > 1.0) {
        return std::make_pair(false, Vec3{0, 0, 0});
    }
    const Vec3 q = s.cross(edge1);
    const double v = f * r.dir.dot(q);
    if (v < 0.0 || u + v > 1.0) {
        return std::make_pair(false, Vec3{0, 0, 0});
    }
    double t_intersect = f * edge1.dot(q);
    if (t_intersect > EPSILON) {
        Vec3 p = r.origin + (r.dir * t_intersect);
        return std::make_pair(true, p);
    } 
    return std::make_pair(false, Vec3{0, 0, 0});
}

std::pair<bool, Eigen::Vector3d> intersects(const Ray &r, const Plane &p) {
    using Vec3 = Eigen::Vector3d;
    return std::make_pair(false, Vec3{0, 0, 0});
}

// Ray/box
// http://psgraphics.blogspot.com/2016/02/new-simple-ray-box-test-from-andrew.html
//
//


} // spatial 
} // makeshape
