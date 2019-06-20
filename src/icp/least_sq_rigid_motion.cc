// Copyright MakeShape. 2019, All rights reserved.

#include "least_sq_rigid_motion.hh"
#include "common.hh"

#include <Eigen/SVD>

namespace makeshape {
namespace icp {

//
// Compute Least Square Rigid Motion Using SVD
// by Olga Sorkine-Hornung and Michael Rabinovich
// https://igl.ethz.ch/projects/ARAP/svd_rot.pdf
//
Eigen::Affine3d compute_icp(const spatial::TriMesh &m1, const spatial::TriMesh &m2) { 
    // num vertices
    const int nv_m1 = m1.const_vertices().rows();
    const int nv_m2 = m2.const_vertices().rows();
    CHECK(nv_m1 == nv_m2);

    // 1. compute weighted centroids of both point sets
    Eigen::Vector3d p_prime = m1.centroid();
    Eigen::Vector3d q_prime = m2.centroid();

    // 2. compute centered vectors
    // xi = pi - p_prime 
    // yi = q1 - q_prime
    Eigen::MatrixXd X = m1.const_vertices().colwise() - p_prime;
    Eigen::MatrixXd Y = m2.const_vertices().colwise() - q_prime;

    // 3. compute the d x d covariance matrix
    // S = X.W.Transpose(Y)
    // W = identity
    Eigen::MatrixXd S = X * Y.transpose();

    // 4. compute SVD, 
    // S = U.Z.Transpose(V)
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(S, 
            Eigen::ComputeThinU | 
            Eigen::ComputeThinV);
    const Eigen::MatrixXd U = svd.matrixU();
    const Eigen::MatrixXd V = svd.matrixV();
    Eigen::MatrixXd M(nv_m1, nv_m1);
    {
        M.setIdentity();
        const auto det_V_U_transpose = (V*U.transpose()).determinant();
        M(nv_m1-1, nv_m1-1) = det_V_U_transpose;
    }

    // 5. Compute rotation and translation
    const Eigen::Matrix3d R = V * M * U.transpose();
    const Eigen::Vector3d t = q_prime - R * p_prime;

    // 6. Compute affine matrix
    Eigen::Affine3d ret;
    {
        ret.linear() = R;
        ret.translation() = t;
    }
    return ret;
}


} // icp 
} // makeshape
