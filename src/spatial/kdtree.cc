// Copyright MakeShape. 2019, All rights reserved.

#include "kdtree.hh"
#include "common.hh"
#include <numeric>
#include <algorithm>
 
namespace makeshape {
namespace spatial {
namespace {
    // do nothing
#if 0
    SplitAxis to_split = SplitAxis::X;
    // compute split axis
    {
        std::vector<std::size_t> sort_x(N);
        std::vector<std::size_t> sort_y(N);
        std::vector<std::size_t> sort_z(N);
        std::iota(sort_x.begin(), sort_x.end(), 0);
        std::iota(sort_y.begin(), sort_y.end(), 0);
        std::iota(sort_z.begin(), sort_z.end(), 0);

        auto sort_by_axis = [&points](const SplitAxis axis, 
                std::vector<size_t> &data){
            int index = static_cast<int>(axis);
            std::sort(data.begin(), data.end(), [&points, &index](
                const std::size_t a, const std::size_t b) -> bool {
                    return (points->at(a)[index] < points->at(b)[index]);
            });
        };
    
        auto compute_range = [&points, &N](const SplitAxis axis,
                const std::vector<size_t> &d) -> double {
            const int index = static_cast<int>(axis);
            return points->at(d[N-1])[index] - points->at(d[0])[index];
        };

        auto compute_split_axis = [](const double rx, 
                const double ry, 
                const double rz) -> int {
            if (rx > ry && rx > rx) { return 0u; }
            else if (ry > rx && ry > rx) { return 1u; }
            else { return 2u; }
        };

        sort_by_axis(SplitAxis::X, sort_x);
        sort_by_axis(SplitAxis::Y, sort_y);
        sort_by_axis(SplitAxis::Z, sort_z);
        const double range_x = compute_range(SplitAxis::X, sort_x);
        const double range_y = compute_range(SplitAxis::Y, sort_y);
        const double range_z = compute_range(SplitAxis::Z, sort_z);
        to_split = static_cast<SplitAxis>(compute_split_axis(range_x, 
                    range_y, range_z));
    }
#endif

constexpr std::size_t MAX_KDTREE_DEPTH = 8u;

SplitAxis to_axis(const int index) {
    return static_cast<SplitAxis>(index);
}

int to_index(const SplitAxis axis) {
    return static_cast<int>(axis);
}

SplitAxis next_axis(const SplitAxis axis) {
    return to_axis((to_index(axis) + 1) % 3);
}


}

KDTree::KDTree(const std::size_t max_depth) 
    : max_depth_(std::min(MAX_KDTREE_DEPTH, max_depth)) {
    // do nothing
}

KDTree::~KDTree() {
    // TODO(mayank) : finish this
}

void KDTree::build(std::shared_ptr<const std::vector<Eigen::Vector3d>> points) {
    CHECK(!points->empty());
    data_ = points;
    const std::size_t N = data_->size();
    std::vector<std::size_t> pts(N);
    std::iota(pts.begin(), pts.end(), 0);
    constexpr SplitAxis     START_AXIS = SplitAxis::X;
    constexpr double        START_VALUE = 0.5;
    constexpr std::size_t   START_DEPTH = 0u;
    root_ = build(START_AXIS, START_VALUE, START_DEPTH, pts, root_);
    CHECK(root_ != nullptr);
}

Eigen::Vector3d KDTree::nearest_neighbour(const Eigen::Vector3d &q) const {
    CHECK(root_ != nullptr);
    double curr_dist = std::numeric_limits<double>::infinity();
    std::size_t nearest_pt = 0;
    nns(q, root_, curr_dist, nearest_pt);
    return (data_->at(nearest_pt));
}

//std::vector<std::size_t> KDTree::nearest_n_neighbours(const Eigen::Vector3d &q, 
                                                      //const std::size_t n) const {

//}

KDTreeNode *KDTree::build(const SplitAxis axis, 
                          const double value,
                          const std::size_t depth,
                          const std::vector<std::size_t> &pt_indices,
                          KDTreeNode *n) const {
    if (pt_indices.empty()) {
        return nullptr;
    }
    
    if (n == nullptr) {
        n = new KDTreeNode{axis, 0.0, nullptr, nullptr};
    }
 
    if (depth >= max_depth_) {
        n->points = pt_indices;
        return n;
    }

    const std::size_t N = pt_indices.size();
    std::vector<std::size_t> lpts;
    std::vector<std::size_t> rpts;
    { // split points for left and right children
        lpts.reserve(N/2);
        rpts.reserve(N/2);
        for (std::size_t i = 0; i < N; ++i) {
            std::size_t pt_index = pt_indices[i];
            if (data_->at(pt_index)[to_index(axis)] < value) {
                lpts.push_back(pt_index);
            } else {
                rpts.push_back(pt_index);
            }
        }
    }
    n->left  = build(next_axis(axis), 0.5*value, depth+1, lpts, n->left);
    n->right = build(next_axis(axis), 0.5*value, depth+1, rpts, n->right);
    return n;
}


void KDTree::nns(const Eigen::Vector3d &q, 
                 const KDTreeNode *n, 
                 double &curr_distance,
                 std::size_t &nearest_pt) const {
    if (n == nullptr) {
        return;
    }
    if (n->left == nullptr && n->right == nullptr) {
        for (const auto each : n->points) {
            double d = (q - data_->at(each)).squaredNorm();
            if ( d < curr_distance ) {
                curr_distance = d;
                nearest_pt = each;
            }
        }
    } else {
        KDTreeNode *search_first = nullptr;
        const auto index = to_index(n->axis);
        if ( q[index] <= n->value ) {
            search_first = n->left;
        } else {
            search_first = n->right;
        }
        if (search_first == n->left ) {
            if (q[index] - curr_distance <= n->value ) {
                nns(q, n->left, curr_distance, nearest_pt);
            }
            if (q[index] + curr_distance > n->value ) {
                nns(q, n->right, curr_distance, nearest_pt);
            }
        } else { // search_first == n->right
            if (q[index] + curr_distance > n->value ) {
                nns(q, n->right, curr_distance, nearest_pt);
            }
            if (q[index] - curr_distance <= n->value ) {
                nns(q, n->left, curr_distance, nearest_pt);
            }
        }
    }
}

Edges KDTree::get_edges() const {
    Edges e;
    return e;
}


} // spatial 
} // makeshape
