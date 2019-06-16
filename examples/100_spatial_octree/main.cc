// Copyright MakeShape. 2019, All rights reserved.

#include "app.hh"
#include "octree.hh"

//
// launch application
// 
int main(int argc, char *argv[])
{
    makeshape::app::App application;
    makeshape::spatial::TriMesh m;

    if (argc < 2) {
        m = makeshape::spatial::load_cube();
    } else {
        m = makeshape::spatial::load_mesh(std::string(argv[1]));
    }

    makeshape::spatial::Octree oc(3);
    oc.build(m.const_vertices());

    application.add_mesh(m);
    application.launch();
    return 0;
}
