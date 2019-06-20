// Copyright MakeShape. 2019, All rights reserved.
#include <Eigen/Dense>
#include <Eigen/Geometry>

#include "trimesh.hh"

#pragma once

namespace makeshape {
namespace icp {

//
// Compute Least Square Rigid Motion Using SVD
// by Olga Sorkine-Hornung and Michael Rabinovich
// https://igl.ethz.ch/projects/ARAP/svd_rot.pdf
//
Eigen::Affine3d least_sq_rigid_motion_svd(const spatial::TriMesh &m1, const spatial::TriMesh &m2);

} // icp 
} // makeshape
