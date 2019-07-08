// Copyright MakeShape. 2019, All rights reserved.
#include "edges.hh"
#include "aabb.hh"
#include <Eigen/Dense>
#include <vector>

#pragma once

//
// TODO(mayank): replace explicit points with point indices
// TODO(mayank): also, pass shared_ptr to the points, save a pointer in octree
// 
// TODO(mayank): use 'union' for points_ or child_ for OctreeNode

namespace makeshape {
namespace spatial {

class KDTreeNode {
  public:
    KDTreeNode();
}; // KDTreeNode

class KDTree {
  public:
    KDTree(const size_t max_depth);
    ~KDTree();
  private:
    KDTree *root_;
}; // KDTree

} // spatial 
} // makeshape
