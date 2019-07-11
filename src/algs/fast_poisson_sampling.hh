// Copyright MakeShape. 2019, All rights reserved.

#include <Eigen/Dense>
#include <vector>

#pragma once

namespace makeshape {
namespace algs {

std::vector<Eigen::Vector3d> sample_cube(const int n_samples);
std::vector<Eigen::Vector3d> sample_sphere(const int n_samples);


} // algs
} // makeshape
