// Copyright MakeShape. 2019, All rights reserved.

#include "trimesh.hh"

#pragma warning( push )
#pragma warning( disable : 4018)
#pragma warning( disable : 4244)
#pragma warning( disable : 4996)
#pragma warning( disable : 4267)
#include <igl/readOBJ.h>
#include <igl/adjacency_list.h>
#pragma warning( pop ) 

#include <limits>

namespace {
  const Eigen::MatrixXd CUBE_VERTICES = (Eigen::MatrixXd(8,3)<<
    0.0,0.0,0.0,
    0.0,0.0,1.0,
    0.0,1.0,0.0,
    0.0,1.0,1.0,
    1.0,0.0,0.0,
    1.0,0.0,1.0,
    1.0,1.0,0.0,
    1.0,1.0,1.0).finished();
  const Eigen::MatrixXi CUBE_FACES = (Eigen::MatrixXi(12,3)<<
    1,7,5,
    1,3,7,
    1,4,3,
    1,2,4,
    3,8,7,
    3,4,8,
    5,7,8,
    5,8,6,
    1,5,6,
    1,6,2,
    2,6,8,
    2,8,4).finished().array()-1;
} // namespace

namespace makeshape {
namespace spatial {

TriMesh::TriMesh(const TriMesh &other) {
    v_ = other.const_vertices();
    f_ = other.const_faces();
}

TriMesh& TriMesh::operator=(const TriMesh& other) {
    if (this != &other) {
        v_ = other.const_vertices();
        f_ = other.const_faces();
    }
    return *this;
}

void TriMesh::build_adjacent_vertices(){ 
    igl::adjacency_list(f_, adj_vertices_); 
}

// rescale vertices between (0, 0, 0) and (1, 1, 1)
void TriMesh::rescale() {
    using Point = Eigen::Vector3d;
    Point min_pt, max_pt;
    min_pt[0] = min_pt[1] = min_pt[2] = std::numeric_limits<double>::max();
    max_pt[0] = max_pt[1] = max_pt[2] = std::numeric_limits<double>::min();
    const size_t rows = v_.rows();
    const size_t cols = v_.cols();
    for (size_t r = 0; r < rows; ++r) {
        for(size_t c = 0; c < 3; ++c) {
            min_pt[c] = std::min(min_pt[c], v_(r, c));
            max_pt[c] = std::max(max_pt[c], v_(r, c));
        }
    }

    Point range = (max_pt - min_pt);
    Point inv_range(1.0/range(0), 1.0/range(1), 1.0/range(2));
    for (size_t r = 0; r < rows; ++r) {
        for(size_t c = 0; c < 3; ++c) {
            v_(r, c) = inv_range(c) * (v_(r, c) - min_pt(c));
        }
    }
}


TriMesh load_mesh(const std::string &filename) {
    TriMesh m;
    igl::readOBJ(filename, m.vertices(), m.faces());
    return m;
}

TriMesh load_cube() {
    TriMesh m;
    m.vertices() = CUBE_VERTICES;
    m.faces() = CUBE_FACES;
    return m;
}

} // spatial 
} // makeshape
