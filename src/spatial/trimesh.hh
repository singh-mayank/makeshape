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
    const std::vector<std::vector<int>> adjacent_vertices() const { return adj_vertices_; } 
    Eigen::Vector3d centroid() const;
    const int64_t nv() const { return v_.rows(); }
    const int64_t nf() const { return f_.rows(); }
    const int64_t ne() const { return static_cast<int64_t>(e_.size()); }
    void rebuild();
    struct Edge {
        int64_t v1, v2;
    };
  private:
    void compute_rescale();
    void compute_adj_vertices();
    void compute_edges();
    Eigen::MatrixXd v_;
    Eigen::MatrixXi f_;
    std::vector<Edge> e_;
    std::vector<std::vector<int>> adj_vertices_;
    double scale_factor_{1.0};
};

TriMesh load_mesh(const std::string &filename);
TriMesh load_cube();

} // mesh
} // makeshape
