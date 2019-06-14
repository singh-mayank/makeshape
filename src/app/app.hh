// Copyright MakeShape. 2019, All rights reserved.

#include "trimesh.hh"

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
  public:
    App();
    void add_mesh(const spatial::TriMesh &m);
    void launch();
  private:
    App(const App& app) = delete;
    App& operator=(const App& other) = delete;
    bool mousepress_callback(igl::opengl::glfw::Viewer& viewer, int x, int y);
    void custom_menu_callback(igl::opengl::glfw::Viewer* viewer,
                              igl::opengl::glfw::imgui::ImGuiMenu *menu );
    igl::opengl::glfw::Viewer viewer_;
    igl::opengl::glfw::imgui::ImGuiMenu menu_;
};

} // namespace app
} // namespace makeshape
