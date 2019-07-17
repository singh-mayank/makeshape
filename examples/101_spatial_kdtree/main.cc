// Copyright MakeShape. 2019, All rights reserved.

#include "app.hh"
#include "kdtree.hh"
#include "common.hh"

//
// launch application
// 
int main(int argc, char *argv[])
{
    makeshape::app::App application;
/*
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
    pts->reserve(n_rows);
    for(int i = 0; i < n_rows; ++i) {
        pts->push_back(vertices.row(i));
    }
*/
    
    //const Eigen::Vector3d pt{0.9, 0.9, 0.9};
    const Eigen::Vector3d pt{0.1, 0.1, 0.1};
    using PointArray = std::vector<Eigen::Vector3d>;
    std::shared_ptr<PointArray> pts = std::make_shared<PointArray>();
    pts->push_back(pt);

    // kdtree
    makeshape::spatial::KDTree ktree(8);
    ktree.build(pts);
    const auto edges = ktree.get_edges();
    application.set_edges(edges);
    
    {
        Eigen::MatrixXd P;
        P.resize(1, 3);
        Eigen::MatrixXd C;
        C.resize(1, 3);
        for(int i = 0; i < 3; ++i) {
            P(0, i) = pt(i);
            C(0, i) = pt(i)*4;
        }
        application.add_point(P, C);
    }



    application.launch();
    return 0;
}
