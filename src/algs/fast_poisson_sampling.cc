// Copyright MakeShape. 2019, All rights reserved.

#include "fast_poisson_sampling.hh"

namespace makeshape {
namespace algs {

std::vector<Eigen::Vector2d> sample_plane(const double r, const int k) {
    struct GridCell {
        Eigen::Vector2d center;
        int index;
    };

    std::vector<Eigen::Vector2d> ret;
    constexpr int DIM = 2;
    const double CELL_SIZE = r/sqrt(DIM);
    const int SIZE = static_cast<int>(1.0/CELL_SIZE);
    const double HALF_CELL_SIZE = 0.5 * CELL_SIZE;

    // remove this
    {
        printf("Cell size: %f, Size: %i\n", CELL_SIZE, SIZE);
    }

    std::vector<std::vector<GridCell>> grid;
    grid.resize(SIZE);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            const Eigen::Vector2d c((i*CELL_SIZE) + HALF_CELL_SIZE, 
                                    (j*CELL_SIZE) + HALF_CELL_SIZE);
            grid[i].emplace_back(GridCell{c, -1});
            //printf("\t[%i, %i] : GridCell{(%f, %f) | %i}\n", i, j, c[0], c[1], -1);
        }
    }

    auto point_in_cell = [&grid](const Eigen::Vector2d &p) -> bool {
        return false;
    };

    std::vector<std::size_t> active_list;



    return ret;
}


std::vector<Eigen::Vector3d> sample_cube(const int n_samples) {
    return std::vector<Eigen::Vector3d>{};
}

std::vector<Eigen::Vector3d> sample_sphere(const int n_samples) {
    return std::vector<Eigen::Vector3d>{};
}

} // algs
} // makeshape
