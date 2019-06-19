// Copyright MakeShape. 2019, All rights reserved.

#include <Eigen/Dense>

#pragma once

namespace makeshape {
namespace spatial {
//
// BSphere with center and radius
//
class BSphere {
  public:
    BSphere() : center_{Eigen::Vector3d(0, 0, 0)}, radius_{0.5} { }
    BSphere(const Eigen::Vector3d &c, const double r);
    BSphere(const BSphere &other);
    BSphere& operator=(const BSphere &other);
    const Eigen::Vector3d &const_center() const { return center_; }
    const double &const_radius() const { return radius_; }
    Eigen::Vector3d &center() { return center_; }
    double &radius() { return radius_; }
    double radius2() const { return radius_ * radius_; }
    bool include(const Eigen::Vector3d &p);
  private:
    Eigen::Vector3d center_;
    double radius_;
}; // BSphere

//static BSphere build_bsphere(const Eigen::Matrixd &points);


} // spatial 
} // makeshape
