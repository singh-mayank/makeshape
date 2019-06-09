// Copyright MakeShape. 2019, All rights reserved.

#include "octree.hh"

#include "common.hh"

#include <cstdlib>
#include <cstdio>
 
namespace makeshape {
namespace common {

using Point = Eigen::Vector3d;

Octree::Octree(const int max_depth) 
    : root_(nullptr)
    , max_depth_(max_depth) {
    // do nothing
}

Octree::~Octree() {
    // recursive delete
}

bool Octree::build(const std::vector<Eigen::Vector3d> &points) {
    if (points.empty()) {
        return false;
    }
    
    auto out_of_bounds = [](const Point &p) -> bool {
        for (int i = 0; i < 3; ++i) {
            if( p[i] < -1.0 || p[i] > 1.0 ) {
                return true;
            }
        }
        return false;
    };

    const size_t nv = points.size();
    for (size_t i = 0; i < nv; ++i) {
        CHECK(out_of_bounds(points[i]));
        



    }


    return true;
}

} // common
} // makeshape
