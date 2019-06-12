// Copyright MakeShape. 2019, All rights reserved.

#include "mesh.hh"

#include <igl/readOBJ.h>

namespace makeshape {
namespace mesh {

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

Mesh Mesh::deep_copy() const {
    Mesh m;
    m.vertices() = const_vertices();
    m.faces() = const_faces();
    return m;
}

Mesh load_mesh(const std::string &filename) {
    Mesh m;
    igl::readOBJ(filename, m.vertices(), m.faces());
    return m;
}

Mesh load_cube() {
    Mesh m;
    m.vertices() = CUBE_VERTICES;
    m.faces() = CUBE_FACES;
    return m;
}

} // mesh
} // makeshape
