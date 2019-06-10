// Copyright MakeShape. 2019, All rights reserved.
//
#include "octree.hh"

#include "gtest/gtest.h" 


TEST(Octree, build_tree)
{
    std::vector<Eigen::Vector3d> p{
        Eigen::Vector3d(0.25, 0.25, 0.25),
        Eigen::Vector3d(0.75, 0.25, 0.25),
        Eigen::Vector3d(0.25, 0.75, 0.25),
        Eigen::Vector3d(0.75, 0.75, 0.25),

        Eigen::Vector3d(0.25, 0.25, 0.75),
        Eigen::Vector3d(0.75, 0.25, 0.75),
        Eigen::Vector3d(0.25, 0.75, 0.75),
        Eigen::Vector3d(0.75, 0.75, 0.75),
    };

    {
        makeshape::common::Octree o(1);
        o.build(p);
        EXPECT_EQ(o.num_nodes(), 9u);
    }
    {
        makeshape::common::Octree o(2);
        o.build(p);
        EXPECT_EQ(o.num_nodes(), 17u);
    }

}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
