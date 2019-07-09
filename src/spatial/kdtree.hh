// Copyright MakeShape. 2019, All rights reserved.
#include "edges.hh"
#include <Eigen/Dense>
#include <vector>
#include <memory>

#pragma once

//
// TODO(mayank): replace explicit points with point indices
// TODO(mayank): also, pass shared_ptr to the points, save a pointer in octree

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
    Eigen::Vector3d nearest_neighbour(const Eigen::Vector3d &q) const;
    std::vector<std::size_t> nearest_n_neighbours(const Eigen::Vector3d &q, 
                                                  const std::size_t n) const;
    Edges get_edges() const;
  private:
    KDTreeNode *build(const SplitAxis axis, 
                      const double value,
                      const std::size_t curr_depth,
                      const std::vector<std::size_t> &pt_indices,
                      KDTreeNode *n) const;
    Eigen::Vector3d nns(const Eigen::Vector3d &q, 
                        const KDTreeNode *n, 
                        const double curr_distance) const;
  private:
    std::size_t max_depth_{1};
    KDTreeNode *root_{nullptr};
    std::shared_ptr<const std::vector<Eigen::Vector3d>> data_{nullptr};
}; // KDTree

} // spatial 
} // makeshape
