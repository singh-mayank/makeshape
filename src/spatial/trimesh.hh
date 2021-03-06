// Copyright MakeShape. 2019, All rights reserved.

#pragma once

#include <Eigen/Dense>
#include <vector>


namespace makeshape {
namespace spatial {

class TriMesh {
  public:
    struct Edge { // TODO(mayank): Replace this with edges.hh
        int64_t v0, v1;
    };
    TriMesh() { /* do nothing */ }
    TriMesh(const TriMesh& other);
	TriMesh(const TriMesh&& other);
    TriMesh& operator=(const TriMesh& other);
	TriMesh& operator=(const TriMesh&& other);
	Eigen::MatrixXd &mutable_vertices() { return v_; }
    Eigen::MatrixXi &mutable_faces() { return f_; }
    std::vector<Edge> &mutable_edges() { return e_; }
    const Eigen::MatrixXd &vertices() const{ return v_; }
    const Eigen::MatrixXi &faces() const{ return f_; }
    const std::vector<Edge> &edges() const{ return e_; }
    const std::vector<std::vector<int>> adjacent_vertices() const { return adj_vertices_; }
    Eigen::Vector3d centroid() const;
    const int64_t nv() const { return v_.rows(); }
    const int64_t nf() const { return f_.rows(); }
    const int64_t ne() const { return static_cast<int64_t>(e_.size()); }
    void rebuild();
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
