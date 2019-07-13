// Copyright MakeShape. 2019, All rights reserved.

#include <Eigen/Dense>
#include <vector>

#pragma once

namespace makeshape {
namespace algs {

// Borrowed from 
// https://www.cs.ubc.ca/~rbridson/docs/bridson-siggraph07-poissondisk.pdf 
// @params 'r': the minimum distance between samples
// @params 'k': limit of samples to choose before rejection
std::vector<Eigen::Vector2d> sample_plane(const double r, const int k);

std::vector<Eigen::Vector3d> sample_cube(const int n_samples);
std::vector<Eigen::Vector3d> sample_sphere(const int n_samples);


} // algs
} // makeshape
