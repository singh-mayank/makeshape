// Copyright MakeShape. 2019, All rights reserved.

#include <Eigen/Dense>

#pragma once

namespace makeshape {
namespace spatial {
//
// AABB with center and extents
//
class AABB {
  public:
    AABB() : center_{Eigen::Vector3d(0, 0, 0)}, extents_{Eigen::Vector3d(1, 1, 1)} { }
    AABB(const Eigen::Vector3d &c, const Eigen::Vector3d &e);
    AABB(const AABB &other);
    AABB& operator=(const AABB &other);
    const Eigen::Vector3d &const_center() const { return center_; }
    const Eigen::Vector3d &const_extents() const { return extents_; }
    Eigen::Vector3d &center() { return center_; }
    Eigen::Vector3d &extents() { return extents_; }
    Eigen::Vector3d min_pt() const { return (center_ - 0.5*extents_); }
    Eigen::Vector3d max_pt() const { return (center_ + 0.5*extents_); }
    bool include(const Eigen::Vector3d &p);
  private:
    Eigen::Vector3d center_;
    Eigen::Vector3d extents_;
}; // AABB

//static AABB build_aabb(const std::vector<Eigen::Vector3d>  &points);


} // spatial 
} // makeshape
