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
    const Eigen::Vector3d &center() const { return center_; }
    double radius() const { return radius_; }
    Eigen::Vector3d &mutable_center() { return center_; }
    double &mutable_radius() { return radius_; }
    double radius2() const { return radius_ * radius_; }
    bool inside(const Eigen::Vector3d &p);
  private:
    Eigen::Vector3d center_;
    double radius_;
}; // BSphere

//static BSphere build_bsphere(const Eigen::Matrixd &points);


} // spatial 
} // makeshape
