// Copyright MakeShape. 2019, All rights reserved.

#include <Eigen/Dense>
#include <vector>

#pragma once

namespace makeshape {
namespace spatial {

class TriMesh {
  public:
    TriMesh() { /* do nothing */ }
    TriMesh(const TriMesh& other);
    TriMesh& operator=(const TriMesh& other);
    Eigen::MatrixXd &vertices() { return v_; }
    Eigen::MatrixXi &faces() { return f_; }
    const Eigen::MatrixXd &const_vertices() const{ return v_; }
    const Eigen::MatrixXi &const_faces() const{ return f_; }
    void build_adjacent_vertices();
    const std::vector<std::vector<int>> adjacent_vertices() const { return adj_vertices_; } 
    void rescale();
    Eigen::Vector3d centroid() const;
  private:
    Eigen::MatrixXd v_;
    Eigen::MatrixXi f_;
    std::vector<std::vector<int>> adj_vertices_;
};

TriMesh load_mesh(const std::string &filename);
TriMesh load_cube();

} // mesh
} // makeshape
