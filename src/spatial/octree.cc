// Copyright MakeShape. 2019, All rights reserved.

#include "octree.hh"
#include "bsphere.hh"
#include "intersections.hh"
#include "common.hh"
#include <cstdlib>
#include <cstdio>
#include <list>
#include <array>
#include <queue>
 
namespace makeshape {
namespace spatial {
namespace {

using Point = Eigen::Vector3d;
using VertexPair = std::pair<Point, Point>;
constexpr size_t DIM = 3;
constexpr size_t N_VERTICES = 8;
constexpr size_t N_EDGES = 12;
constexpr size_t MAX_DEPTH = 8;

struct NodeEdges {
    std::array<Point, N_VERTICES> v;
    std::array<std::pair<int, int>, N_EDGES> e;
};

bool inside(const OctreeNode *n, const Point &p) {
    const Point min_pt = n->min_pt();
    const Point max_pt = n->max_pt();
    for(size_t i = 0; i < DIM; ++i) {
        if (p[i] < min_pt[i]) { return false; }
        if (p[i] > max_pt[i]) { return false; }
    }
    return true;
}

size_t compute_child_index(const OctreeNode *n, const Point &p) {
    size_t index = 0;
    const Eigen::Vector3d c = n->box_.center();
    const Eigen::Vector3d e = n->box_.extents();
    for (size_t i = 0; i < DIM; ++i) {
        const auto x = (p[i] - (c[i] - 0.5*e[i]))/e[i];
        if( std::round(x) ) {
            index |= (1ULL << i);
        }
    }
    return index;
}

AABB compute_child_aabb(const OctreeNode* n, const size_t child_index) {
    Point child_center;
    const Point child_extents = 0.5*n->box_.extents();
    const Point center = n->box_.center();
    for (size_t i = 0; i < DIM; ++i) {
        child_center[i] = (child_index & (1ULL << i))? 
            center[i] + 0.5*child_extents[i] : 
            center[i] - 0.5*child_extents[i];
    }
    return AABB(child_center, child_extents);
}


OctreeNode* insert(OctreeNode *n, 
        const Point &p, 
        const AABB &box,
        const size_t curr_depth, 
        const size_t max_depth) {
    CHECK (curr_depth <= max_depth);
    if (n == nullptr) {
        n = new OctreeNode(box, curr_depth);
    }
    if (curr_depth == max_depth) {
        n->points_.push_back(p);
    } else {
        const size_t index = compute_child_index(n, p); 
        AABB child_box;
        if (n->child_[index] == nullptr) {
            child_box = compute_child_aabb(n, index);
        } 
        n->child_[index] = insert(n->child_[index], 
                p, 
                child_box,
                curr_depth+1, 
                max_depth);
    }
    return n;
}

void clear_tree(OctreeNode *n) {
    if(n == nullptr) {
        return;
    } 
    for(int i = 0; i < OctreeNode::MAX_CHILDREN; ++i) {
        clear_tree(n->child_[i]);
        delete n->child_[i];
        n->child_[i] = nullptr;  
    }
    n->points_.clear();
}

size_t count_nodes(const OctreeNode *n) {
    if (n == nullptr) {
        return 0;
    }
    size_t c = 1;
    for(int i = 0; i < OctreeNode::MAX_CHILDREN; ++i) {
        c += count_nodes(n->child_[i]);
    }
    return c;
}

NodeEdges get_node_edges(const OctreeNode *n) {
    NodeEdges ne;
    {
        Point min_pt = n->min_pt();
        Point max_pt = n->max_pt();
        // bottom
        ne.v[0] = min_pt;
        ne.v[1] = Point(max_pt[0], min_pt[1], min_pt[2]);
        ne.v[2] = Point(max_pt[0], max_pt[1], min_pt[2]);
        ne.v[3] = Point(min_pt[0], max_pt[1], min_pt[2]);
        // top
        ne.v[4] = Point(min_pt[0], min_pt[1], max_pt[2]);
        ne.v[5] = Point(max_pt[0], min_pt[1], max_pt[2]);
        ne.v[6] = max_pt;
        ne.v[7] = Point(min_pt[0], max_pt[1], max_pt[2]);

        ne.e[0] = std::make_pair(0, 1);
        ne.e[1] = std::make_pair(1, 2);
        ne.e[2] = std::make_pair(2, 3);
        ne.e[3] = std::make_pair(3, 0);

        ne.e[4] = std::make_pair(4, 5);
        ne.e[5] = std::make_pair(5, 6);
        ne.e[6] = std::make_pair(6, 7);
        ne.e[7] = std::make_pair(7, 4);

        ne.e[8]  = std::make_pair(0, 4);
        ne.e[9]  = std::make_pair(1, 5);
        ne.e[10] = std::make_pair(2, 6);
        ne.e[11] = std::make_pair(3, 7);
    }
    return ne;
}

void print(const OctreeNode *n) {
    Point min_pt = n->min_pt();
    Point max_pt = n->max_pt();
    Eigen::Vector3d extents = max_pt - min_pt;
    double vol = (extents[0] * extents[1] * extents[2]);
    const std::string indent(2*n->depth_, ' ');
    printf("%s %zu | [%f, %f, %f] --> [%f, %f, %f] [%f] | %zu\n", 
            indent.c_str(),
            n->depth_,
            min_pt[0], min_pt[1], min_pt[2],
            max_pt[0], max_pt[1], max_pt[2], 
            vol,
            n->points_.size());

}

} // namespace

//
// OctreeNode
//
OctreeNode::OctreeNode() {
    OctreeNode(AABB(Eigen::Vector3d(0.5, 0.5, 0.5), Eigen::Vector3d(1, 1, 1)), 0);
}

OctreeNode::OctreeNode(const AABB &box, const size_t depth) {
    box_ = box;
    for(size_t i = 0; i < MAX_CHILDREN; ++i) {
        child_[i] = nullptr;
    }
    depth_ = depth;
}


//
// Octree
//
Octree::Octree(const size_t max_depth) 
    : root_(nullptr)
    , max_depth_(max_depth) {
    // do nothing
}

Octree::~Octree() {
    if (root_ != nullptr) {
        clear_tree(root_);
        delete root_;
        root_ = nullptr;
    }
}

size_t Octree::num_nodes() const {
    return count_nodes(root_);
}

Edges Octree::get_edges() const {
    if (root_ == nullptr) {
        return Edges{};
    }
    // traverse all nodes
    std::vector<NodeEdges> ne;
    std::list<OctreeNode*> q;
    q.push_back(root_);
    while(!q.empty()){
        const OctreeNode *curr = q.front();
        q.pop_front();
        ne.emplace_back(get_node_edges(curr));
        for(size_t i = 0; i < OctreeNode::MAX_CHILDREN; ++i) {
            if (curr->child_[i] != nullptr) {
                q.push_back(curr->child_[i]);
            }
        }
    }
    // build edges
    Edges e;
    {
        // vertices
        e.P.resize(ne.size()*N_VERTICES, DIM);
        for (size_t i = 0; i < ne.size(); ++i) {
            for(size_t j = 0; j < N_VERTICES; ++j) {
                const size_t index = i*N_VERTICES + j;
                for(size_t k = 0; k < DIM; ++k) {
                    e.P(index, k) = ne[i].v[j][k];
                }
            }
        }
        // edges 
        constexpr size_t VERTICES_PER_EDGE = 2;
        e.E.resize(ne.size()*N_EDGES, VERTICES_PER_EDGE); // 2 vertices per edge
        for (size_t i = 0; i < ne.size(); ++i) {
            const size_t offset = i*N_EDGES;
            for(size_t j = 0; j < N_EDGES; ++j) {
                int row = static_cast<int>(offset + j);
                int ii = static_cast<int>(i * 8);
                e.E(row, 0) = ne[i].e[j].first + (ii);
                e.E(row, 1) = ne[i].e[j].second + (ii);
            }
        }
        // color
        e.C.resize(1, 3);
        e.C(0, 0) = 1;
        e.C(0, 1) = 1;
        e.C(0, 2) = 1;
        // print debug
        // {
        //     for (size_t i = 0; i < ne.size(); ++i) {
        //         for(size_t j = 0; j < N_VERTICES; ++j) {
        //             const size_t index = i*N_VERTICES + j;
        //             printf("[%zu]: [%f, %f, %f]\n",
        //                     index,
        //                     e.P(index, 0),
        //                     e.P(index, 1),
        //                     e.P(index, 2));
        //         }
        //     }
        //
        //     for (size_t i = 0; i < ne.size(); ++i) {
        //         for(size_t j = 0; j < N_EDGES; ++j) {
        //             const size_t index = i*N_EDGES + j;
        //             printf("[%zu]: [%i, %i]\n",
        //                     index,
        //                     e.E(index, 0),
        //                     e.E(index, 1));
        //         }
        //     }
        // }
    }
    return e;
}

bool Octree::build(const Eigen::MatrixXd &points) {
    const size_t rows = points.rows();
    const size_t cols = points.cols();
    assert(cols == DIM);
    if (rows == 0 || max_depth_ < 0 || max_depth_ > MAX_DEPTH) {
        return false;
    }

    // clear memory, if needed
    if (root_ != nullptr) {
        clear_tree(root_);
        delete root_;
        root_ = nullptr;
    }

    const Point center(0.5, 0.5, 0.5);
    const Point extents(1, 1, 1);
    const AABB box(center, extents);
    for (int i = 0; i < rows; ++i) {
        Point p;
        for(int j = 0; j < DIM; ++j){
            p(j) = points(i, j); 
        }
        root_ = insert(root_, p, box, 0, max_depth_);
    }

    return true;
}

const Eigen::MatrixXd Octree::neighbours(const Eigen::Vector3d &p, const double radius) {
    const double r2 = (radius * radius);
    BSphere bsp(p, radius);   
    std::vector<Eigen::Vector3d> pts;
    std::queue<OctreeNode*> q;
    q.push(root_);
    while (!q.empty()) {
        const auto curr_node = q.front();
        q.pop();
        if (curr_node == nullptr ){
            continue;
        }

        if (intersects(curr_node->box_, bsp)) {
            if (curr_node->points_.empty()) {
                for (size_t i=0; i<OctreeNode::MAX_CHILDREN; ++i) {
                    q.push(curr_node->child_[i]);
                }
            } else {
                for (const Eigen::Vector3d &each_p : curr_node->points_) {
                    if ((each_p - p).squaredNorm() < r2) {
                        pts.emplace_back(each_p);
                    }
                }
            }
        }
    }

    // convert points to matrix
    Eigen::MatrixXd ret(pts.size(), 3);
    for(size_t i = 0; i < pts.size(); ++i) {
        ret.row(i) = pts.at(i);
    }
    return ret;
}


} // spatial 
} // makeshape
