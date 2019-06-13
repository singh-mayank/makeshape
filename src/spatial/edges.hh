// Copyright MakeShape. 2019, All rights reserved.

#include <Eigen/Dense>

#pragma once

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

} // spatial 
} // makeshape
