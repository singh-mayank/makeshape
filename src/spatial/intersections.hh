// Copyright MakeShape. 2019, All rights reserved.

#pragma once

#include <Eigen/Dense>


namespace makeshape {
namespace spatial {

class AABB;
class BSphere;
struct Triangle;
struct Ray;
struct Plane;

bool intersects(const AABB &a1, const AABB &a2);
bool intersects(const BSphere &b1, const BSphere &b2);
bool intersects(const AABB &a, const BSphere &b);

std::pair<bool, Eigen::Vector3d> intersects(const Ray &r, const Triangle &t);
std::pair<bool, Eigen::Vector3d> intersects(const Ray &r, const Plane &p);
std::pair<bool, Eigen::Vector3d> intersects(const Ray &r, const BSphere &b);
std::pair<bool, Eigen::Vector3d> intersects(const Ray &r, const AABB &a);

Eigen::Vector3d project_point_on_plane(const Eigen::Vector3d &pt, const Plane &p);
Eigen::Vector3d closest_point_on_triangle(const Triangle &t, const Eigen::Vector3d &p);


} // spatial 
} // makeshape
