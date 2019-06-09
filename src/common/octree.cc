// Copyright MakeShape. 2019, All rights reserved.

#include "octree.hh"

#include "common.hh"

#include <cstdlib>
#include <cstdio>
 
namespace makeshape {
namespace common {

using Point = Eigen::Vector3d;

namespace {
void insert(OctreeNode *n, const Point &p, size_t curr_depth, size_t max_depth) {
    CHECK(curr_depth <= max_depth);

    // if 'p' not inside 'n', then bail out
    // which child...


    if(curr_depth == max_depth) {
        // figure out which child, 
        // either append point, or create node and append point
        for (int i = 0; i < OCTREE_MAX_CHILDREN; ++i) {

        }

    } else {
        // figure out which child, 
        // either insert, or create node and insert


    }

}

}



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
    
    // check if the point lies within [-1, 1] bounds
    auto out_of_bounds = [](const Point &p) -> bool {
        for (int i = 0; i < 3; ++i) {
            if( p[i] < -1.0 || p[i] > 1.0 ) {
                return true;
            }
        }
        return false;
    };

    root_ = new OctreeNode();
    size_t curr_depth = 0;
    const size_t nv = points.size();
    for (size_t i = 0; i < nv; ++i) {
        const Point &p = points[i];
        CHECK(out_of_bounds(p));
        insert(root_, p, 0, max_depth_);
    }

    return true;
}

} // common
} // makeshape
