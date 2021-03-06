// Copyright MakeShape. 2019, All rights reserved.

#include "app.hh"

namespace makeshape {
namespace app {

App::App(){
    viewer_.plugins.push_back(&menu_);
    viewer_.callback_mouse_down = std::bind(&App::mousepress_callback, this,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3);
    menu_.callback_draw_custom_window = std::bind(&App::custom_menu_callback, this,
            viewer_,
            menu_);
}

bool App::mousepress_callback(igl::opengl::glfw::Viewer &viewer, int button, int modifier) {
    // do nothing
    return false;
}

void App::custom_menu_callback(igl::opengl::glfw::Viewer &viewer, 
        igl::opengl::glfw::imgui::ImGuiMenu &menu ) {
    // do nothing
}

void App::add_mesh(const spatial::TriMesh &m) {
    viewer_.data().set_mesh(m.vertices(), m.faces());
    viewer_.data().set_face_based(true);
}

void App::set_edges(const spatial::Edges &e) {
    viewer_.data().set_edges(e.P, e.E, e.C);
}

void App::add_point(const Eigen::MatrixXd& P, const Eigen::MatrixXd& C) {
    viewer_.data().set_points(P, C);
}

} // namespace app
} // namespace makeshape
