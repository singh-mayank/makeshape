// Copyright MakeShape. 2019, All rights reserved.

#include "kdtree.hh"
#include "common.hh"
#include <numeric>
#include <algorithm>
#include <list>
 
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

double value_at_axis(const Eigen::Vector3d &p, const SplitAxis &axis) {
    switch(axis) {
        case SplitAxis::X: return p.x(); break;
        case SplitAxis::Y: return p.y(); break;
        case SplitAxis::Z: return p.z(); break;
        default: CHECK(false);
    }
    return 0.0;
}


std::pair<AABB, AABB> compute_child_boxes(const SplitAxis n_axis, 
                                          const double half_value,
                                          const AABB &box) {
    AABB box_left;
    AABB box_right;
    {
        Eigen::Vector3d lcenter;
        Eigen::Vector3d rcenter;
        Eigen::Vector3d extents;

        double ex = box.extents().x();
        double ey = box.extents().y();
        double ez = box.extents().z();

        double cx = box.center().x();
        double cy = box.center().y();
        double cz = box.center().z();
    
        double s = 1;
        switch(n_axis) {
            case SplitAxis::X: 
                extents = Eigen::Vector3d(ex*0.5, ey, ez);
                lcenter = Eigen::Vector3d(cx - s*ex*0.25, cy, cz);
                rcenter = Eigen::Vector3d(cx + s*ex*0.25, cy, cz);
                break;
            case SplitAxis::Y: 
                extents = Eigen::Vector3d(ex, ey*0.5, ez);
                lcenter = Eigen::Vector3d(cx, cy - s*ey*0.25, cz);
                rcenter = Eigen::Vector3d(cx, cy + s*ey*0.25, cz);
                break;
            case SplitAxis::Z: 
                extents = Eigen::Vector3d(ex, ey, ez*0.5);
                lcenter = Eigen::Vector3d(cx, cy, cz - s*ez*0.25);
                rcenter = Eigen::Vector3d(cx, cy, cz + s*ez*0.25);
                break;
            default: CHECK(false);
        }
        box_left = AABB(lcenter, extents);
        box_right = AABB(rcenter, extents);
        // box_left.print(); box_right.print();
        //CHECK(value_at_axis(lcenter, n_axis) <= half_value);
        //CHECK(value_at_axis(rcenter, n_axis) > half_value);
    }



    return std::make_pair(box_left, box_right);
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
    constexpr double        START_VALUE = 1.0;
    constexpr std::size_t   START_DEPTH = 0u;
    AABB box(Eigen::Vector3d(0.5, 0.5, 0.5), Eigen::Vector3d(1, 1, 1));
    root_ = build(START_AXIS, START_VALUE, START_DEPTH, pts, box, root_);
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
                          const AABB &box,
                          KDTreeNode *n) const {
    if (pt_indices.empty()) {
        return nullptr;
    }
    
    if (depth >= max_depth_) {
        return new KDTreeNode{axis, value, nullptr, nullptr, box, pt_indices};
    } else {
        n = new KDTreeNode{axis, value, nullptr, nullptr, box, std::vector<std::size_t>{}};
    }

#if 0
    for(const auto &each : pt_indices) {
        Eigen::Vector3d pt = data_->at(each);
        if(!box.inside(pt)) {
            printf("\t p: {%f, %f, %f} | value: %f | axis: %i\n", 
                    pt[0], pt[1], pt[2], value, to_index(axis));
            box.print_minmax();
            //CHECK(false);
        }
    }
#endif

    const auto n_axis = next_axis(axis);
    const auto half_value = 0.5 * value;
    const std::size_t N = pt_indices.size();
    std::vector<std::size_t> lpts;
    std::vector<std::size_t> rpts;
    { // split points for left and right children
        lpts.reserve(N/2);
        rpts.reserve(N/2);
        for (std::size_t i = 0; i < N; ++i) {
            std::size_t pt_index = pt_indices.at(i);
            Eigen::Vector3d pt = data_->at(pt_index);
            double pt_value = value_at_axis(pt, n_axis);
            if (pt_value <= half_value) {
                lpts.push_back(pt_index);
            } else {
                rpts.push_back(pt_index);
            }
        }
    }
    const auto child_boxes = compute_child_boxes(n_axis, half_value, box);
    n->left  = build(n_axis, half_value, depth+1, lpts, child_boxes.first, n->left);
    n->right = build(n_axis, half_value, depth+1, rpts, child_boxes.second, n->right);
    return n;
}

#if 1
void KDTree::nns(const Eigen::Vector3d &q, 
                 const KDTreeNode *n, 
                 double &curr_distance,
                 std::size_t &nearest_pt) const {
    if (n == nullptr) {
        return;
    }
    if (n->left == nullptr && n->right == nullptr) {
        CHECK(!n->points.empty());
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
#else
void KDTree::nns(const Eigen::Vector3d &q, 
                 const KDTreeNode *n, 
                 double &curr_distance,
                 std::size_t &nearest_pt) const {
    if (n == nullptr) {
        return;
    }
    if (n->left == nullptr && n->right == nullptr) {
        CHECK(!n->points.empty());
        for (const auto each : n->points) {
            double d = (q - data_->at(each)).squaredNorm();
            if ( d < curr_distance ) {
                curr_distance = d;
                nearest_pt = each;
            }
        }
    }
}
#endif


Edges KDTree::get_edges() const {
    Edges e;
    std::vector<CubeEdges> ne;
    std::list<KDTreeNode*> q;
    q.push_back(root_);
    while(!q.empty()){
        const KDTreeNode *curr = q.front();
        q.pop_front();
        if (curr == nullptr) {
            continue;
        }
        ne.emplace_back(get_cube_edges(curr->box));
        q.push_back(curr->left);
        q.push_back(curr->right);
    }
    return make_edges(ne);
}


} // spatial 
} // makeshape
