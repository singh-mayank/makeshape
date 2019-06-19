// Copyright MakeShape. 2019, All rights reserved.

#include "aabb.hh"
#include "bsphere.hh"

#include <Eigen/Dense>

#pragma once

namespace makeshape {
namespace spatial {

bool intersects(const AABB &a1, const AABB &a2);
bool intersects(const BSphere &b1, const AABB &b2);
bool intersects(const AABB &a, const BSphere &b);

//
// TODO(mayank): Other intersections such as 
// ray/triangle
// ray/plane
// triangle/triangle
// closest point on triangle from point
// maybe rename file a more generic pair wise query
//


} // spatial 
} // makeshape
