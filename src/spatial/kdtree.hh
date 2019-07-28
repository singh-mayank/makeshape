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

class KDTree {
    struct KDTreeNode {
	    SplitAxis axis;
	    double value;
	    KDTreeNode *left{nullptr};
	    KDTreeNode *right{nullptr};
	    std::vector<size_t> points;
    }; // KDTreeNode
  public:
    KDTree(const size_t max_depth);
    ~KDTree();
    void build(const Eigen::MatrixXd &points);
    void build(std::shared_ptr<const std::vector<Eigen::Vector3d>> points);
    std::pair<size_t, double> nearest_neighbour(const Eigen::Vector3d &q) const;
    Edges get_edges() const;
  private:
    KDTreeNode *build(const std::vector<size_t> &pt_indices, int depth) const;
    void nns(const Eigen::Vector3d &q, 
            const KDTreeNode *n,
            double &current_distance, 
            size_t &curr_min_index) const;
  private:
    size_t max_depth_{1}; // root is depth 0
    KDTreeNode *root_{nullptr};
    std::shared_ptr<const std::vector<Eigen::Vector3d>> data_{nullptr};
}; // KDTree

} // spatial 
} // makeshape
