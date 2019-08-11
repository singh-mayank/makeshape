// Copyright MakeShape. 2019, All rights reserved.

#pragma once

#include <Eigen/Dense>


namespace makeshape {
namespace spatial {

struct Edges;
struct CubeEdges;

//
// AABB with center and extents
//
class AABB {
  public:
    AABB() : center_{Eigen::Vector3d(0, 0, 0)}, extents_{Eigen::Vector3d(1, 1, 1)} { }
    AABB(const Eigen::Vector3d &c, const Eigen::Vector3d &e);
    AABB(const AABB &other);
    AABB& operator=(const AABB &other);
    const Eigen::Vector3d &center() const { return center_; }
    const Eigen::Vector3d &extents() const { return extents_; }
    Eigen::Vector3d &mutable_center() { return center_; }
    Eigen::Vector3d &mutable_extents() { return extents_; }
    Eigen::Vector3d min_pt() const { return (center_ - 0.5*extents_); }
    Eigen::Vector3d max_pt() const { return (center_ + 0.5*extents_); }
    void print() const;
    void print_minmax() const;
    bool inside(const Eigen::Vector3d &point) const;
    static AABB make_from_minmax(const Eigen::Vector3d &minpt, const Eigen::Vector3d &maxpt);
  private:
    Eigen::Vector3d center_;
    Eigen::Vector3d extents_;
}; // AABB

Edges get_edges(const AABB &box);
CubeEdges get_cube_edges(const AABB &box);

} // spatial 
} // makeshape
