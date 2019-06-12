// Copyright MakeShape. 2019, All rights reserved.

#include <Eigen/Dense>

#pragma once

namespace makeshape {
namespace spatial {

class AABB {
  public:
    AABB();
    AABB(const Eigen::Vector3d &c, const Eigen::Vector3d &e);
    AABB(const AABB &other);
    AABB(const AABB &&other);
    const Eigen::Vector3d &const_center() const { return center; }
    const Eigen::Vector3d &const_extents() const { return extents; }
    Eigen::Vector3d &center() const { return center; }
    Eigen::Vector3d &extents() const { return extents; }
    bool include(const Eigen::Vector3d &p);
  private:
    Eigen::Vector3d center;
    Eigen::Vector3d extents;
}; // AABB

static AABB build_aabb(const std::vector<Eigen::Vector3d>  &points);


} // spatial 
} // makeshape
