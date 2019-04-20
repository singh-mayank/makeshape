// Copyright MakeShape. 2019, All rights reserved.

#include "app.hh"

namespace {
  const Eigen::MatrixXd CUBE_VERTICES = (Eigen::MatrixXd(8,3)<<
    0.0,0.0,0.0,
    0.0,0.0,1.0,
    0.0,1.0,0.0,
    0.0,1.0,1.0,
    1.0,0.0,0.0,
    1.0,0.0,1.0,
    1.0,1.0,0.0,
    1.0,1.0,1.0).finished();
  const Eigen::MatrixXi CUBE_FACES = (Eigen::MatrixXi(12,3)<<
    1,7,5,
    1,3,7,
    1,4,3,
    1,2,4,
    3,8,7,
    3,4,8,
    5,7,8,
    5,8,6,
    1,5,6,
    1,6,2,
    2,6,8,
    2,8,4).finished().array()-1;
} // end namespace

void App::load_cube() {
    v_ = CUBE_VERTICES;
    f_ = CUBE_FACES;
}

bool App::load_mesh(const std::string&& filename) {
    return igl::readOBJ(std::move(filename), v_, f_);
}

bool App::mousepress_callback(igl::opengl::glfw::Viewer& viewer, int x, int y) {


}

void App::custom_menu_callback(igl::opengl::glfw::Viewer* viewer, 
        igl::opengl::glfw::imgui::ImGuiMenu *menu ) {



}

