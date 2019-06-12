// Copyright MakeShape. 2019, All rights reserved.

#include "mesh.hh"

#include <igl/opengl/glfw/Viewer.h>
#include <igl/unproject_onto_mesh.h>

#include <igl/bounding_box_diagonal.h>

#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>
#include <imgui/imgui.h>


#pragma once

namespace makeshape {
namespace app {

class App {

    App(const App& app);
    App& operator=(const App& other);

  public:
    App(){
        viewer_.plugins.push_back(&menu_);
        // callbacks
        viewer_.callback_mouse_down = std::bind(&App::mousepress_callback, this,
                std::placeholders::_1,
                std::placeholders::_2,
                std::placeholders::_3);
        menu_.callback_draw_custom_window = std::bind(&App::custom_menu_callback, this,
                &viewer_,
                &menu_);
    }

    void add_mesh(const mesh::Mesh &m) {
        viewer_.data().set_mesh(m.const_vertices(), m.const_faces());
        viewer_.data().set_face_based(true);
    }

    void launch() {
        viewer_.launch();
    }

  private:
    bool mousepress_callback(igl::opengl::glfw::Viewer& viewer, int x, int y);
    void custom_menu_callback(igl::opengl::glfw::Viewer* viewer,
                              igl::opengl::glfw::imgui::ImGuiMenu *menu );
    igl::opengl::glfw::Viewer viewer_;
    igl::opengl::glfw::imgui::ImGuiMenu menu_;

};

} // namespace app
} // namespace makeshape
