// Copyright MakeShape. 2019, All rights reserved.

#include "mesh.hh"

namespace mesh {

Mesh Mesh::deep_copy() const {
    Mesh m;
    m.vertices() = const_vertices();
    m.faces() = const_faces();
    return m;
}

} // namespace mesh
