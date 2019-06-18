// Copyright MakeShape. 2019, All rights reserved.
#include "edges.hh"
#include <Eigen/Dense>
#include <vector>

#pragma once

namespace makeshape {
namespace spatial {

class OctreeNode {
  public:
    OctreeNode();
    OctreeNode(const Eigen::Vector3d& c, const Eigen::Vector3d& e);
    static constexpr size_t MAX_CHILDREN = 8;
    Eigen::Vector3d center;
    Eigen::Vector3d extents;
    OctreeNode *child[ MAX_CHILDREN ];
    std::vector<Eigen::Vector3d> points;
    size_t depth;
};

class Octree {
  public:
    Octree(const size_t max_depth);
    ~Octree();
    bool build(const std::vector<Eigen::Vector3d> &points); // DELETE THIS, unittest
    bool build(const Eigen::MatrixXd &points);
    size_t num_nodes() const;
    Edges get_edges() const;
  private:
    OctreeNode *root_;
    const size_t max_depth_;
}; // octree

} // spatial 
} // makeshape
