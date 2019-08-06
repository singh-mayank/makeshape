// Copyright MakeShape. 2019, All rights reserved.

#include "kdtree.hh"
#include "common.hh"
#include <array>
#include <limits>
#include <numeric>
#include <list>

namespace makeshape {
namespace spatial {

namespace {
using PointVec = std::shared_ptr<const std::vector<Eigen::Vector3d>>;
using IndexVec = std::vector<size_t>;
using SplitAxis = KDTree::SplitAxis;

constexpr size_t KDTREE_MAX_DEPTH = 8u;
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

// return axis, value for split
std::pair<SplitAxis, double> compute_axis_value(
        const PointVec &data,
        const IndexVec &indices) {
    struct IndexData {
        size_t index;
        double data;
        bool operator<(const IndexData &other) const {
            return (data < other.data);
        }
    };
    // deompose into each dimension
    std::vector<IndexData> x, y, z;
    const size_t N = indices.size();
    CHECK(N > 0);

    x.resize(N, {0, 0});
    y.resize(N, {0, 0});
    z.resize(N, {0, 0});
    for (size_t i = 0; i < N; ++i) {
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

    if (range_axis[0] > range_axis[1] ) {
        if (range_axis[0] > range_axis[2]) { // range_axis[0]
            return std::make_pair(SplitAxis::X, range_axis[0]*0.5);
        } else { // range_axis[2]
            return std::make_pair(SplitAxis::Z, range_axis[2]*0.5);
        }
    } else { // range_axis[1] < range_axis[0]
        if (range_axis[1] > range_axis[2]) { // range_axis[1]
            return std::make_pair(SplitAxis::Y, range_axis[1]*0.5);
        } else { // range_axis[2]
            return std::make_pair(SplitAxis::Z, range_axis[2]*0.5);
        }
    }
}

std::pair<AABB, AABB> create_child_box(const KDTree::SplitAxis &axis, 
                                       const double &value, 
                                       const AABB &box) {
    Eigen::Vector3d center = box.center();
    Eigen::Vector3d extents = box.extents();
    Eigen::Vector3d minpt = box.min_pt();
    Eigen::Vector3d maxpt = box.max_pt();
    int index = to_index(axis);
    // compute center
    Eigen::Vector3d box_left_center = center;
    Eigen::Vector3d box_right_center = center;
    box_left_center[index]  = 0.5*(minpt[index] + value);
    box_right_center[index] = 0.5*(value + maxpt[index]);
    // compute extents
    Eigen::Vector3d box_left_extents = extents;
    Eigen::Vector3d box_right_extents = extents;
    box_left_extents[index]  = (value - minpt[index]);
    box_right_extents[index] = (maxpt[index] - value);
    return std::make_pair(
        AABB(box_left_center, box_left_extents),
        AABB(box_right_center, box_right_extents));
}   

} // namespace

KDTree::KDTree(size_t max_depth) 
    : max_depth_(std::min(KDTREE_MAX_DEPTH, max_depth)) {
    // do nothing
}

KDTree::~KDTree() {

}

void KDTree::build(const std::shared_ptr<std::vector<Eigen::Vector3d>> &points) {
    CHECK(!points->empty());
    data_ = points;
    std::vector<size_t> indices(data_->size());
    std::iota(indices.begin(), indices.end(), 0);
    AABB box(Eigen::Vector3d(0.5, 0.5, 0.5), Eigen::Vector3d(1, 1, 1));
    root_ = build(indices, 0, box);
}

std::pair<size_t, double> KDTree::nearest_neighbour(const Eigen::Vector3d &q) const {
    double curr_min_dist = std::numeric_limits<double>::infinity();
    size_t curr_min_index = 0;
    nns(q, root_, curr_min_dist, curr_min_index);
    CHECK(curr_min_index < data_->size());
    return std::make_pair(curr_min_index, curr_min_dist);
} 


Edges KDTree::get_edges() const {
    if (root_ == nullptr) {
        return Edges{};
    }
    // traverse all nodes
    std::vector<CubeEdges> ne;
    std::list<KDTree::KDTreeNode*> q;
    q.push_back(root_);
    while(!q.empty()){
        const KDTreeNode *curr = q.front();
        q.pop_front();
        if (curr == nullptr ){
            continue;
        }
        ne.emplace_back(get_cube_edges(curr->box));
        q.push_back(curr->left);
        q.push_back(curr->right);
    }
    return make_edges(ne);
}

KDTree::KDTreeNode *KDTree::build(const std::vector<size_t> &pt_indices, 
                                  const int &depth, 
                                  const AABB &box) const {
    if (pt_indices.empty() || depth >= max_depth_){
        return nullptr;
    }

    const auto axis_value  = compute_axis_value(data_, pt_indices);
    const int axis         = to_index(axis_value.first);
    const double value     = axis_value.second;
    {
        CHECK(axis >= 0 && axis <= 2);
        //std::string offset(depth, ' ');
        //common::dprintf("\t%s axis: %i | value: %f\n", offset.c_str(), axis, value);
    }

    KDTree::KDTreeNode *node = new KDTreeNode();
    node->axis = to_axis(axis);
    node->value = value;
    node->box = box;

    // split data for left/right children
    IndexVec left_pt_indices, right_pt_indices;
    {
        for(const auto &each_index : pt_indices) {
            const double w = data_->at(each_index)[axis];
            if (w <= value) {
                left_pt_indices.push_back(each_index);
            } else {
                right_pt_indices.push_back(each_index);
            }
        }
    }
    CHECK(pt_indices.size() == left_pt_indices.size() + right_pt_indices.size());
    const auto child_box = create_child_box(node->axis, node->value, box);
    node->left = build(left_pt_indices, depth+1, child_box.first);
    node->right = build(right_pt_indices, depth+1, child_box.second);
    if (node->left == nullptr && node->right == nullptr) {
        node->points = pt_indices;
    }
    return node;
}

void KDTree::nns(const Eigen::Vector3d &q,
                  const KDTreeNode *n,
                  double &current_distance, 
                  size_t &current_min_index) const
{
    if (n == nullptr) {
        return;
    }

    if (n->left == nullptr && n->right == nullptr) {
        CHECK(!n->points.empty());
        double min_distance = std::numeric_limits<double>::max();
        size_t min_index = 0;
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
    KDTreeNode *nearer_node;
    KDTreeNode *further_node;
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
