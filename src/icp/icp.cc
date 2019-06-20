// Copyright MakeShape. 2019, All rights reserved.

#include "icp.hh"
 
namespace makeshape {
namespace icp {

/*
Eigen::Vector3f trans_vec_A;
//note that you have to create a Translation because multiplying a 
//Transform with a vector will _apply_ the transform to the vector
Eigen::Translation<float,3> translation_A(trans_vec_A);
Eigen::Quaternionf rotation_B;
Eigen::Quaternionf rotation_C;
Eigen::Quaternionf rotation_D;
Eigen::Vector3f trans_vec_E;
Eigen::Translation<float,3> translation_E(trans_vec_E);
Eigen::Transform<float,3,Affine> combined = 
      translation_A * rotation_B * rotation_C * rotation_D * translation_E;

combined*v = A*B*C*D*E*v = A*(B*(C*(D*(E*v))))

*/

Eigen::Affine3d compute_icp() {
    //Eigen::Transform<float, 3, Eigen::Affine> combined;
    
    Eigen::Affine3d t;
    return t;
}


} // icp 
} // makeshape
