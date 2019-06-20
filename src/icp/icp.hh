// Copyright MakeShape. 2019, All rights reserved.
#include <Eigen/Dense>
#include <Eigen/Geometry>

#include "trimesh.hh"

#pragma once

namespace makeshape {
namespace icp {

Eigen::Affine3d compute_icp(const spatial::TriMesh &m1, const spatial::TriMesh &m2);

} // icp 
} // makeshape
