// Copyright MakeShape. 2019, All rights reserved.

#include "kdtree2.hh"
#include "common.hh"
#include <array>
#include <limits>
#include <numeric>

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
            return (data < other.data);
        }
    };
    // deompose into each dimension
    std::vector<IndexData> x, y, z;
    const std::size_t N = indices.size();
    CHECK(N > 0);

    x.resize(N, {0, 0});
    y.resize(N, {0, 0});
    z.resize(N, {0, 0});
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

    // compute min range_axis
    double range_axis[3] = {0, 0, 0};
    range_axis[0] = x[N-1].data - x[0].data;
    range_axis[1] = y[N-1].data - y[0].data;
    range_axis[2] = z[N-1].data - z[0].data;

    printf("\t  range: {%f, %f, %f} | ", range_axis[0], range_axis[1], range_axis[2]);

    if (range_axis[0] > range_axis[1] ) {
        if (range_axis[0] > range_axis[2]) { // range_axis[0]
            return std::make_pair(SplitAxis::X, x.at(N/2).index);
        } else { // range_axis[2]
            return std::make_pair(SplitAxis::Z, z.at(N/2).index);
        }
    } else { // range_axis[1] < range_axis[0]
        if (range_axis[1] > range_axis[2]) { // range_axis[1]
            return std::make_pair(SplitAxis::Y, y.at(N/2).index);
        } else { // range_axis[2]
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
    const int n_rows = static_cast<int>(points.rows());
    CHECK(n_rows > 0);
    std::vector<Eigen::Vector3d> v(points.rows());
    for (int i = 0; i < points.rows(); ++i) {
        v[i] = points.row(i);
    }
    const auto pts = std::make_shared<const std::vector<Eigen::Vector3d>>(std::move(v));
    build(pts);
}

void KDTree2::build(std::shared_ptr<const std::vector<Eigen::Vector3d>> points) {
    CHECK(!points->empty());
    data_ = points;
    std::vector<std::size_t> indices(data_->size());
    std::iota(indices.begin(), indices.end(), 0);
    const auto axis_value = compute_axis_value(data_, indices);
    {
        int a = to_index(axis_value.first);
        CHECK(a >= 0 && a <= 2);
        const double v = data_->at(axis_value.second)[a];
        printf("\t axis: %i | value: %f\n", a, v);
    }
    const AABB box(Eigen::Vector3d(0.5, 0.5, 0.5), Eigen::Vector3d(1,1,1));
    root_ = build(std::get<0>(axis_value),  // axis
                  std::get<1>(axis_value),  // value (index of)
                  0,                        // current depth
                  indices,                  // domain
                  box,                      // bounding box
                  root_);                   // KDTree2
}
/*
Eigen::Vector3d KDTree2::nearest_neighbour(const Eigen::Vector3d &q) const {

}

Edges KDTree2::get_edges() const {


}
*/

KDTreeNode2 *KDTree2::build(const SplitAxis axis, 
                            const std::size_t value_index,
                            const std::size_t curr_depth,
                            const std::vector<std::size_t> &pt_indices,
                            const AABB &box,
                            KDTreeNode2 *n) const {
    if (pt_indices.empty()){
        return nullptr;
    }
    
    n = new KDTreeNode2{axis, value_index, nullptr, nullptr, box};
    IndexVec left_pt_indices, right_pt_indices;
    {
        const int a = to_index(axis);
        const double v = data_->at(value_index)[a];
        for(const auto &each_index : pt_indices) {
            if (each_index == value_index) {
                continue;
            }
            const double w = data_->at(each_index)[a];
            if (w < v) {
                left_pt_indices.push_back(each_index);
            } else {
                right_pt_indices.push_back(each_index);
            }
        }
    }
    CHECK(pt_indices.size()-1 == left_pt_indices.size() + right_pt_indices.size());


    const auto axis_value = compute_axis_value(data_, indices);
    {
        int a = to_index(axis_value.first);
        CHECK(a >= 0 && a <= 2);
        const double v = data_->at(axis_value.second)[a];
        printf("\t axis: %i | value: %f\n", a, v);
    }

    n->left = build(std::get<0>(axis_value),
                    std::get<1>(axis_value), 
                    curr_depth+1,
                    left_pt_indices,
                    box,
                    n->left);

    n->right = build(std::get<0>(axis_value),
                     std::get<1>(axis_value), 
                     curr_depth+1,
                     right_pt_indices,
                     box,
                     n->right);
    
    if (n->left == nullptr && n->right == nullptr) {
        n->points = pt_indices;
    }

    return n;

}


} // spatial 
} // makeshape
