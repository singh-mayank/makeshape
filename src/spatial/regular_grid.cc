// Copyright MakeShape. 2019, All rights reserved.

#include "regular_grid.hh"
 
namespace makeshape {
namespace spatial {

namespace {
double compute_approx_average_edge_length(const TriMesh &m) {
    double ret = 0.0;
    const auto vertices = m.vertices();
    for (const TriMesh::Edge &e : m.edges()) {
        Eigen::Vector3d v0 = vertices(e.v0);
        Eigen::Vector3d v1 = vertices(e.v1);
        ret += (v1 - v0).squaredNorm();
    }
    return (ret/static_cast<double>(vertices.size()));
}
}

// @params size contains number of voxels along x, y and z axis
RegularGrid::RegularGrid(const Eigen::Vector3i size) 
    : size_(size) { 
    assert(size_(0) == size_(1));
    assert(size_(1) == size_(2));
}

bool RegularGrid::build_binary_field(const TriMesh &m) {
    
    // needs ray/triangle intersection
    // needs ray/aabb intersection, which is ray plane or ray quad intersection
    // 




    return true;
}

// 1. Brute force
// 2. Fast Sweeping method
bool RegularGrid::build_distance_field(const TriMesh &m) {




    return true;
}

} // spatial 
} // makeshape
