// Copyright MakeShape. 2019, All rights reserved.

#include "fast_poisson_sampling.hh"

namespace makeshape {
namespace algs {

std::vector<Eigen::Vector2d> sample_plane(const double r, const int k) {
    struct GridCell {
        float center;
        float size;
    };

    constexpr int SIZE = 5;
    vector<vector<GridCell> grid;
    grid.resize(5);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            
        }
    }



}


std::vector<Eigen::Vector3d> sample_cube(const int n_samples) {
    return std::vector<Eigen::Vector3d>{};
}

std::vector<Eigen::Vector3d> sample_sphere(const int n_samples) {
    return std::vector<Eigen::Vector3d>{};
}

} // algs
} // makeshape
