// Copyright MakeShape. 2019, All rights reserved.

#include "trimesh.hh"
#include "edges.hh"

#pragma warning( push )
#pragma warning( disable : 4018)
#pragma warning( disable : 4244)
#pragma warning( disable : 4996)
#pragma warning( disable : 4305)
#pragma warning( disable : 4267)
#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>
#include <imgui/imgui.h>
#pragma warning( pop ) 

#pragma once

namespace makeshape {
namespace app {

class App {
  public:
    App();
    bool mousepress_callback(igl::opengl::glfw::Viewer &viewer, int button, int modifier);
    void custom_menu_callback(igl::opengl::glfw::Viewer &viewer,
                              igl::opengl::glfw::imgui::ImGuiMenu &menu );
    void add_mesh(const spatial::TriMesh &m);
    void launch() { viewer_.launch(); }
  private:
    App(const App& app) = delete;
    App& operator=(const App& other) = delete;
    igl::opengl::glfw::Viewer viewer_;
    igl::opengl::glfw::imgui::ImGuiMenu menu_;
};

} // namespace app
} // namespace makeshape
