// Copyright MakeShape. 2019, All rights reserved.
//
#include "octree.hh"

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

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
