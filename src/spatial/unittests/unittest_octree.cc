// Copyright MakeShape. 2019, All rights reserved.
//
#include "octree.hh"
#include "trimesh.hh"

#include "gtest/gtest.h" 

TEST(Octree, build_tree)
{
    Eigen::MatrixXd points(8, 3);
    points << 0.25, 0.25, 0.25, 
              0.75, 0.25, 0.25,  
              0.25, 0.75, 0.25, 
              0.75, 0.75, 0.25, 
              0.25, 0.25, 0.75, 
              0.75, 0.25, 0.75, 
              0.25, 0.75, 0.75, 
              0.75, 0.75, 0.75; 
    {
        makeshape::spatial::Octree o(1);
        o.build(points);
        EXPECT_EQ(o.num_nodes(), 9u);
    }
    {
        makeshape::spatial::Octree o(2);
        o.build(points);
        EXPECT_EQ(o.num_nodes(), 17u);
    }
}

TEST(Octree, neighbours)
{
    // mesh
    makeshape::spatial::TriMesh m = makeshape::spatial::load_mesh("bunny.obj");

    makeshape::spatial::Octree oc(4);
    oc.build(m.const_vertices());
    
    const std::vector<Eigen::Vector3d> pts{
        Eigen::Vector3d{0, 0, 0},
        Eigen::Vector3d{1, 0, 0},
        Eigen::Vector3d{0, 1, 0},
        Eigen::Vector3d{1, 1, 0},
        Eigen::Vector3d{0, 0, 1},
        Eigen::Vector3d{1, 0, 1},
        Eigen::Vector3d{0, 1, 1},
        Eigen::Vector3d{1, 1, 1}};

    for(const auto &p : pts) {
        constexpr double radius = 0.75;

        // expected via octree
        const auto nearby_pts = oc.neighbours(p, radius);
        const size_t expected = nearby_pts.rows();

        // actual via brute force
        const double r2 = (radius * radius);
        size_t actual = 0;
        const auto vertices = m.const_vertices();
        for (int i = 0; i < vertices.rows(); ++i) {
            Eigen::Vector3d v = vertices.row(i);
            double dist = (v - p).squaredNorm();
            if (dist < r2) {
                ++actual;
            }
        }
        
        // check
        EXPECT_EQ(actual, expected);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
