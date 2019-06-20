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
    m.rescale();

    const Eigen::Vector3d p(0.1, 0.1, 0.1);
    constexpr double radius = 0.3;

    // octree
    makeshape::spatial::Octree oc(4);
    oc.build(m.const_vertices());
    const auto nearby = oc.neighbours(p, radius);

    // brute force
    const double r2 = (radius * radius);
    int count = 0;
    const auto vertices = m.const_vertices();
    for (int i = 0; i < vertices.rows(); ++i) {
        Eigen::Vector3d v = vertices.row(i);
        double dist = (v - p).squaredNorm();
        if (dist < r2) {
            ++count;
        }
    }
    // printf("%i == %li\n", count, nearby.rows());
    EXPECT_EQ(count, nearby.rows());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
