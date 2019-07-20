// Copyright MakeShape. 2019, All rights reserved.

#include "kdtree2.hh"
#include <array>
#include <limits>

namespace makeshape {
namespace spatial {

namespace {
using PointVec = std::shared_ptr<const std::vector<Eigen::Vector3d>>;
using IndexVec = std::vector<std::size_t>;

constexpr std::size_t KDTREE_MAX_DEPTH = 8u;
constexpr int DIM = 3;

SplitAxis to_axis(const int index) {
    return static_cast<SplitAxis>(index);
}

int to_index(const SplitAxis axis) {
    return static_cast<int>(axis);
}


std::pair<SplitAxis, std::size_t> compute_axis_value(
        const PointVec &data,
        const IndexVec &indices) {
    struct IndexData {
        std::size_t index;
        double data;
        bool operator<(const IndexData &other) const {
            data < other.data;
        }
    };
    // deompose into each dimension
    std::vector<IndexData> x, y, z;
    const std::size_t N = indices.size();
    x.resize(N);
    y.resize(N);
    z.resize(N);
    for (std::size_t i = 0; i < N; ++i) {
        x[i].index = y[i].index = z[i].index = indices.at(i);
        const Eigen::Vector3d &p = data->at(indices.at(i));
        x[i].data = p.x();
        y[i].data = p.y();
        z[i].data = p.z();
    }
    // sort by each dimension
    std::sort(x.begin(), x.end());
    std::sort(y.begin(), y.end());
    std::sort(z.begin(), z.end());
    // compute min range
    double range[3];
    range[0] = x[N-1].data - x[0].data;
    range[1] = y[N-1].data - y[0].data;
    range[2] = z[N-1].data - z[0].data;

    if (range[0] < range[1] ) {
        if (range[0] < range[2]) { // range[0]
            return std::make_pair(SplitAxis::X, x.at(N/2).index);
        } else { // range[2]
            return std::make_pair(SplitAxis::Z, z.at(N/2).index);
        }
    } else { // range[1] < range[0]
        if (range[1] < range[2]) { // range[1]
            return std::make_pair(SplitAxis::Y, y.at(N/2).index);
        } else { // range[2]
            return std::make_pair(SplitAxis::Z, z.at(N/2).index);
        }
    }
}
} // namespace

KDTree2::KDTree2(std::size_t max_depth) 
    : max_depth_(std::min(KDTREE_MAX_DEPTH, max_depth)) {
    // do nothing
}

KDTree2::~KDTree2() {

}

void KDTree2::build(const Eigen::MatrixXd &points) {
    const int n_rows = points.rows();
    if (n_rows < 1) {
        return;
    }
    std::vector<Eigen::Vector3d> v(points.rows());
    for (int i = 0; i < points.rows(); ++i) {
        v[i] = points.row(i);
    }
    const auto pts = std::make_shared<const std::vector<Eigen::Vector3d>>(std::move(v));
    build(pts);
}

void KDTree2::build(std::shared_ptr<const std::vector<Eigen::Vector3d>> points) {
    if (points->empty()) {
        return;
    }
    data_ = points;
    std::vector<std::size_t> indices;
    std::iota(indices.begin(), indices.end(), 0);
    const auto axis_value = compute_axis_value(data_, indices);
    const AABB box(Eigen::Vector3d(0.5, 0.5, 0.5), Eigen::Vector3d(1,1,1));
    root_ = build(std::get<0>(axis_value),  // axis
                  std::get<1>(axis_value),  // value (index of)
                  0,                        // current depth
                  indices,                  // domain
                  box,                      // bounding box
                  root_);                   // KDTree2
}


} // spatial 
} // makeshape
