// Copyright MakeShape. 2019, All rights reserved.

#include "intersections.hh"

#include "aabb.hh"
#include "bsphere.hh"
#include "ray.hh"
#include "triangle.hh"
#include "plane.hh"

namespace makeshape {
namespace spatial {

namespace {
using Vec3 = Eigen::Vector3d;
constexpr double EPSILON = 1e-9;
constexpr size_t DIM = 3;
const std::pair<bool, Vec3> FAILURE_CASE = std::make_pair(false, Vec3{0, 0, 0});
double pow_sq(const double x){ return (x*x); };


// This addresses some numerical robustness issues
// Borrowed from : 
// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
std::tuple<bool, double, double> quadratic_roots(const double a, 
                                                 const double b, 
                                                 const double c) {
    double d = (b*b - 4*a*c);
    if (d < 0) {
        return std::make_tuple(false, 0, 0);
    } else if (d == 0.0) {
        double x = (-0.5 * b)/a;
        return std::make_tuple(true, x, x);
    } else {
        float x = sqrt(d);
        float q = (b > 0) ? -0.5 * (b + x) : -0.5 * (b - x);
        double x0 = q/a;
        double x1 = c/q;
        if (x0 > x1) {
            std::swap(x0, x1);
        }
        return std::make_tuple(true, x0, x1);
    }
}

}

// Returns true if the oriented boxes overlap
bool intersects(const AABB &a1, const AABB &a2) {
    return (a1.min_pt().all() <= a2.max_pt().all() && 
            a1.max_pt().all() >= a2.min_pt().all());
}

// Returns true if spheres overlap
bool intersects(const BSphere &b1, const BSphere &b2) {
    return ((b2.center() - b1.center()).squaredNorm() <= 
            pow_sq(b1.radius() + b2.radius()));
}

// Returns true if box, and sphere overlaps
// Borrowed from: 
// https://github.com/erich666/GraphicsGems/blob/master/gems/BoxSphere.c
bool intersects(const AABB &a, const BSphere &b) {
    const Vec3 min_pt = a.min_pt();
    const Vec3 max_pt = a.max_pt();
    const Vec3 &c = b.center();
    double dist = 0.0;
    for (size_t i = 0; i < DIM; ++i) {
        if (c(i) < min_pt(i)) {
            dist += pow_sq(c(i) - min_pt(i));
        } else if (c(i) > max_pt(i)) {
            dist += pow_sq(c(i) - max_pt(i));
        } else {
            // do nothing
        }
    }
    return (dist <= b.radius2());
}

// Returns true if Ray, and Triangle intersects
// Möller/Trumbore intersection algorithm
// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
std::pair<bool, Eigen::Vector3d> intersects(const Ray &r, const Triangle &t) {
    const Vec3 edge1 = (t.v1 - t.v0);
    const Vec3 edge2 = (t.v2 - t.v0);
    const Vec3 h = r.dir.cross(edge2);
    const double a = edge1.dot(h);
    if (a > -EPSILON && a > EPSILON) {
        return FAILURE_CASE;
    }
    const double f = 1.0/a;
    const Vec3 s = r.origin - t.v0;
    const double u = f * s.dot(h);
    if (u < 0.0 || u > 1.0) {
        return FAILURE_CASE;
    }
    const Vec3 q = s.cross(edge1);
    const double v = f * r.dir.dot(q);
    if (v < 0.0 || u + v > 1.0) {
        return FAILURE_CASE;
    }
    double t_intersect = f * edge1.dot(q);
    if (t_intersect > EPSILON) {
        Vec3 p = r.origin + (r.dir * t_intersect);
        return std::make_pair(true, p);
    } 
    return FAILURE_CASE;
}

// Returns true if Ray, and Plane intersects
// Borrowed from ScratchPixel
std::pair<bool, Eigen::Vector3d> intersects(const Ray &r, const Plane &p) {
    double d = (p.normal).dot(r.dir);
    if (d < EPSILON) {
        Vec3 pp = (p.origin - r.origin);
        double t = (pp.dot(p.normal))/d;
        if (t >= 0){
            return std::make_pair(true, r.origin + (t * r.dir));
        }
    }
    return std::make_pair(false, Vec3{0, 0, 0});
}

// Returns true, and intersection point. False implies point returned is a dummy value
std::pair<bool, Eigen::Vector3d> intersects(const Ray &r, const BSphere &b) {
    return std::make_pair(false, Vec3{0, 0, 0});
}



// Ray/box
// http://psgraphics.blogspot.com/2016/02/new-simple-ray-box-test-from-andrew.html
std::pair<bool, Eigen::Vector3d> intersects(const Ray &r, const AABB &a) {
    return std::make_pair(false, Vec3{0, 0, 0});
}

// Eigen::Vector3d project_point_on_plane(const Eigen::Vector3d &pt, const Plane &p);
// Eigen::Vector3d closest_point_on_triangle(const Triangle &t, const Eigen::Vector3d &p);



} // spatial 
} // makeshape
