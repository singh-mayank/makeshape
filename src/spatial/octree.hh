// Copyright MakeShape. 2019, All rights reserved.

#pragma once

#include "edges.hh"
#include "aabb.hh"
#include <Eigen/Dense>
#include <vector>


//
// TODO(mayank): replace explicit points with point indices
// TODO(mayank): also, pass shared_ptr to the points, save a pointer in octree
// 
// TODO(mayank): use 'union' for points_ or child_ for OctreeNode

namespace makeshape {
namespace spatial {

class OctreeNode {
  public:
    OctreeNode();
    OctreeNode(const AABB &box, const size_t depth);
    Eigen::Vector3d min_pt() const { return box_.min_pt(); }
    Eigen::Vector3d max_pt() const { return box_.max_pt(); }
    static constexpr size_t MAX_CHILDREN = 8;
    AABB box_;
    OctreeNode *child_[ MAX_CHILDREN ];
    std::vector<Eigen::Vector3d> points_;
    size_t depth_;
}; // OctreeNode

class Octree {
  public:
    Octree(const size_t max_depth);
    ~Octree();
    size_t num_nodes() const;
    Edges get_edges() const;
    bool build(const Eigen::MatrixXd &points);
    const Eigen::MatrixXd neighbours(const Eigen::Vector3d &p, const double radius);
  private:
    OctreeNode *root_{nullptr};
    const size_t max_depth_;
}; // Octree

} // spatial 
} // makeshape
