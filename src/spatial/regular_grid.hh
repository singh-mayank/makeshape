// Copyright MakeShape. 2019, All rights reserved.
#include "edges.hh"
#include "aabb.hh"
#include <Eigen/Dense>
#include <vector>

#pragma once

namespace makeshape {
namespace spatial {

class RegularGrid {
  public:
    RegularGrid(const size_t max_depth);
    bool build();
  private:
    const size_t max_depth_;
}; // RegularGrid

} // spatial 
} // makeshape
