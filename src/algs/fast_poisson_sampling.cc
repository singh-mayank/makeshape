// Copyright MakeShape. 2019, All rights reserved.

#include "fast_poisson_sampling.hh"
#include "common.hh"

#include <random>
#include <ctime>
#include <cstdlib>

namespace makeshape {
namespace algs {
namespace {

constexpr double R = 1.0/static_cast<double>(RAND_MAX);
double generate_random(const double min_value, const double max_value) {
    double random_number = rand() * R; // between 0 and 1
    return (min_value + (random_number * (max_value - min_value)));
}

std::vector<Eigen::Vector2d> generate_random_pts(const double r, 
                                                 const int k, 
                                                 const Eigen::Vector2d &c) {
    std::vector<Eigen::Vector2d> ret;
    const double r2 = r*2;
    const double r4 = r*4;
    while(ret.size() < k) {
        // generate random point
        double theta = generate_random(0, 2*M_PI);
        double radius = generate_random(r2, r4);
		Eigen::Vector2d p = c + Eigen::Vector2d{ radius * cos(theta), radius * sin(theta) };
		if (p.x() < 0.0 || p.x() > 1.0 || p.y() < 0.0 || p.y() > 1.0) {
			continue;
		}
        ret.push_back(p);
    }
    return ret;
}

}

std::vector<Eigen::Vector2d> sample_plane(const double r, const int k) {
    struct GridCell {
        Eigen::Vector2d center;
        int index; // Index into an array of samples. 
                   // Sample point lies within this GridCell
    };

    srand(static_cast<unsigned int>(time(0)));
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
    
    std::vector<Eigen::Vector2d> samples;
    std::vector<std::size_t> active_list;

    auto insert = [&SIZE, &grid, &active_list, &samples](const Eigen::Vector2d &p) {
        const int row = static_cast<int>(SIZE * p.x());
        const int col = static_cast<int>(SIZE * p.y());
        samples.emplace_back(p);
        const int last_index = static_cast<int>(samples.size()-1);
        active_list.push_back(last_index);
        grid[row][col].index = last_index;
    };

    auto is_valid = [&SIZE, &grid, &samples, &r](const Eigen::Vector2d &p) -> bool {
        const double r2 = (r*r);
        const int row = static_cast<int>(SIZE * p.x());
        const int col = static_cast<int>(SIZE * p.y());
        for(int r = row-1; r < row+1; ++r) {
            for(int c = col-1; c < col+1; ++c) {
                if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) {
                    continue;
                }

				const int index = grid[r][c].index;
				if (index < 0 || index >= samples.size()) {
					continue;
				}

                Eigen::Vector2d p_neighbour = samples.at(index);
                if((p - p_neighbour).squaredNorm() < r2) {
                    return false;
                }
            }
        }
        return true;
    };


    Eigen::Vector2d x0{rand()*R, rand()*R};
	CHECK(x0.x() <= 1.0);
	CHECK(x0.x() >= 0.0);
	CHECK(x0.y() <= 1.0);
	CHECK(x0.y() >= 0.0);

    insert(x0);
    while (!active_list.empty()) {
        int random_index = static_cast<int>((rand()*R) * active_list.size()-1);
        CHECK(random_index < active_list.size());
    
        // generate 'k' points in annulus of 'r' to '2r'
        const Eigen::Vector2d &xi = samples.at(active_list.at(random_index));
        const std::vector<Eigen::Vector2d> k_random_pts = generate_random_pts(r, k, xi);
 
        // check if any point is farther than 'r' from existing points - insert in samples 
        bool sample_found = false;
        for (const Eigen::Vector2d &each_pt : k_random_pts) {
            if (is_valid(each_pt)) {
                insert(each_pt);
                sample_found = true;
            } 
        }

        if (!sample_found) {
            active_list.erase(active_list.begin() + random_index);
        }

    }

    return samples;
}


std::vector<Eigen::Vector3d> sample_cube(const int n_samples) {
    return std::vector<Eigen::Vector3d>{};
}

std::vector<Eigen::Vector3d> sample_sphere(const int n_samples) {
    return std::vector<Eigen::Vector3d>{};
}

} // algs
} // makeshape
