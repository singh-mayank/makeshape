// Copyright MakeShape. 2019, All rights reserved.
#include "edges.hh"
#include "aabb.hh"
#include <Eigen/Dense>
#include <vector>
#include <memory>

#pragma once

namespace makeshape {
namespace spatial {

enum class SplitAxis { X = 0, Y = 1, Z = 2 };
struct KDTreeNode2 {
    SplitAxis axis;
    double value;
    KDTreeNode2 *left{nullptr};
    KDTreeNode2 *right{nullptr};
    std::vector<std::size_t> points;
}; // KDTreeNode

class KDTree2 {
  public:
    KDTree2(const std::size_t max_depth);
    ~KDTree2();
    void build(const Eigen::MatrixXd &points);
    void build(std::shared_ptr<const std::vector<Eigen::Vector3d>> points);
    Eigen::Vector3d nearest_neighbour(const Eigen::Vector3d &q) const;
    Edges get_edges() const;
  private:
    KDTreeNode2 *build(const std::vector<std::size_t> &pt_indices, int depth) const;
    void nns(const Eigen::Vector3d &q, 
             const KDTreeNode2 *n, 
             double &curr_distance,
             std::size_t &nearest_pt) const;
  private:
    std::size_t max_depth_{1}; // root is depth 0
    KDTreeNode2 *root_{nullptr};
    std::shared_ptr<const std::vector<Eigen::Vector3d>> data_{nullptr};
}; // KDTree

} // spatial 
} // makeshape
