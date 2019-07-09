// Copyright MakeShape. 2019, All rights reserved.
#include "edges.hh"
#include <Eigen/Dense>
#include <vector>
#include <memory>

#pragma once

//
// TODO(mayank): replace explicit points with point indices
// TODO(mayank): also, pass shared_ptr to the points, save a pointer in octree
// 
// TODO(mayank): use 'union' for points_ or child_ for OctreeNode

namespace makeshape {
namespace spatial {

enum class SplitAxis { X = 0u, Y, Z };
struct KDTreeNode {
    SplitAxis axis;
    double value;
    KDTreeNode *left;
    KDTreeNode *right;
    std::vector<std::size_t> points;
}; // KDTreeNode

class KDTree {
  public:
    KDTree(const std::size_t max_depth);
    ~KDTree();
    void build(std::shared_ptr<const std::vector<Eigen::Vector3d>> points);
    Edges get_edges() const;
  private:
    KDTreeNode *build(const SplitAxis axis, 
                      const double value,
                      const std::size_t curr_depth,
                      const std::vector<std::size_t> &pt_indices,
                      KDTreeNode *n);
    std::size_t nearest_neighbour(const Eigen::Vector3d &p);
    std::vector<std::size_t> nearest_n_neighbours(const Eigen::Vector3d &p, const std::size_t n);
    
    std::size_t max_depth_{1};
    KDTreeNode *root_{nullptr};
    std::shared_ptr<const std::vector<Eigen::Vector3d>> data_{nullptr};
}; // KDTree

} // spatial 
} // makeshape
