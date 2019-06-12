// Copyright MakeShape. 2019, All rights reserved.
#include <Eigen/Dense>
#include <vector>

#pragma once

namespace makeshape {
namespace spatial {

class OctreeNode {
  public:
    //TODO(mayank): make these private
    static constexpr int MAX_CHILDREN = 8;
    Eigen::Vector3d center;
    Eigen::Vector3d extents;
    OctreeNode *child[ MAX_CHILDREN ];
    std::vector<Eigen::Vector3d> points;
    OctreeNode() {
        OctreeNode(Eigen::Vector3d(0.5, 0.5, 0.5), Eigen::Vector3d(1, 1, 1));
    }
    OctreeNode(const Eigen::Vector3d& c, const Eigen::Vector3d& e) {
        center = c;
        extents = e;
        for(int i = 0; i < MAX_CHILDREN; ++i) {
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
    size_t num_nodes() const;
}; // octree

} // spatial 
} // makeshape
