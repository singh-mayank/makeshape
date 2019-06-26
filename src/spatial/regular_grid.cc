// Copyright MakeShape. 2019, All rights reserved.

#include "regular_grid.hh"
 
namespace makeshape {
namespace spatial {

namespace {
double compute_average_edge_length(const TriMesh &m) {
    double ret = 0;
    //for (const TriMesh::Edge &e : 

}
}

// @params size contains number of voxels along x, y and z axis
RegularGrid::RegularGrid(const Eigen::Vector3i size) 
    : size_(size) { 
    assert(size_(0) == size_(1));
    assert(size_(1) == size_(2));
}

bool RegularGrid::build_binary_field(const TriMesh &m) {
    






    return true;
}

// 1. Brute force
// 2. Fast Sweeping method
bool RegularGrid::build_distance_field(const TriMesh &m) {




    return true;
}

} // spatial 
} // makeshape
