// Copyright MakeShape. 2019, All rights reserved.

#include "aabb.hh"
#include "edges.hh"

namespace makeshape {
namespace spatial {

AABB::AABB(const Eigen::Vector3d &c, const Eigen::Vector3d &e) {
    center_ = c;
    extents_ = e;
}

AABB::AABB(const AABB &other) {
    center_ = other.center();
    extents_ = other.extents();
}

AABB& AABB::operator=(const AABB &other) {
    if (this != &other) {
        center_ = other.center();
        extents_ = other.extents();
    }
    return *this;
}

bool AABB::inside(const Eigen::Vector3d &p) {
    using Vec3 = Eigen::Vector3d;
    const Vec3 minpt = min_pt();
    const Vec3 maxpt = max_pt();
    return ((p(0) >= minpt(0) && p(0) <= maxpt(0)) && 
            (p(1) >= minpt(1) && p(1) <= maxpt(1)) && 
            (p(2) >= minpt(2) && p(2) <= maxpt(2)));
}

Edges get_edges(const AABB &box) {
    using Vec3d = Eigen::Vector3d;
    using Vec2i = Eigen::Vector2i;
    static constexpr int DIM = 3;
    static constexpr int N_VERTICES = 8;
    static constexpr int N_EDGES = 12;
    static constexpr size_t VERTICES_PER_EDGE = 2;
    Edges e;
    {
        e.P.resize(N_VERTICES, DIM);
        Vec3d min_pt = box.min_pt();
        Vec3d max_pt = box.max_pt();
        // bottom
        e.P.row(0) = min_pt;
        e.P.row(1) = Vec3d{max_pt[0], min_pt[1], min_pt[2]};
        e.P.row(2) = Vec3d{max_pt[0], max_pt[1], min_pt[2]};
        e.P.row(3) = Vec3d{min_pt[0], max_pt[1], min_pt[2]};
        // top
        e.P.row(4) = Vec3d{min_pt[0], min_pt[1], max_pt[2]};
        e.P.row(5) = Vec3d{max_pt[0], min_pt[1], max_pt[2]};
        e.P.row(6) = max_pt;
        e.P.row(7) = Vec3d{min_pt[0], max_pt[1], max_pt[2]};
    }
    {
        e.E.resize(N_EDGES, VERTICES_PER_EDGE);
        e.E.row(0)  = Vec2i{0, 1};
        e.E.row(1)  = Vec2i{1, 2};
        e.E.row(2)  = Vec2i{2, 3};
        e.E.row(3)  = Vec2i{3, 0};
        e.E.row(4)  = Vec2i{4, 5};
        e.E.row(5)  = Vec2i{5, 6};
        e.E.row(6)  = Vec2i{6, 7};
        e.E.row(7)  = Vec2i{7, 4};
        e.E.row(8)  = Vec2i{0, 4};
        e.E.row(9)  = Vec2i{1, 5};
        e.E.row(10) = Vec2i{2, 6};
        e.E.row(11) = Vec2i{3, 7};
    }

    return e;
}

} // spatial 
} // makeshape
