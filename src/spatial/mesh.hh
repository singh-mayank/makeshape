// Copyright MakeShape. 2019, All rights reserved.

#include <Eigen/Dense>
#include <vector>

#pragma once

namespace makeshape {
namespace spatial {

class Mesh {
  public:
    Mesh() { /* do nothing */ }
    Mesh(const Mesh& other);
    Mesh& operator=(const Mesh& other);
    Eigen::MatrixXd &vertices() { return v_; }
    Eigen::MatrixXi &faces() { return f_; }
    const Eigen::MatrixXd &const_vertices() const{ return v_; }
    const Eigen::MatrixXi &const_faces() const{ return f_; }
    void build_adjacent_vertices();
    const std::vector<std::vector<int>> adjacent_vertices() const { return adj_vertices_; } 
  private:
    Eigen::MatrixXd v_;
    Eigen::MatrixXi f_;
    std::vector<std::vector<int>> adj_vertices_;
};

Mesh load_mesh(const std::string &filename);
Mesh load_cube();

} // mesh
} // makeshape