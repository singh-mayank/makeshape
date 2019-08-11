// Copyright MakeShape. 2019, All rights reserved.

#include "sdf.hh"
#include "kdtree.hh"

namespace makeshape {
namespace spatial {

namespace {
int MAX_RESOLUTION = 8;
void build(const Eigen::MatrixXd &pts, Eigen::MatrixXd &sdf) {
    KDTree kd(MAX_RESOLUTION);
    std::shared_ptr<std::vector<Eigen::Vector3d>> points;
    {
        // build a vector of points

    }
    kd.build(points);

    // populate sdf grid
    {


    }
}

}

SDF::SDF(const int resolution, const Eigen::MatrixXd &pts) 
    : resolution_(std::min(resolution, MAX_RESOLUTION))  {
    sdf_.resize(resolution_, resolution_);
    build(pts, sdf_);
}


} // spatial 
} // makeshape
