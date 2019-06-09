// Copyright MakeShape. 2019, All rights reserved.

#include "octree.hh"

#include "common.hh"

#include <cstdlib>
#include <cstdio>
 
namespace makeshape {
namespace common {

using Point = Eigen::Vector3d;
constexpr int DIM = 3;

namespace {

// ---------------------------------------------------------------------------
// Children
// 0: [c-x, c-y, c-z] -> [c.x, c-y, c-z]
// 4: 
// 5: 
// 6: 
// 7: 
// ---------------------------------------------------------------------------

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
    for (size_t i = 0; i < DIM; ++i) {
        if( round(p[i] - n->center[i]) == 1 ) {
            index = index << (i+1);
        }
    }
    return index;
}

std::pair<Point, Point> compute_child_center_and_extents(const OctreeNode* n, const size_t child_index) {
    Point center;
    const Point extents = 0.5*n->extents;
    
    for (size_t i = 0; i < DIM; ++i) {
        center[i] = (child_index & (1 << (i+1)))? 
            n->center[i] - extents[i] : n->center[i] + extents[i];
    }

    return std::make_pair(center, extents);
}


void insert(OctreeNode *n, const Point &p, size_t curr_depth, size_t max_depth) {
    CHECK (curr_depth <= max_depth);
    CHECK (n != nullptr);
    CHECK (inside(n, p));


    size_t child_index = compute_child_index(n, p);
    if (n->child[child_index] == nullptr) {
        const auto center_and_extents = compute_child_center_and_extents(n, child_index);
        OctreeNode *new_node = new OctreeNode();
        new_node->center = center_and_extents.first;
        new_node->extents = center_and_extents.second;
        n->child[child_index] = new_node;
    }

    if (curr_depth == max_depth) {
        n->points.push_back(p);
    } else {
        insert(n->child[child_index], p, curr_depth+1, max_depth);
    }
}

} // namespace


Octree::Octree(const size_t max_depth) 
    : root_(nullptr)
    , max_depth_(max_depth) {
    // do nothing
}

Octree::~Octree() {
    // recursive delete
}

bool Octree::build(const std::vector<Eigen::Vector3d> &points) {
    if (points.empty() || max_depth_ < 0 || max_depth_ > 8) {
        return false;
    }

    if (root_ != nullptr) {
        // clear_tree(root_);
    }

    root_ = new OctreeNode();
    size_t curr_depth = 0;
    const size_t nv = points.size();
    for (size_t i = 0; i < nv; ++i) {
        const Point &p = points[i];
        CHECK(inside(root_, p));
        insert(root_, p, 1, max_depth_);
    }

    return true;
}

void Octree::print_stats() const {
    if (root_ == nullptr) {
        dprintf("Error: Octree empty\n");
    }
    

}



} // common
} // makeshape
