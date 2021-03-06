// Copyright MakeShape. 2019, All rights reserved.

#include "app.hh"

int main(int argc, char *argv[])
{
    makeshape::app::App application;
    makeshape::spatial::TriMesh m;

    if (argc < 2) {
        m = makeshape::spatial::load_cube();
    } else {
        m = makeshape::spatial::load_mesh(std::string(argv[1]));
    }

    application.add_mesh(m);
    application.launch();

    return 0;
}
