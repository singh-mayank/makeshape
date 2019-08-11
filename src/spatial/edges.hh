// Copyright MakeShape. 2019, All rights reserved.

#pragma once

#include <Eigen/Dense>
#include <vector>
#include <array>


namespace makeshape {
namespace spatial {

// A set of edges
// Mimics LibIGL `set_edges` expected data structure
//   P  #P by 3 list of vertex positions
//   E  #E by 2 list of edge indices into P
//   C  #E|1 by 3 color(s)
struct Edges {
    Eigen::MatrixXd P;
    Eigen::MatrixXi E;
    Eigen::MatrixXd C;
};

//
// Edges for a cube (used by the likes of Octree/kd-Tree)
//
struct CubeEdges {
    constexpr static int N_VERTICES{8};
    constexpr static int N_EDGES{12};
    std::array<Eigen::Vector3d, N_VERTICES> v;
    std::array<std::pair<int, int>, N_EDGES> e;
};

//
// For display, convert a set of cubes into a set of edges
//
Edges make_edges(const std::vector<CubeEdges> &ce);

} // spatial 
} // makeshape
