// Copyright MakeShape. 2019, All rights reserved.
#include <Eigen/Dense>
#include <vector>

#pragma once

namespace makeshape {
namespace common {

constexpr int OCTREE_MAX_CHILDREN = 8;

struct OctreeNode {
    Eigen::Vector3d center;
    Eigen::Vector3d extents;
    OctreeNode *child[8];
    std::vector<Eigen::Vector3d> points;
    OctreeNode() {
        center = Eigen::Vector3d(0, 0, 0);
        extents = Eigen::Vector3d(1, 1, 1);
        for(int i = 0; i < OCTREE_MAX_CHILDREN; ++i) {
            child[i] = nullptr;
        }
    }
};

class Octree {
    OctreeNode *root_;
    const size_t max_depth_;
  public:
    Octree(const size_t max_depth);
    ~Octree();
    bool build(const std::vector<Eigen::Vector3d> &points);
    void print_stats() const;
}; // octree

} // common
} // makeshape