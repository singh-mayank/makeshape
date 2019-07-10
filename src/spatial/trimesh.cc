// Copyright MakeShape. 2019, All rights reserved.

#include "trimesh.hh"
#include "common.hh"

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
    v_ = other.vertices();
    f_ = other.faces();
	e_ = other.edges();
	adj_vertices_ = other.adjacent_vertices();
}

TriMesh::TriMesh(const TriMesh &&other) {
	v_ = std::move(other.vertices());
	f_ = std::move(other.faces());
	e_ = std::move(other.edges());
	adj_vertices_ = std::move(other.adjacent_vertices());
}

TriMesh& TriMesh::operator=(const TriMesh& other) {
    if (this != &other) {
        v_ = other.vertices();
        f_ = other.faces();
		e_ = other.edges();
		adj_vertices_ = other.adjacent_vertices();
    }
    return *this;
}

TriMesh& TriMesh::operator=(const TriMesh&& other) {
	if (this != &other) {
		v_ = std::move(other.vertices());
		f_ = std::move(other.faces());
		e_ = std::move(other.edges());
		adj_vertices_ = std::move(other.adjacent_vertices());
	}
	return *this;
}


Eigen::Vector3d TriMesh::centroid() const {
    Eigen::Vector3d centroid = v_.colwise().sum();
    centroid *= (1.0/static_cast<float>(v_.rows()));
    return centroid;
}

void TriMesh::rebuild() {
    compute_rescale();
    compute_adj_vertices();
    compute_edges();
    common::dprintf("Mesh: nv: %i, nf: %i, ne: %i\n", nv(), nf(), ne());
}

// rescale vertices between (0, 0, 0) and (1, 1, 1) 
void TriMesh::compute_rescale() {
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
    scale_factor_ = std::max(range[0], std::max(range[1], range[2]));
    for (size_t r = 0; r < rows; ++r) {
        for(size_t c = 0; c < 3; ++c) {
            v_(r, c) = (v_(r, c) - min_pt(c))/scale_factor_;
        }
    }
}

void TriMesh::compute_adj_vertices() { 
    igl::adjacency_list(f_, adj_vertices_); 
}

void TriMesh::compute_edges() {
    const int64_t nv = v_.rows();
    const int64_t nf = f_.rows();
    const int64_t ne = (nv + nf - 2);
    e_.reserve(ne);
    constexpr int64_t DIM = 3;
    for (int64_t f = 0; f < nf; ++f) {
        for (int64_t i = 0; i < DIM; ++i) {
            int64_t v0 = f_(f, i);
            int64_t v1 = f_(f, (i+1)%DIM);
            if (v0 < v1) {
                e_.emplace_back(Edge{v0, v1});
            }
        }
    }
}

TriMesh load_mesh(const std::string &filename) {
    TriMesh m;
    //TODO(mayank) -- update this so as to read obj, and ply files.
    igl::readOBJ(filename, m.mutable_vertices(), m.mutable_faces());
	m.rebuild();
	return std::move(m);
}

TriMesh	 load_cube() {
    TriMesh m;
    m.mutable_vertices() = CUBE_VERTICES;
    m.mutable_faces() = CUBE_FACES;
	m.rebuild();
	return std::move(m);
}

} // spatial 
} // makeshape
