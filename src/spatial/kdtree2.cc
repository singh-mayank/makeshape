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

double SQ(const double &x) {
    return (x) * (x);
}

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

    //printf("\t  range: {%f, %f, %f} | ", range_axis[0], range_axis[1], range_axis[2]);

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
    root_ = build(indices, 0);
}

std::pair<std::size_t, double> KDTree2::nearest_neighbour(const Eigen::Vector3d &q) const {
    double curr_min_dist = std::numeric_limits<double>::infinity();
    std::size_t curr_min_index = 0;
    nns(q, root_, curr_min_dist, curr_min_index);
    CHECK(curr_min_index < data_->size());
    return std::make_pair(curr_min_index, curr_min_dist);
}   

/*
Edges KDTree2::get_edges() const {


}
*/

KDTreeNode2 *KDTree2::build(const std::vector<std::size_t> &pt_indices, int depth) const {
    if (pt_indices.empty() || depth >= max_depth_){
        return nullptr;
    }

    const auto axis_value       = compute_axis_value(data_, pt_indices);
    const int axis              = to_index(axis_value.first);
    const std::size_t v_index   = axis_value.second;
    const double value          = data_->at(v_index)[axis];
    {
        CHECK(axis >= 0 && axis <= 2);
        //std::string offset(depth, ' ');
        //printf("\t%s axis: %i | value: %f\n", offset.c_str(), axis, value);
    }

    KDTreeNode2 *node = new KDTreeNode2();
    node->axis = to_axis(axis);
    node->value = value;

    // split data for left/right children
    IndexVec left_pt_indices, right_pt_indices;
    {
        for(const auto &each_index : pt_indices) {
            if (each_index == v_index) {
                continue;
            }
            const double w = data_->at(each_index)[axis];
            if (w <= value) {
                left_pt_indices.push_back(each_index);
            } else {
                right_pt_indices.push_back(each_index);
            }
        }
    }
    CHECK(pt_indices.size()-1 == left_pt_indices.size() + right_pt_indices.size());
    
    node->left = build(left_pt_indices, depth+1);
    node->right = build(right_pt_indices, depth+1);
    
    if (node->left == nullptr && node->right == nullptr) {
        node->points = pt_indices;
    }

    return node;
}

void KDTree2::nns(const Eigen::Vector3d &q,
                  const KDTreeNode2 *n,
                  double &current_distance, 
                  size_t &current_min_index) const
{
    if (n == nullptr) {
        return;
    }

    if (n->left == nullptr && n->right == nullptr) {
        CHECK(!n->points.empty());
        double min_distance = std::numeric_limits<double>::max();
        std::size_t min_index = 0;
        for (const auto each : n->points) {
            double d = (q - data_->at(each)).squaredNorm();
            if ( d < min_distance ) {
                min_distance = d;
                min_index = each;
            }
        }
        if(min_distance < current_distance) { 
            current_distance = min_distance;
            current_min_index = min_index;
        }
        return;
    }

    const double value = n->value;
    const SplitAxis axis = n->axis;
    KDTreeNode2 *nearer_node;
    KDTreeNode2 *further_node;
    if ( q[to_index(axis)] <= value) {
        nearer_node = n->left;
        further_node = n->right;
    } else {
        nearer_node = n->right;
        further_node = n->left;
    }

    nns(q, nearer_node, current_distance, current_min_index);

    if (SQ(q[to_index(axis)] - value) < current_distance) {
        nns(q, further_node, current_distance, current_min_index);
    }
}


} // spatial 
} // makeshape
