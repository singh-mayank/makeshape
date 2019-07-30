// Copyright MakeShape. 2019, All rights reserved.

#include "app.hh"
#include "kdtree.hh"
#include "common.hh"

//
// launch application
// 
int main(int argc, char *argv[]) {
    makeshape::app::App application;
    makeshape::spatial::TriMesh m;
 
    if (argc < 2) {
        m = makeshape::spatial::load_cube();
    } else {
        m = makeshape::spatial::load_mesh(std::string(argv[1]));
    }
    application.add_mesh(m);

    const auto vertices = m.vertices();
    const auto n_rows = vertices.rows();
    
    using PointArray = std::vector<Eigen::Vector3d>;
    std::shared_ptr<PointArray> pts = std::make_shared<PointArray>();
    pts->resize(n_rows);
    for(int i = 0; i < n_rows; ++i) {
        pts->at(i) = vertices.row(i);
    }
    // kdtree
    makeshape::spatial::KDTree ktree(8);
    ktree.build(pts);
    const auto edges = ktree.get_edges();
    application.set_edges(edges);
    application.launch();
    return 0;
}
