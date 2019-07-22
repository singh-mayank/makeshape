// Copyright MakeShape. 2019, All rights reserved.
//
#include "kdtree.hh"
#include "trimesh.hh"
#include "common.hh"

#include "gtest/gtest.h" 

#include <random>
#include <chrono>
#include <inttypes.h>

TEST(KDTree, neighbours)
{
    using PointArray = std::vector<Eigen::Vector3d>;

    // mesh
    makeshape::spatial::TriMesh m = makeshape::spatial::load_mesh("bunny.obj");
    const auto vertices = m.vertices();
    const auto n_rows = vertices.rows();
    
    std::shared_ptr<PointArray> pts = std::make_shared<PointArray>();
    pts->reserve(n_rows);
    for(int i = 0; i < n_rows; ++i) {
        pts->push_back(vertices.row(i));
    }

    // kdtree
    makeshape::spatial::KDTree ktree(4);
    ktree.build(pts);
    
    // samples
    constexpr int N_SAMPLES = 1000;
    PointArray q(N_SAMPLES);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10, 10);
    for (int i = 0; i < N_SAMPLES; ++i) {
        double x = dis(gen);
        double y = dis(gen);
        double z = dis(gen);
        q[i] = Eigen::Vector3d(x, y, z);
    }

    // distance using kdtree 
    std::vector<double> actual(N_SAMPLES);
    int64_t t1, t2;
    {
        auto start = std::chrono::steady_clock::now();   
        {
            for (int i = 0; i < N_SAMPLES; ++i) {
                Eigen::Vector3d p = ktree.nearest_neighbour(q[i]);
                actual[i] = (q[i] - p).squaredNorm();
            }
        }
        auto end = std::chrono::steady_clock::now();
        t1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }

    std::vector<double> expected(N_SAMPLES);
    {
        auto compute_min_dist = [&pts, &n_rows](const Eigen::Vector3d qq){
            double min_dist = std::numeric_limits<double>::max();
            for (int i = 0; i < n_rows; ++i) {
                Eigen::Vector3d each = pts->at(i);
                double d = (qq - each).squaredNorm();
                min_dist = std::min(min_dist, d);
            }
            return min_dist;
        };

        auto start = std::chrono::steady_clock::now();   
        {
            for (int i = 0; i < N_SAMPLES; ++i) {
                expected[i] = compute_min_dist(q[i]);
            }
        }
        auto end = std::chrono::steady_clock::now();
        t2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }

    // test
    EXPECT_LE(t1, t2);
    constexpr double TOLERANCE = 1e-6;
    for (int i = 0; i < N_SAMPLES; ++i) {
        EXPECT_GE(expected[i], actual[i]);
    }
}
