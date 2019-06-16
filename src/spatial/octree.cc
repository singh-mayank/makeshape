// Copyright MakeShape. 2019, All rights reserved.

#include "octree.hh"
#include "common.hh"
#include <cstdlib>
#include <cstdio>
#include <list>
#include <array>

#include <cassert>
 
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
    const Point min_pt = n->center - n->extents;
    const Point max_pt = n->center + n->extents;
    for(size_t i = 0; i < DIM; ++i) {
        if (p[i] < min_pt[i]) { return false; }
        if (p[i] > max_pt[i]) { return false; }
    }
    return true;
}

size_t compute_child_index(const OctreeNode *n, const Point &p) {
    size_t index = 0;
    const auto c = n->center;
    const auto e = n->extents;
    for (size_t i = 0; i < DIM; ++i) {
        const auto x = (p[i] - (c[i] - 0.5*e[i]))/e[i];
        if( std::round(x) ) {
            index |= (1ULL << i);
        }
    }
    return index;
}

std::pair<Point, Point> compute_center_and_extents(const OctreeNode* n, const size_t child_index) {
    Point center;
    const Point extents = 0.5*n->extents;
    for (size_t i = 0; i < DIM; ++i) {
        center[i] = (child_index & (1ULL << i))? 
            n->center[i] + 0.5*extents[i] : n->center[i] - 0.5*extents[i];
    }
    return std::make_pair(center, extents);
}


OctreeNode* insert(OctreeNode *n, 
        const Point &p, 
        const Point &center, 
        const Point &extents, 
        const size_t curr_depth, 
        const size_t max_depth) {
    CHECK (curr_depth <= max_depth);
    if (n == nullptr) {
        n = new OctreeNode(center, extents);
    }
    if (curr_depth == max_depth) {
        n->points.push_back(p);
    } else {
        const size_t index = compute_child_index(n, p); 
        Point child_center, child_extents;
        if (n->child[index] == nullptr) {
            const auto center_and_extents = compute_center_and_extents(n, index);
            child_center = center_and_extents.first;
            child_extents = center_and_extents.second;
        } 
        n->child[index] = insert(n->child[index], 
                p, 
                child_center, 
                child_extents, 
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
        clear_tree(n->child[i]);
        delete n->child[i];
        n->child[i] = nullptr;  
    }
    n->points.clear();
}

size_t count_nodes(const OctreeNode *n) {
    if (n == nullptr) {
        return 0;
    }
    size_t c = 1;
    for(int i = 0; i < OctreeNode::MAX_CHILDREN; ++i) {
        c += count_nodes(n->child[i]);
    }
    return c;
}

NodeEdges get_node_edges(const OctreeNode *n) {
    NodeEdges ne;
    {
        Point min_pt{n->center - 0.5*n->extents};       
        Point max_pt{n->center + 0.5*n->extents};
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

} // namespace

OctreeNode::OctreeNode() {
    OctreeNode(Eigen::Vector3d(0.5, 0.5, 0.5), Eigen::Vector3d(1, 1, 1));
}
OctreeNode::OctreeNode(const Eigen::Vector3d& c, const Eigen::Vector3d& e) {
    center = c;
    extents = e;
    for(size_t i = 0; i < MAX_CHILDREN; ++i) {
        child[i] = nullptr;
    }
}

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

bool Octree::build(const std::vector<Eigen::Vector3d> &points) {
    if (points.empty() || max_depth_ < 0 || max_depth_ > 8) {
        return false;
    }

    if (root_ != nullptr) {
        clear_tree(root_);
        delete root_;
        root_ = nullptr;
    }

    const Point center(0.5, 0.5, 0.5);
    const Point extents(1, 1, 1);
    const size_t nv = points.size();
    for (size_t i = 0; i < nv; ++i) {
        const Point &p = points[i]; 
        root_ = insert(root_, p, center, extents, 0, max_depth_);
    }
    return true;
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
    for (int i = 0; i < rows; ++i) {
        Point p;
        for(int j = 0; j < DIM; ++j){
            p(j) = points(i, j); 
        }
        root_ = insert(root_, p, center, extents, 0, max_depth_);
    }

    return true;
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
            if (curr->child[i] != nullptr) {
                q.push_back(curr->child[i]);
            }
        }
    }
    Edges e;
    {
        // vertices
        e.P.resize(ne.size()*N_VERTICES, DIM);
        for (size_t i = 0; i < ne.size(); ++i) {
            for(size_t j = 0; j < N_VERTICES; ++j) {
                for(size_t k = 0; k < DIM; ++k) {
                    e.P(N_VERTICES * i + j, k) = ne[i].v[j][k];
                }
            }
        }
        // edges
        constexpr size_t VERTICES_PER_EDGE = 2;
        e.E.resize(ne.size()*N_EDGES, VERTICES_PER_EDGE); // 2 vertices per edge
        for (size_t i = 0; i < ne.size(); ++i) {
            for(size_t j = 0; j < N_EDGES; ++j) {
                e.E(N_EDGES * i + j, 0) = ne[i].e[j].first;
                e.E(N_EDGES * i + j, 1) = ne[i].e[j].second;
            }
        }
        e.C.resize(1, 3);
        e.C(0, 0) = 1;
        e.C(0, 1) = 1;
        e.C(0, 2) = 1;
    }
    return e;
}


} // spatial 
} // makeshape
