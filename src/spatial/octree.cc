// Copyright MakeShape. 2019, All rights reserved.

#include "octree.hh"
#include "common.hh"
#include <cstdlib>
#include <cstdio>
 
namespace makeshape {
namespace spatial {

using Point = Eigen::Vector3d;
constexpr int DIM = 3;

namespace {

bool inside(const OctreeNode *n, const Point &p) {
    const Point min_pt = n->center - n->extents;
    const Point max_pt = n->center + n->extents;
    for(int i = 0; i < DIM; ++i) {
        if (p[i] < min_pt[i]) { return false; }
        if (p[i] > max_pt[i]) { return false; }
    }
    return true;
}

size_t compute_child_index(const OctreeNode *n, const Point &p) {
    size_t index = 0;
    const auto c = n->center;
    const auto e = n->extents;
    for (size_t i = 0; i < DIM; ++i) {
        const auto x = (p[i] - (c[i] - 0.5*e[i]))/e[i];
        if( std::round(x) ) {
            index |= (1 << i);
        }
    }
    return index;
}

std::pair<Point, Point> compute_center_and_extents(const OctreeNode* n, const size_t child_index) {
    Point center;
    const Point extents = 0.5*n->extents;
    for (size_t i = 0; i < DIM; ++i) {
        center[i] = (child_index & (1 << i))? 
            n->center[i] + 0.5*extents[i] : n->center[i] - 0.5*extents[i];
    }
    return std::make_pair(center, extents);
}


OctreeNode* insert(OctreeNode *n, 
        const Point &p, 
        const Point &center, 
        const Point &extents, 
        const size_t curr_depth, 
        const size_t max_depth) {
    CHECK (curr_depth <= max_depth);
    if (n == nullptr) {
        n = new OctreeNode(center, extents);
    }
    if (curr_depth == max_depth) {
        n->points.push_back(p);
    } else {
        const size_t index = compute_child_index(n, p); 
        Point child_center, child_extents;
        if (n->child[index] == nullptr) {
            const auto center_and_extents = compute_center_and_extents(n, index);
            child_center = center_and_extents.first;
            child_extents = center_and_extents.second;
        } 
        n->child[index] = insert(n->child[index], p, child_center, child_extents, curr_depth+1, max_depth);
    }
    return n;
}

void clear_tree(OctreeNode *n) {
    if(n == nullptr) {
        return;
    } 
    for(int i = 0; i < OctreeNode::MAX_CHILDREN; ++i) {
        clear_tree(n->child[i]);
        delete n->child[i];
        n->child[i] = nullptr;  
    }
    n->points.clear();
}

size_t count_nodes(const OctreeNode *n) {
    if (n == nullptr) {
        return 0;
    }
    size_t c = 1;
    for(int i = 0; i < OctreeNode::MAX_CHILDREN; ++i) {
        c += count_nodes(n->child[i]);
    }
    return c;
}

} // namespace


Octree::Octree(const size_t max_depth) 
    : root_(nullptr)
    , max_depth_(max_depth) {
    // do nothing
}

Octree::~Octree() {
    if (root_ != nullptr) {
        clear_tree(root_);
        delete root_;
        root_ = nullptr;
    }
}

bool Octree::build(const std::vector<Eigen::Vector3d> &points) {
    if (points.empty() || max_depth_ < 0 || max_depth_ > 8) {
        return false;
    }

    if (root_ != nullptr) {
        clear_tree(root_);
        delete root_;
        root_ = nullptr;
    }

    const Point center(0.5, 0.5, 0.5);
    const Point extents(1, 1, 1);
    const size_t nv = points.size();
    for (size_t i = 0; i < nv; ++i) {
        const Point &p = points[i]; 
        root_ = insert(root_, p, center, extents, 0, max_depth_);
    }
    return true;
}

size_t Octree::num_nodes() const {
    return count_nodes(root_);
}

} // spatial 
} // makeshape
